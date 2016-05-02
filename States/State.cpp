// The author disclaims copyright to this source code.
#include "State.h"
#include "../Pages/Page.h"
#include "../Buttons.h"

State::State(Clock* clk, StateMachine* s, Buttons* b, Page* p) {
	clock = clk;
	stateMachine = s;
	buttons = b;
	page = p;

	statistics = new Statistics();
	lastProcessTimestamp = UINT32_MAX;
}

State::~State() {
}

void State::setup() {
	resetProcessStatistics();
	page->update();
}

void State::read() {
}

void State::process() {
	updateProcessStatistics();
}

void State::write() {
	page->write();
}

Statistics* State::getStatistics() {
	return statistics;
}

void State::resetProcessStatistics() {
	lastProcessTimestamp = UINT32_MAX;
}

void State::updateProcessStatistics() {
	unsigned long timestamp = clock->getTimestamp();
	if (lastProcessTimestamp == UINT32_MAX) {
		// first process occurrence
		lastProcessTimestamp = timestamp;

	} else {
		// update statistics with process interval
		unsigned long interval = timestamp - lastProcessTimestamp;
		lastProcessTimestamp = timestamp;
		statistics->add(interval);
	}
}
