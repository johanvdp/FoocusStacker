// The author disclaims copyright to this source code.
#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "Domain.h"
#include "Clock.h"

class Debug {

public:
	static Debug* createInstance(Clock* clock, Configuration* configuration);
	static Debug* getInstance();

	void setup();

	void info(String info);
	void error(String error);

private:
	static Debug* instance;
	static const String zeroTemplate;

	Clock* clock;
	Configuration* configuration;
	unsigned long previousTimestamp;

	Debug();
	virtual ~Debug();
	String timestamps();
	String fixedLength(unsigned long number);
};

#endif
