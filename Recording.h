// The author disclaims copyright to this source code.
#ifndef RECORDING_H
#define RECORDING_H

// forward declaration
class RecordingConfiguration;

#include <Arduino.h>
#include "Component.h"
#include "Configuration.h"

class Recording: public Component, public Configurable {

public:

	static const int RECORD_STEP_COUNT = 10;

	Recording();
	virtual ~Recording();

	void setup();

	void clearStepPositions();
	long getStepPosition(int index);
	int getCurrentStepIndex();
	long getCurrentStepPosition();
	void setStepPosition(int index, long position);
	void changeCurrentStepPosition(long positionDelta);
	int getStepIndex();
	void resetStepIndex();
	// return true if successful
	boolean nextStepIndex();
	// return true if successful
	boolean previousStepIndex();

	Configuration* getConfiguration();

	long getStepCount();
	long getStepIntervalMs();
	long getIterations();

private:

	RecordingConfiguration* configuration;
	long stepPositions[RECORD_STEP_COUNT] = { -100, -100, -100, -100, -100,
			-100, -100, -100, -100, -100 };
	int stepIndex = 0;
};

class RecordingConfiguration: public AbstractConfiguration {

public:

	RecordingConfiguration();
	virtual ~RecordingConfiguration();

	long getStepCount();
	long getStepIntervalMs();
	long getIterations();

	virtual const int getItemCount();
	virtual const String* getItemNames();
	virtual const String* getItemUnits();
	virtual long* getItemValues();
	virtual const long* getItemValuesMin();
	virtual const long* getItemValuesMax();

private:

	static const int ITEM_STEP_COUNT = 0;
	static const int ITEM_STEP_INTERVAL_S = 1;
	static const int ITEM_ITERATIONS = 2;
	static const int ITEM_COUNT = 3;

	long itemValues[ITEM_COUNT] = { 1, 0, 5 };
};

#endif

