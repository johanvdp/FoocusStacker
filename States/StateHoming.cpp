// The author disclaims copyright to this source code.
#include "StateHoming.h"
#include <limits>
StateHoming::StateHoming(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a) :
		State(clk, s, b, p) {
	actuator = a;
}

StateHoming::~StateHoming() {
}

void StateHoming::read() {
	State::read();

	actuator->read();
}

void StateHoming::process() {
	State::process();

	if (buttons->isPressed(HOMING_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (actuator->isLimitDown()) {
		// failed to step reverse, down limit reached
		stateMachine->stateGotoStopped();
	} else if (actuator->getState() == Actuator::State::STOPPED){
		actuator->setTargetPosition(std::numeric_limits<long>::min());
	}
	actuator->process();
}

void StateHoming::write() {
	actuator->write();

	State::write();
}
