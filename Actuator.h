// The author disclaims copyright to this source code.
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include "Component.h"
#include "Debug.h"

class Actuator: public FullProcess {

public:

	Actuator(Configuration* configuration);
	virtual ~Actuator();

	void setup();
	void read();
	void process();
	void write();

	void requestUp();
	void requestDown();
	boolean isLimitUp();
	boolean isLimitDown();
	int getPosition();

private:

	Configuration* configuration;

	void pulse();
	void up();
	void down();

	boolean limitUp;
	boolean limitDown;
	long position = 0;
	boolean upPending;
	boolean downPending;
	boolean goingUp;
	boolean goingDown;
};

#endif

