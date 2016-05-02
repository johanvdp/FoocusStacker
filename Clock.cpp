// The author disclaims copyright to this source code.
#include "Clock.h"
#include "Debug.h"

Clock::Clock() :
		Input() {
	timestamp = 0;
}

Clock::~Clock() {
}

void Clock::setup() {
	Debug::getInstance()->debug("Clock::setup");
	timestamp = millis();
}

void Clock::read() {
	timestamp = millis();
}

unsigned long Clock::getTimestamp() {
	return timestamp;
}
