// The author disclaims copyright to this source code.
#ifndef MANUALPAGE_H_
#define MANUALPAGE_H_

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"
#include "../Actuator.h"

class ManualPage: public Page {

public:

	ManualPage(LCD* l, Actuator* a);

protected:

	void display();

	Actuator* actuator;
};

#endif
