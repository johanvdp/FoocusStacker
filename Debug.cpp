// The author disclaims copyright to this source code.
#include "Debug.h"

Debug* Debug::instance = NULL;

Debug* Debug::createInstance(Clock* clk) {
	if (!instance) {
		instance = new Debug(clk);
	}
	return instance;
}

Debug* Debug::getInstance() {
	return instance;
}

Debug::Debug(Clock* clk) {
	configuration = new DebugConfiguration();
	clock = clk;
	previousTimestamp = 0;
}

Debug::~Debug() {
}

void Debug::setup() {
	Serial.begin(115200);
	Debug::getInstance()->debug("Debug::setup");
}

void Debug::debug(String debug) {
	if (configuration->isDebugDebugEnabled()) {
		Serial.println(timestamps() + " DEBUG " + debug);
	}
}

void Debug::info(String info) {
	if (configuration->isDebugInfoEnabled()) {
		Serial.println(timestamps() + " INFO  " + info);
	}
}

void Debug::error(String error) {
	if (configuration->isDebugErrorEnabled()) {
		Serial.println(timestamps() + " ERROR " + error);
	}
}

const String Debug::zeroTemplate = "00000000000000000000";

String Debug::timestamps() {
	unsigned long now = clock->getTimestamp();
	unsigned long relative = now - previousTimestamp;
	previousTimestamp = now;
	return fixedLength(now) + " " + fixedLength(relative);
}

String Debug::fixedLength(unsigned long number) {
	String text = String(number);
	String maxed = text.substring(0, 10);
	int padLength = 10 - maxed.length();
	String padding = zeroTemplate.substring(0, padLength);
	String result = padding + maxed;
	return result;
}

Configuration* Debug::getConfiguration() {
	return configuration;
}

DebugConfiguration::DebugConfiguration() {
}

DebugConfiguration::~DebugConfiguration() {
}

const int DebugConfiguration::getItemCount() {
	return ITEM_COUNT;
}

const String* DebugConfiguration::getItemNames() {
	static const String ITEM_NAMES[ITEM_COUNT] = //
			{ "debug errors", "debug info", "debug debug" };
	return ITEM_NAMES;
}

const String* DebugConfiguration::getItemUnits() {
	static const String ITEM_UNITS[ITEM_COUNT] = //
			{ "0=no 1=yes", "0=no 1=yes", "0=no 1=yes" };
	return ITEM_UNITS;
}

long* DebugConfiguration::getItemValues() {
	return itemValues;
}

const long* DebugConfiguration::getItemValuesMin() {
	static const long ITEM_VALUES_MIN[ITEM_COUNT] = //
			{ 0, 0, 0 };
	return ITEM_VALUES_MIN;
}

const long* DebugConfiguration::getItemValuesMax() {
	static const long ITEM_VALUES_MAX[ITEM_COUNT] = //
			{ 1, 1, 1 };
	return ITEM_VALUES_MAX;
}

boolean DebugConfiguration::isDebugErrorEnabled() {
	return itemValues[ITEM_DEBUG_ERRORS_ENABLED] != 0;
}

boolean DebugConfiguration::isDebugInfoEnabled() {
	return itemValues[ITEM_DEBUG_INFO_ENABLED] != 0;
}

boolean DebugConfiguration::isDebugDebugEnabled() {
	return itemValues[ITEM_DEBUG_DEBUG_ENABLED] != 0;
}

