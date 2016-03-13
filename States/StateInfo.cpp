// The author disclaims copyright to this source code.
#include "StateInfo.h"

StateInfo::StateInfo(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Information* i) :
		State(clk, s, b, p) {
	info = i;
}

StateInfo::~StateInfo() {
}

void StateInfo::setup() {

	Debug::getInstance()->info("StateInfo::setup");

	info->setSupplyVoltageMilliV(10000);
	info->setSupplyCurrentMilliA(10);

	Statistics* statistics = stateMachine->getPlaybackStatistics();

	info->setStatisticsAverageMillis(statistics->getAverage());
	info->setStatisticsMinimumMillis(statistics->getMinimum());
	info->setStatisticsMaximumMillis(statistics->getMaximum());

	State::setup();
}

void StateInfo::process() {
	State::process();

	if (buttons->isPressed(INFO_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (buttons->isPressed(INFO_NEXT)) {
		info->nextItemIndex();
		page->update();
	}
}
