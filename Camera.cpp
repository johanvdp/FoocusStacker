// The author disclaims copyright to this source code.

#include "Camera.h"
#include "Debug.h"

// camera control I/O
#define CAMERA_FOCUS D7
#define CAMERA_SHUTTER D6

Camera::Camera(Clock* clk) :
		Output() {
	clock = clk;
	configuration = new CameraConfiguration();
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

Configuration* Camera::getConfiguration() {
	return configuration;
}

CameraConfiguration::CameraConfiguration() {
}

CameraConfiguration::~CameraConfiguration() {
}

int CameraConfiguration::getItemCount() {
	return ITEM_COUNT;
}

String* CameraConfiguration::getItemNames() {
	return itemNames;
}

String* CameraConfiguration::getItemUnits() {
	return itemUnits;
}

long* CameraConfiguration::getItemValues() {
	return itemValues;
}

long* CameraConfiguration::getItemValuesMin() {
	return itemValuesMin;
}

long* CameraConfiguration::getItemValuesMax() {
	return itemValuesMax;
}

long CameraConfiguration::getClickCount() {
	return itemValues[ITEM_CLICK_COUNT];
}

long CameraConfiguration::getCameraShakeDelayMs() {
	return itemValues[ITEM_CAMERA_SHAKE_DELAY_MS];
}

long CameraConfiguration::getCameraSaveDurationMs() {
	return itemValues[ITEM_CAMERA_SAVE_DURATION_MS];
}
