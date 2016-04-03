// The author disclaims copyright to this source code.
#ifndef DOMAIN_H
#define DOMAIN_H

#include <Arduino.h>
#include "Component.h"

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
	String itemUnits[INFO_ITEM_COUNT] = { "[mV]", "[mA]", "[mW]", "[ms]",
			"[ms]", "[ms]" };
	unsigned long itemValues[INFO_ITEM_COUNT] = { 0, 0, 0, 0, 0, 0 };
	int itemIndex = 0;
};

#endif

