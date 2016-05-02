// The author disclaims copyright to this source code.

#include "Powersupply.h"

#include <Wire.h>

#include "Debug.h"

Powersupply::Powersupply(Clock *clk) {
	// INA219 module configuration
	// default: 100 mOhm
	shuntResistanceOhm = 100e-3;
	// INA219 chip configuration
	configuration = //
			BUS_RANGE_32V |
			SHUNT_RANGE_320MV |
			BUS_RESOLUTION_12BIT |
			SHUNT_RESOLUTION_12BITx128_69MS |
			MODE_BOTH_TRIGGERED;
	// fixed value 4mV per bit
	busResolutionVolt = 4e-3;
	// calculated from configuration
	shuntResolutionVolt = 0;

	// measured value
	shuntVoltage = 0;
	// measured value
	busVoltage = 0;
	// measured value
	ready = false;
	// measured value
	overflow = false;
	// calculated value
	shuntCurrent = 0;
	// calculated value
	busPower = 0;

	clock = clk;
	state = IDLE;
	readyTimestamp = 0;
}

Powersupply::~Powersupply() {
}

void Powersupply::setup() {
	Debug::getInstance()->debug("Powersupply::setup");

	shuntResolutionVolt = getShuntRangeVolt() / getShuntRangeCount();
	writeRegister(REGISTER_CALIBRATION, 0);

	startMeasurement();
}

void Powersupply::read() {
	if (state == WAIT_FOR_RESULT) {
		unsigned long now = clock->getTimestamp();
		if (now > readyTimestamp) {
			readResult();
			state = IDLE;
		}
	} else if (state == IDLE && isModeContinuous()) {
		readResult();
	}
}

void Powersupply::readResult() {

	uint16_t shuntVoltageRaw = readRegister(REGISTER_SHUNT_VOLTAGE);
	shuntVoltage = shuntVoltageRaw * shuntResolutionVolt;

	uint16_t busVoltageRaw = readRegister(REGISTER_BUS_VOLTAGE);
	overflow = busVoltageRaw & 0x0001;
	ready = busVoltageRaw & 0x0002;
	busVoltage = (busVoltageRaw >> 3) * busResolutionVolt;

	shuntCurrent = shuntVoltage / shuntResistanceOhm;
	busPower = busVoltage * shuntCurrent;

	if (overflow || !ready) {
		Debug::getInstance()->error(
				"Powersupply::read overflow:" + String(!!overflow) + ", ready:"
						+ String(!!ready));
	} else {
		Debug::getInstance()->debug(
				"Powersupply::readResult shuntVoltage:"
						+ String(shuntVoltage * 1000.0, 1) + "mV");
		Debug::getInstance()->debug(
				"Powersupply::readResult busVoltage:" + String(busVoltage, 2)
						+ "V");
		Debug::getInstance()->debug(
				"Powersupply::readResult shuntCurrent:"
						+ String(shuntCurrent * 1000, 0) + "mA");
		Debug::getInstance()->debug(
				"Powersupply::readResult busPower:" + String(busPower, 2)
						+ "W");
	}
}

void Powersupply::startMeasurement() {
	if (state == IDLE) {
		writeRegister(REGISTER_CONFIG, configuration);
		unsigned long now = clock->getTimestamp();
		readyTimestamp = now + getConversionTimeMillis();
		state = WAIT_FOR_RESULT;
	} else {
		Debug::getInstance()->error("Powersupply::startMeasurement not idle");
	}
}

double Powersupply::getShuntVoltage() {
	return shuntVoltage;
}

double Powersupply::getBusVoltage() {
	return busVoltage;
}

double Powersupply::getBusPower() {
	return busPower;
}

double Powersupply::getShuntCurrent() {
	return shuntCurrent;
}

boolean Powersupply::isReady() {
	return state == IDLE;
}

void Powersupply::write() {
	if (state == START_REQUESTED) {
		writeRegister(REGISTER_CONFIG, configuration);
		if (isModeContinuous()) {

		} else {
			unsigned long now = clock->getTimestamp();
			readyTimestamp = now + 1;
			state = WAIT_FOR_RESULT;
		}
	}
}

void Powersupply::writeRegister(uint8_t reg, uint16_t value) {
	Debug::getInstance()->debug(
			"Powersupply::writeRegister " + String(reg) + ":" + String(value, 2)
					+ "b (" + String(value) + "d)");
	Wire.beginTransmission(I2C_INA219);
	Wire.write(reg);
	Wire.write((value >> 8) & 0xFF);
	Wire.write(value & 0xFF);
	Wire.endTransmission();
}

uint16_t Powersupply::readRegister(uint8_t reg) {
	Wire.beginTransmission(I2C_INA219);
	Wire.write(reg);
	Wire.endTransmission();
	delay(getConversionTimeMillis());
	Wire.requestFrom(I2C_INA219, (uint8_t)2);
	uint16_t msb = Wire.read();
	uint16_t lsb = Wire.read();
	uint16_t value = msb << 8 | lsb;
	Debug::getInstance()->debug(
			"Powersupply::readRegister " + String(reg) + "=" + String(value, 2)
					+ "b (" + String(value) + "d)");
	return value;
}

double Powersupply::getShuntRangeVolt() {
	switch (configuration & SHUNT_RANGE_MASK) {
	case SHUNT_RANGE_40MV:
		return 40e-3;
	case SHUNT_RANGE_80MV:
		return 80e-3;
	case SHUNT_RANGE_160MV:
		return 160e-3;
	case SHUNT_RANGE_320MV:
	default:
		return 320e-3;
	}
}

double Powersupply::getBusRangeVolt() {
	switch (configuration & BUS_RANGE_MASK) {
	case BUS_RANGE_16V:
		return 16.0;
	case BUS_RANGE_32V:
	default:
		return 32.0;
	}
}

int Powersupply::getBusRangeCount() {
	switch (configuration & BUS_RESOLUTION_MASK) {
	case BUS_RESOLUTION_9BIT:
		return 512;
	case BUS_RESOLUTION_10BIT:
		return 1024;
	case BUS_RESOLUTION_11BIT:
		return 2048;
	case BUS_RESOLUTION_12BIT:
	default:
		return 4096;
	}
}

int Powersupply::getShuntRangeCount() {
	switch (configuration & SHUNT_RESOLUTION_MASK) {
	case SHUNT_RESOLUTION_9BIT_84US:
		return 512;
	case SHUNT_RESOLUTION_10BIT_148US:
		return 1024;
	case SHUNT_RESOLUTION_11BIT_276US:
		return 2048;
	case SHUNT_RESOLUTION_12BIT_532US:
	default:
		return 4096;
	}
}

int Powersupply::getConversionTimeMillis() {
	switch (configuration & SHUNT_RESOLUTION_MASK) {
	case SHUNT_RESOLUTION_9BIT_84US:
		return 1;
	case SHUNT_RESOLUTION_10BIT_148US:
		return 1;
	case SHUNT_RESOLUTION_11BIT_276US:
		return 1;
	case SHUNT_RESOLUTION_12BITx2_1060US:
		return 2;
	case SHUNT_RESOLUTION_12BITx4_2130US:
		return 3;
	case SHUNT_RESOLUTION_12BITx8_4260US:
		return 5;
	case SHUNT_RESOLUTION_12BITx16_8510US:
		return 9;
	case SHUNT_RESOLUTION_12BITx32_17MS:
		return 18;
	case SHUNT_RESOLUTION_12BITx64_34MS:
		return 35;
	case SHUNT_RESOLUTION_12BITx128_69MS:
		return 70;
	case SHUNT_RESOLUTION_12BIT_532US:
	default:
		return 1;
	}
}

boolean Powersupply::isModeContinuous() {
	switch (configuration & MODE_MASK) {
	case MODE_BOTH_CONTINUOUS:
	case MODE_BUS_CONTINUOUS:
	case MODE_SHUNT_CONTINUOUS:
		return true;
	default:
		return false;
	}
}
