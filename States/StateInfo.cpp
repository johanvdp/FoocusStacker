// The author disclaims copyright to this source code.
#include "StateInfo.h"

StateInfo::StateInfo(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Information* i, Powersupply* psu) :
		State(clk, s, b, p) {
	info = i;
	powersupply = psu;
}

StateInfo::~StateInfo() {
}

void StateInfo::setup() {

	Debug::getInstance()->debug("StateInfo::setup");

	Statistics* statistics = stateMachine->getPlaybackStatistics();

	info->setStatisticsAverageMillis(statistics->getAverage());
	info->setStatisticsMinimumMillis(statistics->getMinimum());
	info->setStatisticsMaximumMillis(statistics->getMaximum());

	powersupply->setup();

	State::setup();
}

void StateInfo::read() {
	if (powersupply->isReady()) {
		int voltage = powersupply->getBusVoltage() * 1000;
		int current = powersupply->getShuntCurrent() * 1000;
		int power = powersupply->getBusPower() * 1000;

		info->setSupplyVoltageMilliV(voltage);
		info->setSupplyCurrentMilliA(current);
		info->setSupplyPowerMilliW(power);

		powersupply->startMeasurement();

		page->update();
	}
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
