// The author disclaims copyright to this source code.
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Component.h"
#include "Debug.h"


class Actuator: public FullProcess {


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
	void process();
	void write();

	boolean isLimitUp();
	boolean isLimitDown();
	Actuator::State getState();

	long getPosition();
	void setTargetPosition(long position);

private:

	Configuration* configuration;

	void pulse();
	void up();
	void down();

	boolean limitUp;
	boolean limitDown;
	Actuator::State state;
	Actuator::State previousState;
	long position = 0;
	long targetPosition = 0;
};

#endif

