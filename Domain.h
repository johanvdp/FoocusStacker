// The author disclaims copyright to this source code.
#ifndef DOMAIN_H
#define DOMAIN_H

// forward declarations
class Configuration;

#include <Arduino.h>
#include "Component.h"
#include "Debug.h"

class Recording: public Component {

public:

	static const int RECORD_STEP_COUNT = 10;

	Recording(Configuration* c);
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

private:

	Configuration* configuration;
	long stepPositions[RECORD_STEP_COUNT] = { -100, -100, -100, -100, -100,
			-100, -100, -100, -100, -100 };
	int stepIndex = 0;
};

class Configuration: public Component {

public:

	Configuration();
	virtual ~Configuration();

	void setup();

	String getCurrentItemName();
	String getCurrentItemUnit();
	long getCurrentItemValue();
	void changeCurrentItemValue(long deltaValue);
	void nextItemIndex();
	void previousItemIndex();

	long getStepCount();
	long getStepIntervalMs();
	long getClickCount();
	long getCameraShakeDelayMs();
	long getCameraSaveDurationMs();
	long getIterations();

	boolean isDebugDebugEnabled();
	boolean isDebugInfoEnabled();
	boolean isDebugErrorEnabled();
	long getActuatorDelayMs();
	boolean isActuatorHold();

private:

	static const int CONFIGURATION_ITEM_STEP_COUNT = 0;
	static const int CONFIGURATION_ITEM_STEP_INTERVAL_S = 1;
	static const int CONFIGURATION_ITEM_CLICK_COUNT = 2;
	static const int CONFIGURATION_ITEM_CAMERA_SHAKE_DELAY_MS = 3;
	static const int CONFIGURATION_ITEM_CAMERA_SAVE_DURATION_MS = 4;
	static const int CONFIGURATION_ITEM_ITERATIONS = 5;
	static const int CONFIGURATION_ITEM_DEBUG_ERRORS_ENABLED = 6;
	static const int CONFIGURATION_ITEM_DEBUG_INFO_ENABLED = 7;
	static const int CONFIGURATION_ITEM_DEBUG_DEBUG_ENABLED = 8;
	static const int CONFIGURATION_ITEM_ACTUATOR_DELAY_MS = 9;
	static const int CONFIGURATION_ITEM_ACTUATOR_HOLD = 10;
	static const int CONFIGURATION_ITEM_COUNT = 11;

	String itemNames[CONFIGURATION_ITEM_COUNT] = {
			//
			"step count", "step interval", "click count", "camera shake delay", "camera save duration",
			"iterations", "debug errors", "debug info", "debug debug", "actuator delay", "actuator hold" };
	String itemUnits[CONFIGURATION_ITEM_COUNT] = {
	//
			"", "[s]", "", "[ms]", "[ms]", "", "0=no 1=yes", "0=no 1=yes", "0=no 1=yes", "[ms]", "0=no 1=yes" };
	long itemValues[CONFIGURATION_ITEM_COUNT] = {
	//
			1, 0, 1, 500, 1000, 5, 1, 1, 0, 10, 0 };
	long itemValuesMin[CONFIGURATION_ITEM_COUNT] = {
	//
			1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0 };
	long itemValuesMax[CONFIGURATION_ITEM_COUNT] = {
	//
			Recording::RECORD_STEP_COUNT, 3600, 100, 5000, 5000, 1000, 1, 1, 1, 1000, 1 };
	int itemIndex = 0;
};

class Information: public Component {

public:

	Information();
	virtual ~Information();

	void setup();

	String getCurrentItemName();
	String getCurrentItemUnit();
	long getCurrentItemValue();
	void setSupplyVoltageMilliV(unsigned long value);
	void setSupplyCurrentMilliA(unsigned long value);
	void setSupplyPowerMilliW(unsigned long value);
	void setStatisticsAverageMillis(unsigned long value);
	void setStatisticsMinimumMillis(unsigned long value);
	void setStatisticsMaximumMillis(unsigned long value);
	void nextItemIndex();

private:

	static const int INFO_ITEM_SUPPLY_VOLTAGE_MV = 0;
	static const int INFO_ITEM_SUPPLY_CURRENT_MA = 1;
	static const int INFO_ITEM_SUPPLY_POWER_MW = 2;
	static const int INFO_ITEM_STATISTICS_AVERAGE_MS = 3;
	static const int INFO_ITEM_STATISTICS_MINIMUM_MS = 4;
	static const int INFO_ITEM_STATISTICS_MAXIMUM_MS = 5;
	static const int INFO_ITEM_COUNT = 6;

	String itemNames[INFO_ITEM_COUNT] = { "voltage", "current", "power",
			"statistics average", "statistics minimum", "statistics maximum" };
	String itemUnits[INFO_ITEM_COUNT] =
			{ "[mV]", "[mA]", "[mW]", "[ms]", "[ms]", "[ms]" };
	unsigned long itemValues[INFO_ITEM_COUNT] = { 0, 0, 0, 0, 0, 0 };
	int itemIndex = 0;
};

#endif

