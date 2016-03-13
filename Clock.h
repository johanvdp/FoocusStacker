// The author disclaims copyright to this source code.
#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include "Component.h"

class Clock: public Input {

public:

	Clock();
	virtual ~Clock();

	void setup();
	void read();

	unsigned long getTimestamp();

private:

	unsigned long timestamp;
};

#endif
