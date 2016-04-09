// The author disclaims copyright to this source code.
#include "Recording.h"
#include "Debug.h"

Recording::Recording() :
		Component() {
	configuration = new RecordingConfiguration();
}

Recording::~Recording() {
}

void Recording::setup() {
	Debug::getInstance()->info("Recording::setup");
}

void Recording::clearStepPositions() {
	for (int i = 0; i < RECORD_STEP_COUNT; i++) {
		stepPositions[i] = 0;
	}
}

long Recording::getStepPosition(int index) {
	return stepPositions[index];
}

int Recording::getCurrentStepIndex() {
	return stepIndex;
}

long Recording::getCurrentStepPosition() {
	return stepPositions[stepIndex];
}

void Recording::setStepPosition(int index, long position) {
	stepPositions[index] = position;
}

void Recording::changeCurrentStepPosition(long positionDelta) {
	stepPositions[stepIndex] += positionDelta;
}

int Recording::getStepIndex() {
	return stepIndex;
}

void Recording::resetStepIndex() {
	stepIndex = 0;
}

boolean Recording::nextStepIndex() {
	if (stepIndex < configuration->getStepCount() - 1) {
		stepIndex++;
		return true;
	}
	return false;
}

boolean Recording::previousStepIndex() {
	if (stepIndex > 0) {
		stepIndex--;
		return true;
	}
	return false;
}

Configuration* Recording::getConfiguration() {
	return configuration;
}

long Recording::getStepCount() {
	return configuration->getStepCount();
}

long Recording::getStepIntervalMs() {
	return configuration->getStepIntervalMs();
}

long Recording::getIterations() {
	return configuration->getIterations();
}

RecordingConfiguration::RecordingConfiguration() {
}

RecordingConfiguration::~RecordingConfiguration() {
}

const int RecordingConfiguration::getItemCount() {
	return ITEM_COUNT;
}

const String* RecordingConfiguration::getItemNames() {
	static const String ITEM_NAMES[ITEM_COUNT] = //
			{ "step count", "step interval", "iterations" };
	return ITEM_NAMES;
}

const String* RecordingConfiguration::getItemUnits() {
	static const String ITEM_UNITS[ITEM_COUNT] = //
			{ "", "[s]", "" };
	return ITEM_UNITS;
}

long* RecordingConfiguration::getItemValues() {
	return itemValues;
}

const long* RecordingConfiguration::getItemValuesMin() {
	static const long ITEM_VALUES_MIN[ITEM_COUNT] = //
			{ 1, 0, 1 };
	return ITEM_VALUES_MIN;
}

const long* RecordingConfiguration::getItemValuesMax() {
	static const long ITEM_VALUES_MAX[ITEM_COUNT] = //
			{ Recording::RECORD_STEP_COUNT, 3600, 1000 };
	return ITEM_VALUES_MAX;
}

long RecordingConfiguration::getStepCount() {
	return itemValues[ITEM_STEP_COUNT];
}

long RecordingConfiguration::getStepIntervalMs() {
	return itemValues[ITEM_STEP_INTERVAL_S] * 1000;
}

long RecordingConfiguration::getIterations() {
	return itemValues[ITEM_ITERATIONS];
}
