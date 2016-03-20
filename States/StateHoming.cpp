// The author disclaims copyright to this source code.
#include "StateHoming.h"

StateHoming::StateHoming(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a) :
		State(clk, s, b, p) {
	actuator = a;
}

StateHoming::~StateHoming() {
}

void StateHoming::setup() {
	Debug::getInstance()->info("StateHoming::setup");
	actuator->gotoHome();
}

void StateHoming::process() {
	State::process();

	if (buttons->isPressed(HOMING_STOP)) {
		actuator->stop();
		stateMachine->stateGotoStopped();
	} else if (actuator->isLimitDown()) {
		stateMachine->stateGotoStopped();
	}
}
