// The author disclaims copyright to this source code.
#ifndef RECORDPAGE_H
#define RECORDPAGE_H

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"
#include "../Recording.h"

class RecordPage: public Page {

public:

	RecordPage(LCD* l, Recording* r);

protected:

	void display();
	String toStepPrevious();
	String toStepCurrent();
	String toStepNext();

	Recording* recording;
};

#endif
