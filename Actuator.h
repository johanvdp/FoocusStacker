// The author disclaims copyright to this source code.
#ifndef ACTUATOR_H
#define ACTUATOR_H

// forward declaration
class ActuatorConfiguration;

#include <Arduino.h>
#include "Component.h"
#include "Configuration.h"

class Actuator: public Component,
		public Input,
		public Output,
		public Configurable {

public:
	enum State {
		STOPPED, MOVING_UP, MOVING_DOWN
	};

	Actuator();
	virtual ~Actuator();

	void setup();
	void read();
	void write();

	void gotoHome();
	void stop();

	boolean isLimitUp();
	boolean isLimitDown();
	boolean isStopped();

	long getPosition();
	void gotoPosition(long position);

	Configuration* getConfiguration();

private:

	// limit switch I/O
	static const uint8_t LIMIT_UP = D0;
	static const uint8_t LIMIT_DOWN = D5;

	// stepper motor driver I/O
	static const uint8_t DIRECTION = D1;
	static const uint8_t PULSE = D2;
	static const uint8_t ENABLE = D8;

	ActuatorConfiguration* configuration;

	void actuatorPulse();
	void actuatorUp();
	void actuatorDown();
	void actuatorDisable();
	void actuatorEnable();

	boolean limitUp;
	boolean limitDown;
	boolean stopRequested;
	boolean homeRequested;
	State state;
	State previousState;
	long position = 0;
	long targetPosition = 0;
};

class ActuatorConfiguration: public AbstractConfiguration {

public:

	ActuatorConfiguration();
	virtual ~ActuatorConfiguration();

	virtual long getActuatorDelayUs();
	virtual boolean isActuatorHold();

	virtual const int getItemCount();
	virtual const String* getItemNames();
	virtual const String* getItemUnits();
	virtual long* getItemValues();
	virtual const long* getItemValuesMin();
	virtual const long* getItemValuesMax();

private:

	static const int ITEM_ACTUATOR_DELAY_US = 0;
	static const int ITEM_ACTUATOR_HOLD = 1;
	static const int ITEM_COUNT = 2;

	long itemValues[ITEM_COUNT] = { 10, 0 };
};

#endif

