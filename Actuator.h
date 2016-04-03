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

	virtual long getActuatorDelayMs();
	virtual boolean isActuatorHold();

	virtual int getItemCount();
	virtual String* getItemNames();
	virtual String* getItemUnits();
	virtual long* getItemValues();
	virtual long* getItemValuesMin();
	virtual long* getItemValuesMax();

private:

	static const int ACTUATOR_CONFIGURATION_ITEM_ACTUATOR_DELAY_MS = 0;
	static const int ACTUATOR_CONFIGURATION_ITEM_ACTUATOR_HOLD = 1;
	static const int ACTUATOR_CONFIGURATION_ITEM_COUNT = 2;

	String itemNames[ACTUATOR_CONFIGURATION_ITEM_COUNT] = {
	//
			"actuator delay", "actuator hold" };
	String itemUnits[ACTUATOR_CONFIGURATION_ITEM_COUNT] = {
	//
			"[us]", "0=no 1=yes" };
	long itemValues[ACTUATOR_CONFIGURATION_ITEM_COUNT] = {
	//
			10, 0 };
	long itemValuesMin[ACTUATOR_CONFIGURATION_ITEM_COUNT] = {
	//
			1, 0 };
	long itemValuesMax[ACTUATOR_CONFIGURATION_ITEM_COUNT] = {
	//
			1000, 1 };
};

#endif

