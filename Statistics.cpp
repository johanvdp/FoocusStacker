// The author disclaims copyright to this source code.
#include "Statistics.h"

Statistics::Statistics() {
	minimum = 0;
	maximum = 0;
	average = 0;
}

Statistics::~Statistics() {
}

void Statistics::setup() {
	Debug::getInstance()->debug("Statistics::setup");
}

void Statistics::add(float newSample) {
	needRecalculation = true;

	// ring buffer
	samples[index] = newSample;
	index++;
	if (index >= NUMBER_OF_SAMPLES) {
		index = 0;
	}
}

void Statistics::recalculate() {
	Debug::getInstance()->debug("Statistics::recalculate");
	float sum = 0;
	minimum = samples[0];
	maximum = samples[0];
	for (int i = 1; i < NUMBER_OF_SAMPLES; i++) {
		long sample = samples[i];
		if (sample < minimum) {
			minimum = sample;
		}
		if (sample > maximum) {
			maximum = sample;
		}
		sum += sample;
	}
	average = sum / NUMBER_OF_SAMPLES;
	needRecalculation = false;
}

float Statistics::getAverage() {
	if (needRecalculation) {
		recalculate();
	}
	return average;
}

float Statistics::getMinimum() {
	if (needRecalculation) {
		recalculate();
	}
	return minimum;
}

float Statistics::getMaximum() {
	if (needRecalculation) {
		recalculate();
	}
	return maximum;
}

