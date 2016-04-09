// The author disclaims copyright to this source code.
#ifndef POWERSUPPLY_H
#define POWERSUPPLY_H

#include <Arduino.h>
#include "Component.h"
#include "Clock.h"

class Powersupply: public Component, public Input, public Output {

public:
	enum State {
		IDLE, START_REQUESTED, WAIT_FOR_RESULT
	};

	Powersupply(Clock *clock);
	virtual ~Powersupply();

	void setup();
	void read();
	void write();

	void startMeasurement();
	boolean isReady();
	double getShuntVoltage();
	double getBusVoltage();
	double getShuntCurrent();
	double getBusPower();

private:

	static const uint8_t I2C_INA219             = 0x40;

	static const uint8_t REGISTER_CONFIG        = 0x00;
	static const uint8_t REGISTER_SHUNT_VOLTAGE = 0x01;
	static const uint8_t REGISTER_BUS_VOLTAGE   = 0x02;
	static const uint8_t REGISTER_POWER         = 0x03;
	static const uint8_t REGISTER_CURRENT       = 0x04;
	static const uint8_t REGISTER_CALIBRATION   = 0x05;

	static const uint16_t RESET                = 0x8000;

	static const uint16_t BUS_RANGE_MASK       = 0x2000;
	static const uint16_t BUS_RANGE_16V        = 0x0000;
	static const uint16_t BUS_RANGE_32V        = 0x2000;

	static const uint16_t SHUNT_RANGE_MASK     = 0x1800;
	static const uint16_t SHUNT_RANGE_40MV     = 0x0000;
	static const uint16_t SHUNT_RANGE_80MV     = 0x0800;
	static const uint16_t SHUNT_RANGE_160MV    = 0x1000;
	static const uint16_t SHUNT_RANGE_320MV    = 0x1800;

	static const uint16_t BUS_RESOLUTION_MASK  = 0x0780;
	static const uint16_t BUS_RESOLUTION_9BIT  = 0x0080;
	static const uint16_t BUS_RESOLUTION_10BIT = 0x0100;
	static const uint16_t BUS_RESOLUTION_11BIT = 0x0200;
	static const uint16_t BUS_RESOLUTION_12BIT = 0x0400;

	static const uint16_t SHUNT_RESOLUTION_MASK            = 0x0078;
	static const uint16_t SHUNT_RESOLUTION_9BIT_84US       = 0x0000;
	static const uint16_t SHUNT_RESOLUTION_10BIT_148US     = 0x0008;
	static const uint16_t SHUNT_RESOLUTION_11BIT_276US     = 0x0010;
	static const uint16_t SHUNT_RESOLUTION_12BIT_532US     = 0x0018;
	static const uint16_t SHUNT_RESOLUTION_12BITx2_1060US  = 0x0048;
	static const uint16_t SHUNT_RESOLUTION_12BITx4_2130US  = 0x0050;
	static const uint16_t SHUNT_RESOLUTION_12BITx8_4260US  = 0x0058;
	static const uint16_t SHUNT_RESOLUTION_12BITx16_8510US = 0x0060;
	static const uint16_t SHUNT_RESOLUTION_12BITx32_17MS   = 0x0068;
	static const uint16_t SHUNT_RESOLUTION_12BITx64_34MS   = 0x0070;
	static const uint16_t SHUNT_RESOLUTION_12BITx128_69MS  = 0x0078;

	static const uint16_t MODE_MASK             = 0x0007;
	static const uint16_t MODE_POWERDOWN        = 0x0000;
	static const uint16_t MODE_SHUNT_TRIGGERED  = 0x0001;
	static const uint16_t MODE_BUS_TRIGGERED    = 0x0002;
	static const uint16_t MODE_BOTH_TRIGGERED   = 0x0003;
	static const uint16_t MODE_ADCOFF           = 0x0004;
	static const uint16_t MODE_SHUNT_CONTINUOUS = 0x0005;
	static const uint16_t MODE_BUS_CONTINUOUS   = 0x0006;
	static const uint16_t MODE_BOTH_CONTINUOUS  = 0x0007;

	void readResult();
	void writeRegister(uint8_t reg, uint16_t value);
	uint16_t readRegister(uint8_t reg);
	int getConversionTimeMillis();
	int getShuntRangeCount();
	int getBusRangeCount();
	double getBusRangeVolt();
	double getShuntRangeVolt();
	boolean isModeContinuous();

	Clock* clock;
	State state;
	uint16_t configuration;
	// Shunt resistor value [Ohm]
	// default INA219 module 100 mOhm
	double shuntResistanceOhm;
	// Shunt voltage measurement resoltion (LSB) [V]
	// calculated from configuration
	double shuntResolutionVolt;
	// Bus voltage measurement resoltion (LSB) [V]
	// calculated from configuration
	double busResolutionVolt;
	// measured value
	double shuntVoltage;
	// measured value
	double busVoltage;
	// calculated after measurement
	double shuntCurrent;
	// calculated after measurement
	double busPower;
	// chip status, conversion/calculation overflow
	boolean overflow;
	// chip status, conversion ready
	boolean ready;
	unsigned long readyTimestamp;
};

#endif
