// The author disclaims copyright to this source code.
#include <Wire.h>
#include "Buttons.h"
#include "Debug.h"

Buttons::Buttons(Clock* c) :
		Input() {
	clock = c;
}

Buttons::~Buttons() {
}

void Buttons::setup() {
	Debug::getInstance()->info("Buttons::setup");
	Wire.beginTransmission(I2C_BUTTONS);
	// configure all buttons as input
	Wire.write(0xFF);
	Wire.endTransmission();
}

void Buttons::read() {
	reset();
	byte bits = readHardware();
	update(bits);
}

byte Buttons::readHardware() {
	Wire.requestFrom(I2C_BUTTONS, 1);
	if (Wire.available()) {
		return Wire.read();
	}
	Debug::getInstance()->error("Buttons::readHardware failed");
	return 0xFF;
}

void Buttons::update(int index, boolean isReleased) {
	unsigned long now = clock->getTimestamp();

	// ignore changes in debounce period
	if (now > debounceEndTime[index]) {

		boolean wasActive = activeSince[index] > 0;

		// process change
		if (wasActive && isReleased) {
			// mark button state
			activeSince[index] = 0;
			// mark edge detect
			released[index] = true;
			// start debounce period
			debounceEndTime[index] = now + BUTTON_DEBOUNCE_PERIOD_MS;
			// show button released on terminal
			String text = "Buttons::update button" + String(index)
					+ ":released";
			Debug::getInstance()->info(text);
		}
		if (!wasActive & !isReleased) {
			// mark button state
			activeSince[index] = now;
			// mark edge detect
			pressed[index] = true;
			// start debounce period
			debounceEndTime[index] = now + BUTTON_DEBOUNCE_PERIOD_MS;
			// show button pressed on terminal
			String text = "Buttons::update button" + String(index) + ":pressed";
			Debug::getInstance()->info(text);
		}
	}
}

void Buttons::update(byte bits) {
	update(0, bits & 0x01);
	update(1, bits & 0x02);
	update(2, bits & 0x04);
	update(3, bits & 0x08);
	update(4, bits & 0x10);
	update(5, bits & 0x20);
	update(6, bits & 0x40);
	update(7, bits & 0x80);
}

// check button edge
boolean Buttons::isReleased(int index) {
	boolean wasReleased = released[index];
	released[index] = false;
	return wasReleased;
}

// check button edge
boolean Buttons::isPressed(int index) {
	boolean wasPressed = pressed[index];
	pressed[index] = false;
	return wasPressed;
}

// check button active
boolean Buttons::isActive(int index) {
	boolean active = activeSince[index] > 0;
	return active;
}

// get button active duration
unsigned long Buttons::getActiveDuration(int index) {
	unsigned long int since = activeSince[index];
	if (since == 0) {
		// not active
		return 0;
	}
	unsigned long duration = clock->getTimestamp() - since;
	return duration;
}

// reset button edge detection
void Buttons::reset() {
	for (int i = 0; i < BUTTON_COUNT; i++) {
		pressed[i] = false;
		released[i] = false;
	}
}

