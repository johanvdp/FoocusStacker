// The author disclaims copyright to this source code.
#include "Debug.h"

Debug* Debug::instance = NULL;

Debug* Debug::createInstance(Configuration* c) {
	if (!instance) {
		instance = new Debug();
		instance->configuration = c;
	}
	return instance;
}

Debug* Debug::getInstance() {
	return instance;
}

Debug::Debug() {
	configuration = NULL;
}

Debug::~Debug() {
}

void Debug::setup() {
	Serial.begin(115200);
}

void Debug::info(String info) {
	if (configuration->isDebugInfoEnabled()) {
		Serial.println("INFO: " + info);
	}
}

void Debug::error(String error) {
	if (configuration->isDebugErrorEnabled()) {
		Serial.println("ERROR: " + error);
	}
}
