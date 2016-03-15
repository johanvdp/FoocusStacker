// The author disclaims copyright to this source code.

#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include "Component.h"
#include "Domain.h"
#include "Clock.h"
#include "Debug.h"

class Camera: public Output {

public:

	Camera(Clock* clock, Configuration* configuration);
	virtual ~Camera();

	void setup();
	void write();

	void click();

private:

	Clock* clock;
	Configuration* configuration;
	unsigned long pressFocusTimestamp;
	unsigned long pressShutterTimestamp;
	unsigned long releaseBothTimestamp;
};

#endif
