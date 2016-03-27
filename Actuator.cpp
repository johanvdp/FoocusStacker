// The author disclaims copyright to this source code.

#include "Actuator.h"

#include "Domain.h"

#include <limits>

// limit switch I/O
#define LIMIT_UP D0
#define LIMIT_DOWN D5

// stepper motor driver I/O
#define DIRECTION D1
#define PULSE D2
#define ENABLE D8

Actuator::Actuator(Configuration* c) :
		FullProcess() {
	configuration = c;
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
	Debug::getInstance()->info("Actuator::setup");
	pinMode(LIMIT_UP, INPUT);
	pinMode(LIMIT_DOWN, INPUT);
	pinMode(DIRECTION, OUTPUT);
	pinMode(PULSE, OUTPUT);
	pinMode(ENABLE, OUTPUT);

	digitalWrite(DIRECTION, HIGH);
	digitalWrite(PULSE, HIGH);
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

void Actuator::process() {
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
			Debug::getInstance()->info(
					"Actuator::write STOPPED " + String(position));
		}
	} else if (state == MOVING_UP) {
		if (previousState != state) {
			Debug::getInstance()->info(
					"Actuator::write MOVING_UP " + String(position));
		}
		position++;
		actuatorUp();
		actuatorPulse();
	} else if (state == MOVING_DOWN) {
		if (previousState != state) {
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
	delayMicroseconds(configuration->getActuatorDelayMs());
}

void Actuator::actuatorDown() {
	digitalWrite(DIRECTION, HIGH);
	delayMicroseconds(configuration->getActuatorDelayMs());
}

void Actuator::actuatorPulse() {
	digitalWrite(PULSE, LOW);
	// pulse 1us low
	delayMicroseconds(1);
	digitalWrite(PULSE, HIGH);
}

void Actuator::actuatorStop() {
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

