// The author disclaims copyright to this source code.
#include "Domain.h"

// =========================================================
// RECORDING
// =========================================================

Recording::Recording(Configuration* c) {
	configuration = c;
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

// =========================================================
// CONFIGURATION
// =========================================================

Configuration::Configuration() {
}

Configuration::~Configuration() {
}

void Configuration::setup() {
	Debug::getInstance()->info("Configuration::setup");
}

String Configuration::getCurrentItemName() {
	return itemNames[itemIndex];
}

String Configuration::getCurrentItemUnit() {
	return itemUnits[itemIndex];
}

long Configuration::getCurrentItemValue() {
	return itemValues[itemIndex];
}

void Configuration::changeCurrentItemValue(long deltaValue) {
	long newValue = itemValues[itemIndex] += deltaValue;
	if (newValue < itemValuesMin[itemIndex]) {
		newValue = itemValuesMin[itemIndex];
	} else if (newValue > itemValuesMax[itemIndex]) {
		newValue = itemValuesMax[itemIndex];
	}
	itemValues[itemIndex] = newValue;
}

void Configuration::nextItemIndex() {
	if (itemIndex < (CONFIGURATION_ITEM_COUNT - 1)) {
		itemIndex++;
	}
}

void Configuration::previousItemIndex() {
	if (itemIndex > 0) {
		itemIndex--;
	}
}

long Configuration::getStepCount() {
	return itemValues[CONFIGURATION_ITEM_STEP_COUNT];
}

long Configuration::getStepIntervalMs() {
	return itemValues[CONFIGURATION_ITEM_STEP_INTERVAL_S] * 1000;
}

long Configuration::getClickCount() {
	return itemValues[CONFIGURATION_ITEM_CLICK_COUNT];
}

long Configuration::getCameraShakeDelayMs() {
	return itemValues[CONFIGURATION_ITEM_CAMERA_SHAKE_DELAY_MS];
}

long Configuration::getCameraSaveDurationMs() {
	return itemValues[CONFIGURATION_ITEM_CAMERA_SAVE_DURATION_MS];
}

long Configuration::getIterations() {
	return itemValues[CONFIGURATION_ITEM_ITERATIONS];
}

boolean Configuration::isDebugErrorEnabled() {
	return itemValues[CONFIGURATION_ITEM_DEBUG_ERRORS_ENABLED] != 0;
}

boolean Configuration::isDebugInfoEnabled() {
	return itemValues[CONFIGURATION_ITEM_DEBUG_INFO_ENABLED] != 0;
}

boolean Configuration::isDebugDebugEnabled() {
	return itemValues[CONFIGURATION_ITEM_DEBUG_DEBUG_ENABLED] != 0;
}

long Configuration::getActuatorDelayMs() {
	return itemValues[CONFIGURATION_ITEM_ACTUATOR_DELAY_MS];
}

boolean Configuration::isActuatorHold() {
	return itemValues[CONFIGURATION_ITEM_ACTUATOR_HOLD] != 0;
}


// =========================================================
// INFO
// =========================================================

Information::Information() {
}

Information::~Information() {
}

void Information::setup() {
	Debug::getInstance()->info("Information::setup");
}

String Information::getCurrentItemName() {
	return itemNames[itemIndex];
}

String Information::getCurrentItemUnit() {
	return itemUnits[itemIndex];
}

long Information::getCurrentItemValue() {
	return itemValues[itemIndex];
}

void Information::setSupplyVoltageMilliV(unsigned long value) {
	itemValues[INFO_ITEM_SUPPLY_VOLTAGE_MV] = value;
}

void Information::setSupplyCurrentMilliA(unsigned long value) {
	itemValues[INFO_ITEM_SUPPLY_CURRENT_MA] = value;
}

void Information::setSupplyPowerMilliW(unsigned long value) {
	itemValues[INFO_ITEM_SUPPLY_POWER_MW] = value;
}

void Information::setStatisticsAverageMillis(unsigned long value) {
	itemValues[INFO_ITEM_STATISTICS_AVERAGE_MS] = value;
}

void Information::setStatisticsMinimumMillis(unsigned long value) {
	itemValues[INFO_ITEM_STATISTICS_MINIMUM_MS] = value;
}

void Information::setStatisticsMaximumMillis(unsigned long value) {
	itemValues[INFO_ITEM_STATISTICS_MAXIMUM_MS] = value;
}

void Information::nextItemIndex() {
	if (itemIndex < (INFO_ITEM_COUNT - 1)) {
		itemIndex++;
	} else {
		itemIndex = 0;
	}
}

