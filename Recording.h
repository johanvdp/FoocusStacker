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

	virtual int getItemCount();
	virtual String* getItemNames();
	virtual String* getItemUnits();
	virtual long* getItemValues();
	virtual long* getItemValuesMin();
	virtual long* getItemValuesMax();

private:

	static const int RECORDING_CONFIGURATION_ITEM_STEP_COUNT = 0;
	static const int RECORDING_CONFIGURATION_ITEM_STEP_INTERVAL_S = 1;
	static const int RECORDING_CONFIGURATION_ITEM_ITERATIONS = 2;
	static const int RECORDING_CONFIGURATION_ITEM_COUNT = 3;

	String itemNames[RECORDING_CONFIGURATION_ITEM_COUNT] = {
	//
			"step count", "step interval", "iterations" };
	String itemUnits[RECORDING_CONFIGURATION_ITEM_COUNT] = {
	//
			"", "[s]", "" };
	long itemValues[RECORDING_CONFIGURATION_ITEM_COUNT] = {
	//
			1, 0, 5 };
	long itemValuesMin[RECORDING_CONFIGURATION_ITEM_COUNT] = {
	//
			1, 0, 1 };
	long itemValuesMax[RECORDING_CONFIGURATION_ITEM_COUNT] = {
	//
			Recording::RECORD_STEP_COUNT, 3600, 1000 };
};

#endif

