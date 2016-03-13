// The author disclaims copyright to this source code.
#ifndef INFORMATIONPAGE_H_
#define INFORMATIONPAGE_H_

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"
#include "../Domain.h"

class InformationPage: public Page {

public:

	InformationPage(LCD* l, Information* i);

protected:

	void display();
	String toInfoItemName();
	String toInfoItemUnit();
	String toInfoItemValue();

	Information* info;
};

#endif
