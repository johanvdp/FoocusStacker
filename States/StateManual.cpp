// The author disclaims copyright to this source code.

#include "StateManual.h"

#include "../Actuator.h"
#include "../Buttons.h"
#include "../Pages/Page.h"

StateManual::StateManual(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a, Camera* cam) :
		State(clk, s, b, p) {
	actuator = a;
	camera = cam;
	displayUpdateRequired = true;
}

StateManual::~StateManual() {
}

void StateManual::process() {
	State::process();

	if (buttons->isPressed(MANUAL_STOP)) {
		stateMachine->stateGotoStopped();
		return;
	}

	int delta = 0;
	if (buttons->isPressed(MANUAL_DOWN) || buttons->getActiveDuration(MANUAL_DOWN) > 500) {
		delta = -1;
	} else if (buttons->isPressed(MANUAL_DOWN_FAST) || buttons->getActiveDuration(MANUAL_DOWN_FAST) > 500) {
		delta = -10;
	} else if (buttons->isPressed(MANUAL_DOWN_FASTER)|| buttons->getActiveDuration(MANUAL_DOWN_FASTER) > 500 ) {
		delta = -100;
	} else if (buttons->isPressed(MANUAL_UP) || buttons->getActiveDuration(MANUAL_UP) > 500) {
		delta = 1;
	} else if (buttons->isPressed(MANUAL_UP_FAST) || buttons->getActiveDuration(MANUAL_UP_FAST) > 500) {
		delta = 10;
	} else if (buttons->isPressed(MANUAL_UP_FASTER) || buttons->getActiveDuration(MANUAL_UP_FASTER) > 500) {
		delta = 100;
	} else if (buttons->isPressed(MANUAL_CLICK)) {
		camera->click();
		page->blink();
	}

	if (delta > 0) {
		if (actuator->isLimitUp()) {
			// can not step up, up limit reached
			page->blink();
		} else {
			displayUpdateRequired = true;
			actuator->gotoPosition(actuator->getPosition() + delta);
		}
	} else if (delta < 0) {
		if (actuator->isLimitDown()) {
			// can not step down, down limit reached
			page->blink();
		} else {
			displayUpdateRequired = true;
			actuator->gotoPosition(actuator->getPosition() + delta);
		}
	}

	// do not disturb running actuator with display updates
	if (displayUpdateRequired && actuator->isStopped()) {
		page->update();
		displayUpdateRequired = false;
	}
}
