// The author disclaims copyright to this source code.

#include "StateManual.h"

#include <cstdbool>

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

void StateManual::setup() {
	actuator->setup();
	camera->setup();

	State::setup();
}

void StateManual::read() {
	State::read();

	actuator->read();
}

void StateManual::process() {
	State::process();

	int delta = 0;
	if (buttons->isPressed(MANUAL_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (actuator->getState() == Actuator::State::STOPPED) {
		if (buttons->isActive(MANUAL_DOWN)) {
			delta = -1;
		} else if (buttons->isActive(MANUAL_DOWN_FAST)) {
			delta = -10;
		} else if (buttons->isActive(MANUAL_DOWN_FASTER)) {
			delta = -100;
		} else if (buttons->isActive(MANUAL_UP)) {
			delta = 1;
		} else if (buttons->isActive(MANUAL_UP_FAST)) {
			delta = 10;
		} else if (buttons->isActive(MANUAL_UP_FASTER)) {
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
				actuator->setTargetPosition(actuator->getPosition() + delta);
				displayUpdateRequired = true;
			}
		} else if (delta < 0) {
			if (actuator->isLimitDown()) {
				// can not step down, down limit reached
				page->blink();
			} else {
				actuator->setTargetPosition(actuator->getPosition() + delta);
				displayUpdateRequired = true;
			}
		}

	}

	actuator->process();

	if (displayUpdateRequired && actuator->getState() == Actuator::State::STOPPED) {
		displayUpdateRequired = false;
		page->update();
	}
}

void StateManual::write() {
	actuator->write();
	camera->write();

	State::write();
}
