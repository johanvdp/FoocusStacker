// The author disclaims copyright to this source code.
#ifndef DEBUG_H
#define DEBUG_H

// forward declaration
class DebugConfiguration;

#include <Arduino.h>
#include "Configuration.h"
#include "Clock.h"

class Debug: public Configurable {

public:
	static Debug* createInstance(Clock* clock);
	static Debug* getInstance();

	void setup();

	void debug(String info);
	void info(String info);
	void error(String error);

	Configuration* getConfiguration();

private:
	static Debug* instance;
	static const String zeroTemplate;

	Clock* clock;
	DebugConfiguration* configuration;
	unsigned long previousTimestamp;

	Debug(Clock* clock);
	virtual ~Debug();
	String timestamps();
	String fixedLength(unsigned long number);
};

class DebugConfiguration: public AbstractConfiguration {

public:

	DebugConfiguration();
	virtual ~DebugConfiguration();

	boolean isDebugErrorEnabled();
	boolean isDebugInfoEnabled();
	boolean isDebugDebugEnabled();

protected:

	virtual const int getItemCount();
	virtual const String* getItemNames();
	virtual const String* getItemUnits();
	virtual long* getItemValues();
	virtual const long* getItemValuesMin();
	virtual const long* getItemValuesMax();

private:

	static const int ITEM_DEBUG_ERRORS_ENABLED = 0;
	static const int ITEM_DEBUG_INFO_ENABLED = 1;
	static const int ITEM_DEBUG_DEBUG_ENABLED = 2;
	static const int ITEM_COUNT = 3;

	long itemValues[ITEM_COUNT] = { 1, 1, 0 };
};

#endif
