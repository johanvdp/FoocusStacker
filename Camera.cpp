// The author disclaims copyright to this source code.

#include "Camera.h"

#include "Domain.h"

// camera control I/O
#define CAMERA_FOCUS D7
#define CAMERA_SHUTTER D6

Camera::Camera(Clock* clk, Configuration* c) :
		Output() {
	clock = clk;
	configuration = c;
	pressFocusTimestamp = 0;
	pressShutterTimestamp = 0;
	releaseBothTimestamp = 0;
	finishTimestamp = 0;
	iteration = 0;
	state = READY;
	clickRequested = false;
}

Camera::~Camera() {
}

void Camera::setup() {
	Debug::getInstance()->info("Camera::setup");
	pinMode(CAMERA_FOCUS, OUTPUT);
	pinMode(CAMERA_SHUTTER, OUTPUT);

	digitalWrite(CAMERA_FOCUS, HIGH);
	digitalWrite(CAMERA_SHUTTER, HIGH);

	state = READY;
	clickRequested = false;
}

void Camera::write() {

	unsigned long now = clock->getTimestamp();

	if (state == READY && clickRequested) {
		iteration = configuration->getClickCount();
		calculateWaitTimes();
		state = WAIT_BEFORE_FOCUS;
	} else if (state == WAIT_BEFORE_FOCUS && now > pressFocusTimestamp) {
		digitalWrite(CAMERA_FOCUS, LOW);
		Debug::getInstance()->info("Camera::write focus");
		state = WAIT_BEFORE_SHUTTER;
	} else if (state == WAIT_BEFORE_SHUTTER && now > pressShutterTimestamp) {
		digitalWrite(CAMERA_SHUTTER, LOW);
		Debug::getInstance()->info("Camera::write shutter");
		state = WAIT_BEFORE_RELEASE;
	} else if (state == WAIT_BEFORE_RELEASE && now > releaseBothTimestamp) {
		digitalWrite(CAMERA_SHUTTER, HIGH);
		digitalWrite(CAMERA_FOCUS, HIGH);
		Debug::getInstance()->info("Camera::write release");
		state = WAIT_BEFORE_FINISH;
	} else if (state == WAIT_BEFORE_FINISH && now > finishTimestamp) {
		Debug::getInstance()->info("Camera::write finish");
		iteration--;
		if (iteration > 0) {
			calculateWaitTimes();
			state = WAIT_BEFORE_FOCUS;
		} else {
			state = READY;
		}
	}

	clickRequested = false;
}

void Camera::click() {
	clickRequested = true;
}

void Camera::calculateWaitTimes() {

	unsigned long now = clock->getTimestamp();
	long int cameraShakeDelayMs = configuration->getCameraShakeDelayMs();
	long int cameraSaveDurationMs = configuration->getCameraSaveDurationMs();

	pressFocusTimestamp = now + cameraShakeDelayMs;
	pressShutterTimestamp = pressFocusTimestamp + 10;
	releaseBothTimestamp = pressShutterTimestamp + 40;
	finishTimestamp = releaseBothTimestamp + cameraSaveDurationMs;
}

boolean Camera::isReady() {
	return state == READY && !clickRequested;
}
