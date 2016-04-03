// The author disclaims copyright to this source code.
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Component.h"
#include "Debug.h"


class Actuator: public Component, Input, Output {


public:
	enum State {
		STOPPED,
		MOVING_UP,
		MOVING_DOWN
	};

	Actuator(Configuration* configuration);
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

private:

	Configuration* configuration;

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

#endif

