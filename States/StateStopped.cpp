// The author disclaims copyright to this source code.
#include "StateStopped.h"

StateStopped::StateStopped(Clock* clk, StateMachine* s, Buttons* b, Page* p) :
		State(clk, s, b, p) {
}

StateStopped::~StateStopped() {
}

void StateStopped::process() {
	State::process();

	if (buttons->isPressed(STOPPED_INFO)) {
		stateMachine->stateGotoInfo();
	} else if (buttons->isPressed(STOPPED_HOME)) {
		stateMachine->stateGotoHoming();
	} else if (buttons->isPressed(STOPPED_MANUAL)) {
		stateMachine->stateGotoManual();
	} else if (buttons->isPressed(STOPPED_RECORD)) {
		stateMachine->stateGotoRecord();
	} else if (buttons->isPressed(STOPPED_PLAY)) {
		stateMachine->stateGotoPlayback();
	} else if (buttons->isPressed(STOPPED_CONF)) {
		stateMachine->stateGotoConfiguration();
	}
}
