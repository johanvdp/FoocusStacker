// The author disclaims copyright to this source code.

#include "Camera.h"

#include "Domain.h"

// camera control I/O
#define CAMERA_FOCUS D6
#define CAMERA_SHUTTER D7

Camera::Camera(Clock* clk, Configuration* c) :
		Output() {
	clock = clk;
	configuration = c;
	pressFocusTimestamp = 0;
	pressShutterTimestamp = 0;
	releaseBothTimestamp = 0;
}

Camera::~Camera() {
}

void Camera::setup() {
	Debug::getInstance()->info("Camera::setup");
	pinMode(CAMERA_FOCUS, OUTPUT);
	pinMode(CAMERA_SHUTTER, OUTPUT);

	digitalWrite(CAMERA_FOCUS, HIGH);
	digitalWrite(CAMERA_SHUTTER, HIGH);
}

void Camera::write() {
	unsigned long now = clock->getTimestamp();

	if (pressFocusTimestamp != 0 && now > pressFocusTimestamp) {
		digitalWrite(CAMERA_FOCUS, LOW);
		pressFocusTimestamp = 0;
		Debug::getInstance()->info("Camera::write focus");
	} else if (pressShutterTimestamp != 0 && now > pressShutterTimestamp) {
		digitalWrite(CAMERA_SHUTTER, LOW);
		pressShutterTimestamp = 0;
		Debug::getInstance()->info("Camera::write shutter");
	} else if (releaseBothTimestamp != 0 && now > releaseBothTimestamp) {
		digitalWrite(CAMERA_SHUTTER, HIGH);
		digitalWrite(CAMERA_FOCUS, HIGH);
		releaseBothTimestamp = 0;
		Debug::getInstance()->info("Camera::write release");
	}
}

void Camera::click() {
	unsigned long now = clock->getTimestamp();

	pressFocusTimestamp = now;
	pressShutterTimestamp = now + 500;
	releaseBothTimestamp = now + 1000;
}

