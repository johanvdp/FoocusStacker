// The author disclaims copyright to this source code.
#ifndef STOPPEDPAGE_H_
#define STOPPEDPAGE_H_

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
