// The author disclaims copyright to this source code.
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>

class Configuration {

public:

	virtual ~Configuration() {};

	virtual String getCurrentItemName() = 0;
	virtual String getCurrentItemUnit() = 0;
	virtual long getCurrentItemValue() = 0;
	virtual void changeCurrentItemValue(long deltaValue) = 0;
	virtual void nextItemIndex() = 0;
	virtual void previousItemIndex() = 0;
};

class Configurable {

public:

	virtual ~Configurable() {};

	virtual Configuration* getConfiguration() = 0;
};

class AbstractConfiguration: public Configuration {

public:

	AbstractConfiguration();
	virtual ~AbstractConfiguration();

	String getCurrentItemName();
	String getCurrentItemUnit();
	long getCurrentItemValue();
	void changeCurrentItemValue(long deltaValue);
	void nextItemIndex();
	void previousItemIndex();
	void lastItemIndex();
	void firstItemIndex();

	virtual const int getItemCount() = 0;
	virtual const String* getItemNames() = 0;
	virtual const String* getItemUnits() = 0;
	virtual long* getItemValues() = 0;
	virtual const long* getItemValuesMin() = 0;
	virtual const long* getItemValuesMax() = 0;

private:

	int itemIndex;
};

class CompositeConfiguration: public Configuration {

public:

	CompositeConfiguration(AbstractConfiguration* c1, AbstractConfiguration* c2,
			AbstractConfiguration* c3, AbstractConfiguration* c4);
	virtual ~CompositeConfiguration();

	String getCurrentItemName();
	String getCurrentItemUnit();
	long getCurrentItemValue();
	void changeCurrentItemValue(long deltaValue);
	void nextItemIndex();
	void previousItemIndex();

private:
	AbstractConfiguration* configuration1;
	AbstractConfiguration* configuration2;
	AbstractConfiguration* configuration3;
	AbstractConfiguration* configuration4;
	AbstractConfiguration* currentConfiguration;
	int itemIndex;
};

#endif
