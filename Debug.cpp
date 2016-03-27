// The author disclaims copyright to this source code.
#include "Debug.h"
#include <Arduino.h>

Debug* Debug::instance = NULL;

Debug* Debug::createInstance(Clock* clk, Configuration* c) {
	if (!instance) {
		instance = new Debug();
		instance->clock = clk;
		instance->configuration = c;
	}
	return instance;
}

Debug* Debug::getInstance() {
	return instance;
}

Debug::Debug() {
	configuration = NULL;
	clock = NULL;
	previousTimestamp = 0;
}

Debug::~Debug() {
}

void Debug::setup() {
	Serial.begin(115200);
	Debug::getInstance()->info("Debug::setup");
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

