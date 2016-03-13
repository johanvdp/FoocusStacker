// The author disclaims copyright to this source code.
#ifndef STATISTICS_H
#define STATISTICS_H

#include <Arduino.h>
#include "Component.h"
#include "Debug.h"

class Statistics: public Component {

public:

	Statistics();
	virtual ~Statistics();

	void setup();

	void add(float sample);
	float getAverage();
	float getMinimum();
	float getMaximum();

private:

	void recalculate();

	static const int NUMBER_OF_SAMPLES = 100;

	float samples[NUMBER_OF_SAMPLES];
	int index = 0;
	boolean needRecalculation = true;
	float average;
	float minimum;
	float maximum;
};
#endif
