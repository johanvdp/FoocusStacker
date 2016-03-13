// The author disclaims copyright to this source code.
#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "Component.h"
#include "Clock.h"

class Buttons: public Input {

public:

	Buttons(Clock *clock);
	virtual ~Buttons();

	void setup();
	void read();

	boolean isPressed(int index);
	boolean isReleased(int index);
	boolean isActive(int index);
	unsigned long getActiveDuration(int index);

private:

	static const int BUTTON_COUNT = 8;
	static const int BUTTON_DEBOUNCE_PERIOD_MS = 100;
	static const int I2C_BUTTONS = 0x26;

	byte readHardware();
	void update(int index, boolean released);
	void update(byte bits);
	void reset();

	Clock* clock;
	unsigned long activeSince[BUTTON_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	boolean pressed[BUTTON_COUNT] = { false, false, false, false, false, false,
	false, false };
	boolean released[BUTTON_COUNT] = { false, false, false, false, false, false,
	false, false };
	unsigned long debounceEndTime[BUTTON_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
};
#endif

