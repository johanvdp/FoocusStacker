// The author disclaims copyright to this source code.
#ifndef CONFIGURATIONPAGE_H
#define CONFIGURATIONPAGE_H

#include <Arduino.h>
#include <LCD.h>
#include "Page.h"
#include "../Domain.h"

class ConfigurationPage: public Page {

public:

	ConfigurationPage(LCD* l, Configuration* c);

protected:

	void display();
	String toConfigurationItemName();
	String toConfigurationItemValue();
	String toConfigurationItemUnit();

	Configuration* configuration;
};

#endif
