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

int RecordingConfiguration::getItemCount() {
	return RECORDING_CONFIGURATION_ITEM_COUNT;
}

String* RecordingConfiguration::getItemNames() {
	return itemNames;
}

String* RecordingConfiguration::getItemUnits() {
	return itemUnits;
}

long* RecordingConfiguration::getItemValues() {
	return itemValues;
}

long* RecordingConfiguration::getItemValuesMin() {
	return itemValuesMin;
}

long* RecordingConfiguration::getItemValuesMax() {
	return itemValuesMax;
}

long RecordingConfiguration::getStepCount() {
	return itemValues[RECORDING_CONFIGURATION_ITEM_STEP_COUNT];
}

long RecordingConfiguration::getStepIntervalMs() {
	return itemValues[RECORDING_CONFIGURATION_ITEM_STEP_INTERVAL_S] * 1000;
}

long RecordingConfiguration::getIterations() {
	return itemValues[RECORDING_CONFIGURATION_ITEM_ITERATIONS];
}
