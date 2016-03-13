// The author disclaims copyright to this source code.
#include "StateManual.h"

StateManual::StateManual(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a) :
		State(clk, s, b, p) {
	actuator = a;
	displayUpdateRequired = true;
}

StateManual::~StateManual() {
}

void StateManual::read() {
	State::read();

	actuator->read();
}

void StateManual::process() {
	State::process();

	if (buttons->isPressed(MANUAL_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (buttons->isActive(MANUAL_DOWN)) {
		if (actuator->isLimitDown()) {
			// can not step reverse, down limit reached
			page->blink();
		} else {
			actuator->requestDown();
			displayUpdateRequired = true;
		}
	} else if (buttons->isActive(MANUAL_UP)) {
		if (actuator->isLimitUp()) {
			// can not step forward, up limit reached
			page->blink();
		} else {
			actuator->requestUp();
			displayUpdateRequired = true;
		}
	} else if (buttons->isPressed(MANUAL_CLICK)) {
		page->blink();
	} else if (displayUpdateRequired) {
		displayUpdateRequired = false;
		page->update();
	}
	actuator->process();
}

void StateManual::write() {
	actuator->write();

	State::write();
}

