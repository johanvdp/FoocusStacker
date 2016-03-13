// The author disclaims copyright to this source code.
#include "Actuator.h"

// limit switch I/O
#define LIMIT_UP D6
#define LIMIT_DOWN D5

// stepper motor driver I/O
#define DIRECTION D1
#define PULSE D2

Actuator::Actuator(Configuration* c) :
		FullProcess() {
	configuration = c;
	limitUp = false;
	limitDown = false;
	position = 0;
	upPending = false;
	downPending = false;
	goingUp = false;
	goingDown = false;
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

	upPending = false;
	downPending = false;
}

void Actuator::process() {
	if (limitDown) {
		position = 0;
	}
}

void Actuator::write() {

	if (upPending && !limitUp && !downPending) {
		if (!goingUp) {
			Debug::getInstance()->info("Actuator::goingUp");
			goingUp = true;
			goingDown = false;
		}
		up();
		pulse();
	} else if (downPending && !limitDown && !upPending) {
		if (!goingDown) {
			Debug::getInstance()->info("Actuator::goingDown");
			goingUp = false;
			goingDown = true;
		}
		down();
		pulse();
	} else {
		if (goingUp || goingDown) {
			Debug::getInstance()->info("Actuator::stopped");
			goingUp = false;
			goingDown = false;
		}
	}

	upPending = false;
	downPending = false;
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

void Actuator::requestUp() {
	if (!limitUp) {
		upPending = true;
		position++;
	}
}

void Actuator::requestDown() {
	if (!limitDown) {
		downPending = true;
		position--;
	}
}

boolean Actuator::isLimitDown() {
	return limitDown;
}

boolean Actuator::isLimitUp() {
	return limitUp;
}

int Actuator::getPosition() {
	return position;
}

