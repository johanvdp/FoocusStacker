// The author disclaims copyright to this source code.

#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include "Component.h"
#include "Domain.h"
#include "Clock.h"
#include "Debug.h"

class Camera: public Component, Output {

public:
	enum State {
		READY,
		WAIT_BEFORE_FOCUS,
		WAIT_BEFORE_SHUTTER,
		WAIT_BEFORE_RELEASE,
		WAIT_BEFORE_FINISH,
	};

	Camera(Clock* clock, Configuration* configuration);
	virtual ~Camera();

	void setup();
	void write();

	void click();
	boolean isReady();

private:

	void calculateWaitTimes();

	Clock* clock;
	Configuration* configuration;
	State state;
	int iteration;
	boolean clickRequested;
	unsigned long pressFocusTimestamp;
	unsigned long pressShutterTimestamp;
	unsigned long releaseBothTimestamp;
	unsigned long finishTimestamp;
};

#endif
