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

