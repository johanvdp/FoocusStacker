// The author disclaims copyright to this source code.
#ifndef RECORDPAGE_H_
#define RECORDPAGE_H_

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"
#include "../Domain.h"

class RecordPage: public Page {

public:

	RecordPage(LCD* l, Recording* r, Configuration* c);

protected:

	void display();
	String toStepPrevious();
	String toStepCurrent();
	String toStepNext();

	Recording* recording;
	Configuration* configuration;
};

#endif
