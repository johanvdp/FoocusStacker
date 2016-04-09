// The author disclaims copyright to this source code.
#include "Domain.h"
#include "Debug.h"

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
	static const String ITEM_NAMES[ITEM_COUNT] = //
			{ "voltage", "current", "power", "statistics average",
					"statistics minimum", "statistics maximum" };
	return ITEM_NAMES[itemIndex];
}

String Information::getCurrentItemUnit() {
	static const String ITEM_UNITS[ITEM_COUNT] = //
			{ "[mV]", "[mA]", "[mW]", "[ms]", "[ms]", "[ms]" };
	return ITEM_UNITS[itemIndex];
}

long Information::getCurrentItemValue() {
	return itemValues[itemIndex];
}

void Information::setSupplyVoltageMilliV(unsigned long value) {
	itemValues[ITEM_SUPPLY_VOLTAGE_MV] = value;
}

void Information::setSupplyCurrentMilliA(unsigned long value) {
	itemValues[ITEM_SUPPLY_CURRENT_MA] = value;
}

void Information::setSupplyPowerMilliW(unsigned long value) {
	itemValues[ITEM_SUPPLY_POWER_MW] = value;
}

void Information::setStatisticsAverageMillis(unsigned long value) {
	itemValues[ITEM_STATISTICS_AVERAGE_MS] = value;
}

void Information::setStatisticsMinimumMillis(unsigned long value) {
	itemValues[ITEM_STATISTICS_MINIMUM_MS] = value;
}

void Information::setStatisticsMaximumMillis(unsigned long value) {
	itemValues[ITEM_STATISTICS_MAXIMUM_MS] = value;
}

void Information::nextItemIndex() {
	if (itemIndex < (ITEM_COUNT - 1)) {
		itemIndex++;
	} else {
		itemIndex = 0;
	}
}

