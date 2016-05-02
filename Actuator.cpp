// The author disclaims copyright to this source code.
#include "Actuator.h"
#include "Debug.h"

#include <limits>

Actuator::Actuator() {
	configuration = new ActuatorConfiguration();
	limitUp = false;
	limitDown = false;
	position = 0;
	targetPosition = 0;
	state = STOPPED;
	previousState = STOPPED;
	stopRequested = false;
	homeRequested = false;
}

Actuator::~Actuator() {
}

void Actuator::setup() {
	Debug::getInstance()->debug("Actuator::setup");
	pinMode(LIMIT_UP, INPUT);
	pinMode(LIMIT_DOWN, INPUT);
	pinMode(DIRECTION, OUTPUT);
	pinMode(PULSE, OUTPUT);
	pinMode(ENABLE, OUTPUT);

	digitalWrite(DIRECTION, HIGH);
	digitalWrite(PULSE, HIGH);
	actuatorDisable();
}

void Actuator::read() {
	if (state == STOPPED) {
		// nothing to do
		return;
	}

	// latch limit switch status
	boolean newLimitUp = !digitalRead(LIMIT_UP);
	boolean newLimitDown = !digitalRead(LIMIT_DOWN);

	// debug show changes
	if (newLimitUp != limitUp) {
		if (newLimitUp) {
			Debug::getInstance()->info("Actuator::read limitUp set");
		} else {
			Debug::getInstance()->info("Actuator::read limitUp cleared");
		}
		limitUp = newLimitUp;
	}
	if (newLimitDown != limitDown) {
		if (newLimitDown) {
			Debug::getInstance()->info("Actuator::read limitDown set");
		} else {
			Debug::getInstance()->info("Actuator::read limitDown cleared");
		}
		limitDown = newLimitDown;
	}
}

void Actuator::write() {

	// decide
	previousState = state;
	if (state == STOPPED) {
		if (stopRequested) {
			// do not start moving again
			targetPosition = position;
			state = STOPPED;
		} else if (homeRequested && !limitDown) {
			// target maximum down position
			gotoPosition(std::numeric_limits<long>::min());
			state = MOVING_DOWN;
		} else if (targetPosition > position && !limitUp) {
			state = MOVING_UP;
		} else if (targetPosition < position && !limitDown) {
			state = MOVING_DOWN;
		}
	} else if (state == MOVING_UP) {
		if (stopRequested) {
			// do not start moving again
			targetPosition = position;
			state = STOPPED;
		} else if (limitUp || position >= targetPosition) {
			state = STOPPED;
		}
	} else if (state == MOVING_DOWN) {
		if (stopRequested) {
			// do not start moving again
			targetPosition = position;
			state = STOPPED;
		} else if (limitDown) {
			// at home position
			position = 0;
			targetPosition = 0;
			state = STOPPED;
		} else if (targetPosition >= position) {
			state = STOPPED;
		}
	}

	// act
	if (state == STOPPED) {
		if (previousState != state) {
			actuatorDisable();
			Debug::getInstance()->info(
					"Actuator::write STOPPED " + String(position));
		}
	} else if (state == MOVING_UP) {
		if (previousState != state) {
			actuatorEnable();
			Debug::getInstance()->info(
					"Actuator::write MOVING_UP " + String(position));
		}
		position++;
		actuatorUp();
		actuatorPulse();
	} else if (state == MOVING_DOWN) {
		if (previousState != state) {
			actuatorEnable();
			Debug::getInstance()->info(
					"Actuator::write MOVING_DOWN " + String(position));
		}
		position--;
		actuatorDown();
		actuatorPulse();
	}

	stopRequested = false;
	homeRequested = false;
}

void Actuator::gotoHome() {
	homeRequested = true;
}

void Actuator::stop() {
	stopRequested = true;
}

void Actuator::actuatorUp() {
	digitalWrite(DIRECTION, LOW);
	delayMicroseconds(configuration->getActuatorDelayUs());
}

void Actuator::actuatorDown() {
	digitalWrite(DIRECTION, HIGH);
	delayMicroseconds(configuration->getActuatorDelayUs());
}

void Actuator::actuatorPulse() {
	digitalWrite(PULSE, LOW);
	// pulse 1us low
	delayMicroseconds(1);
	digitalWrite(PULSE, HIGH);
}

void Actuator::actuatorEnable() {
	digitalWrite(ENABLE, LOW);
}

void Actuator::actuatorDisable() {
	if (configuration->isActuatorHold()) {
		digitalWrite(ENABLE, LOW);
	} else {
		digitalWrite(ENABLE, HIGH);
	}
}

boolean Actuator::isLimitDown() {
	return limitDown;
}

boolean Actuator::isLimitUp() {
	return limitUp;
}

boolean Actuator::isStopped() {
	return state == STOPPED;
}

long Actuator::getPosition() {
	return position;
}

void Actuator::gotoPosition(long p) {
	targetPosition = p;
	// too often
	// Debug::getInstance()->info("Actuator::gotoPosition " + String(targetPosition));
}

Configuration* Actuator::getConfiguration() {
	return configuration;
}

ActuatorConfiguration::ActuatorConfiguration() {
}

ActuatorConfiguration::~ActuatorConfiguration() {
}

const int ActuatorConfiguration::getItemCount() {
	return ITEM_COUNT;
}

const String* ActuatorConfiguration::getItemNames() {
	static const String ITEM_NAMES[ITEM_COUNT] = //
			{ "actuator delay", "actuator hold" };
	return ITEM_NAMES;
}

const String* ActuatorConfiguration::getItemUnits() {
	static const String ITEM_UNITS[ITEM_COUNT] = //
			{ "[us]", "0=no 1=yes" };
	return ITEM_UNITS;
}

long* ActuatorConfiguration::getItemValues() {
	return itemValues;
}

const long* ActuatorConfiguration::getItemValuesMin() {
	static const long ITEM_VALUES_MIN[ITEM_COUNT] = //
			{ 1, 0 };
	return ITEM_VALUES_MIN;
}

const long* ActuatorConfiguration::getItemValuesMax() {
	static const long ITEM_VALUES_MAX[ITEM_COUNT] = //
			{ 1000, 1 };
	return ITEM_VALUES_MAX;
}

long ActuatorConfiguration::getActuatorDelayUs() {
	return itemValues[ITEM_ACTUATOR_DELAY_US];
}

boolean ActuatorConfiguration::isActuatorHold() {
	return itemValues[ITEM_ACTUATOR_HOLD] != 0;
}
