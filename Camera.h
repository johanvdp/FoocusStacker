// The author disclaims copyright to this source code.
#ifndef CAMERA_H
#define CAMERA_H

// forward declaration
class CameraConfiguration;

#include <Arduino.h>
#include "Component.h"
#include "Configuration.h"
#include "Clock.h"

class Camera: public Component, public Output, public Configurable {

public:
	enum State {
		READY,
		WAIT_BEFORE_FOCUS,
		WAIT_BEFORE_SHUTTER,
		WAIT_BEFORE_RELEASE,
		WAIT_BEFORE_FINISH,
	};

	Camera(Clock* clock);
	virtual ~Camera();

	void setup();
	void write();

	void click();
	boolean isReady();

	Configuration* getConfiguration();

private:

	void calculateWaitTimes();

	Clock* clock;
	CameraConfiguration* configuration;
	State state;
	int iteration;
	boolean clickRequested;
	unsigned long pressFocusTimestamp;
	unsigned long pressShutterTimestamp;
	unsigned long releaseBothTimestamp;
	unsigned long finishTimestamp;
};

class CameraConfiguration: public AbstractConfiguration {

public:
	CameraConfiguration();
	virtual ~CameraConfiguration();

	long getClickCount();
	long getCameraShakeDelayMs();
	long getCameraSaveDurationMs();

	virtual const int getItemCount();
	virtual const String* getItemNames();
	virtual const String* getItemUnits();
	virtual long* getItemValues();
	virtual const long* getItemValuesMin();
	virtual const long* getItemValuesMax();

private:

	static const int ITEM_CLICK_COUNT = 0;
	static const int ITEM_CAMERA_SHAKE_DELAY_MS = 1;
	static const int ITEM_CAMERA_SAVE_DURATION_MS = 2;
	static const int ITEM_COUNT = 3;

	long itemValues[ITEM_COUNT] = { 1, 500, 1000 };
};

#endif
