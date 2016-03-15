// The author disclaims copyright to this source code.
#ifndef STOPPEDPAGE_H
#define STOPPEDPAGE_H

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"

class StoppedPage: public Page {

public:

	StoppedPage(LCD* l);

protected:

	void display();
};

#endif
