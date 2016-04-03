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

	virtual int getItemCount();
	virtual String* getItemNames();
	virtual String* getItemUnits();
	virtual long* getItemValues();
	virtual long* getItemValuesMin();
	virtual long* getItemValuesMax();

private:

	static const int DEBUG_CONFIGURATION_ITEM_DEBUG_ERRORS_ENABLED = 0;
	static const int DEBUG_CONFIGURATION_ITEM_DEBUG_INFO_ENABLED = 1;
	static const int DEBUG_CONFIGURATION_ITEM_DEBUG_DEBUG_ENABLED = 2;
	static const int DEBUG_CONFIGURATION_ITEM_COUNT = 3;

	String itemNames[DEBUG_CONFIGURATION_ITEM_COUNT] = {
	//
			"debug errors", "debug info", "debug debug" };
	String itemUnits[DEBUG_CONFIGURATION_ITEM_COUNT] = {
	//
			"0=no 1=yes", "0=no 1=yes", "0=no 1=yes" };
	long itemValues[DEBUG_CONFIGURATION_ITEM_COUNT] = {
	//
			1, 1, 0 };
	long itemValuesMin[DEBUG_CONFIGURATION_ITEM_COUNT] = {
	//
			0, 0, 0 };
	long itemValuesMax[DEBUG_CONFIGURATION_ITEM_COUNT] = {
	//
			1, 1, 1 };
};

#endif
