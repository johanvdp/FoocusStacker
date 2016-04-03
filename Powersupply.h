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
