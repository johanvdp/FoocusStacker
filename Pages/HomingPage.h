// The author disclaims copyright to this source code.
#ifndef HOMINGPAGE_H
#define HOMINGPAGE_H

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"
#include "../Actuator.h"

class HomingPage: public Page {

public:

	HomingPage(LCD* l, Actuator* a);

protected:

	void display();

	Actuator* actuator;
};

#endif
