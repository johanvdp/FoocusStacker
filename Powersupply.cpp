// The author disclaims copyright to this source code.

#include "Powersupply.h"

#include <Wire.h>

#include "Debug.h"

#define I2C_INA219              (0x40)

#define REGISTER_CONFIG         (0x00)
#define REGISTER_SHUNT_VOLTAGE  (0x01)
#define REGISTER_BUS_VOLTAGE    (0x02)
#define REGISTER_POWER          (0x03)
#define REGISTER_CURRENT        (0x04)
#define REGISTER_CALIBRATION    (0x05)

#define RESET                 (0x8000)

#define BUS_RANGE_MASK        (0x2000)
#define BUS_RANGE_16V         (0x0000)
#define BUS_RANGE_32V         (0x2000)

#define SHUNT_RANGE_MASK      (0x1800)
#define SHUNT_RANGE_40MV      (0x0000)
#define SHUNT_RANGE_80MV      (0x0800)
#define SHUNT_RANGE_160MV     (0x1000)
#define SHUNT_RANGE_320MV     (0x1800)

#define BUS_RESOLUTION_MASK   (0x0780)
#define BUS_RESOLUTION_9BIT   (0x0080)
#define BUS_RESOLUTION_10BIT  (0x0100)
#define BUS_RESOLUTION_11BIT  (0x0200)
#define BUS_RESOLUTION_12BIT  (0x0400)

#define SHUNT_RESOLUTION_MASK            (0x0078)
#define SHUNT_RESOLUTION_9BIT_84US       (0x0000)
#define SHUNT_RESOLUTION_10BIT_148US     (0x0008)
#define SHUNT_RESOLUTION_11BIT_276US     (0x0010)
#define SHUNT_RESOLUTION_12BIT_532US     (0x0018)
#define SHUNT_RESOLUTION_12BITx2_1060US  (0x0048)
#define SHUNT_RESOLUTION_12BITx4_2130US  (0x0050)
#define SHUNT_RESOLUTION_12BITx8_4260US  (0x0058)
#define SHUNT_RESOLUTION_12BITx16_8510US (0x0060)
#define SHUNT_RESOLUTION_12BITx32_17MS   (0x0068)
#define SHUNT_RESOLUTION_12BITx64_34MS   (0x0070)
#define SHUNT_RESOLUTION_12BITx128_69MS  (0x0078)

#define MODE_MASK             (0x0007)
#define MODE_POWERDOWN        (0x0000)
#define MODE_SHUNT_TRIGGERED  (0x0001)
#define MODE_BUS_TRIGGERED    (0x0002)
#define MODE_BOTH_TRIGGERED   (0x0003)
#define MODE_ADCOFF           (0x0004)
#define MODE_SHUNT_CONTINUOUS (0x0005)
#define MODE_BUS_CONTINUOUS   (0x0006)
#define MODE_BOTH_CONTINUOUS  (0x0007)

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
	Debug::getInstance()->info("Powersupply::setup");

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
		Debug::getInstance()->info(
				"Powersupply::readResult shuntVoltage:"
						+ String(shuntVoltage * 1000.0, 1) + "mV");
		Debug::getInstance()->info(
				"Powersupply::readResult busVoltage:" + String(busVoltage, 2)
						+ "V");
		Debug::getInstance()->info(
				"Powersupply::readResult shuntCurrent:"
						+ String(shuntCurrent * 1000, 0) + "mA");
		Debug::getInstance()->info(
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

void Powersupply::process() {
	// nothing to do
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
	Wire.requestFrom(I2C_INA219, 2);
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
