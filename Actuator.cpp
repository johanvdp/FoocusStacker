// The author disclaims copyright to this source code.

#include "Actuator.h"

#include "Domain.h"

// limit switch I/O
#define LIMIT_UP D5
#define LIMIT_DOWN D0

// stepper motor driver I/O
#define DIRECTION D1
#define PULSE D2

Actuator::Actuator(Configuration* c) :
		FullProcess() {
	configuration = c;
	limitUp = false;
	limitDown = false;
	position = 0;
	targetPosition = 0;
	state = Actuator::State::STOPPED;
	previousState = Actuator::State::STOPPED;
}

Actuator::~Actuator() {
}

void Actuator::setup() {
	Debug::getInstance()->info("Actuator::setup");
	pinMode(LIMIT_UP, INPUT);
	pinMode(LIMIT_DOWN, INPUT);
	pinMode(DIRECTION, OUTPUT);
	pinMode(PULSE, OUTPUT);

	digitalWrite(DIRECTION, HIGH);
	digitalWrite(PULSE, HIGH);
}

void Actuator::read() {
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
	previousState = state;
	if (state == Actuator::State::STOPPED) {
		if (targetPosition > position && !limitUp) {
			state = Actuator::State::MOVING_UP;
		} else if (targetPosition < position && !limitDown) {
			state = Actuator::State::MOVING_DOWN;
		}
	} else if (state == Actuator::State::MOVING_UP) {
		if (limitUp || position >= targetPosition) {
			state = Actuator::State::STOPPED;
		}
	} else if (state == Actuator::State::MOVING_DOWN) {
		if (limitDown || position <= targetPosition) {
			state = Actuator::State::STOPPED;
		}
	}
}

void Actuator::write() {

	if (state == Actuator::State::MOVING_UP) {
		if (previousState != state) {
			Debug::getInstance()->info("Actuator::write MOVING_UP");
		}
		position++;
		up();
		pulse();
	} else if (state == Actuator::State::MOVING_DOWN) {
		if (previousState != state) {
			Debug::getInstance()->info("Actuator::write MOVING_DOWN");
		}
		position--;
		down();
		pulse();
	} else {
		if (previousState != state) {
			Debug::getInstance()->info("Actuator::write STOPPED");
		}
	}
}

void Actuator::up() {
	digitalWrite(DIRECTION, LOW);
	delayMicroseconds(configuration->getActuatorDelayMs());
}

void Actuator::down() {
	digitalWrite(DIRECTION, HIGH);
	delayMicroseconds(configuration->getActuatorDelayMs());
}

void Actuator::pulse() {
	digitalWrite(PULSE, LOW);
	// pulse 1us low
	delayMicroseconds(1);
	digitalWrite(PULSE, HIGH);
}

boolean Actuator::isLimitDown() {
	return limitDown;
}

boolean Actuator::isLimitUp() {
	return limitUp;
}

Actuator::State Actuator::getState() {
	return state;
}

long Actuator::getPosition() {
	return position;
}

void Actuator::setTargetPosition(long p) {
	targetPosition = p;
	Debug::getInstance()->info("Actuator::setTargetPosition " + String(targetPosition));
}

