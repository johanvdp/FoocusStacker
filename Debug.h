// The author disclaims copyright to this source code.
#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "Domain.h"

class Debug {

public:
	static Debug* createInstance(Configuration* configuration);
	static Debug* getInstance();

	void setup();

	void info(String info);
	void error(String error);

private:
	static Debug* instance;

	Configuration* configuration;

	Debug();
	virtual ~Debug();
};

#endif
