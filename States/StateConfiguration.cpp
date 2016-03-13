// The author disclaims copyright to this source code.
#include "StateConfiguration.h"

StateConfiguration::StateConfiguration(Clock* clk, StateMachine* s, Buttons* b,
		Page* p, Configuration* c) :
		State(clk, s, b, p) {
	configuration = c;
}

StateConfiguration::~StateConfiguration() {
}

void StateConfiguration::process() {
	State::process();

	if (buttons->isPressed(CONFIGURE_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (buttons->isPressed(CONFIGURE_PREV)) {
		configuration->previousItemIndex();
		page->update();
	} else if (buttons->isPressed(CONFIGURE_NEXT)) {
		configuration->nextItemIndex();
		page->update();
	} else if (buttons->isPressed(CONFIGURE_DOWN)) {
		configuration->changeCurrentItemValue(-1);
		page->update();
	} else if (buttons->isActive(CONFIGURE_DOWN)) {
		changeItemValueSpinDown();
		page->update();
	} else if (buttons->isPressed(CONFIGURE_UP)) {
		configuration->changeCurrentItemValue(1);
		page->update();
	} else if (buttons->isActive(CONFIGURE_UP)) {
		changeItemValueSpinUp();
		page->update();
	}
}

void StateConfiguration::changeItemValueSpinDown() {
	unsigned long duration = buttons->getActiveDuration(CONFIGURE_DOWN);
	if (duration > 3000) {
		configuration->changeCurrentItemValue(-1000);
	} else if (duration > 2000) {
		configuration->changeCurrentItemValue(-100);
	} else if (duration > 1000) {
		configuration->changeCurrentItemValue(-10);
	} else if (duration > 100) {
		configuration->changeCurrentItemValue(-1);
	}
}

void StateConfiguration::changeItemValueSpinUp() {
	unsigned long duration = buttons->getActiveDuration(CONFIGURE_UP);
	if (duration > 3000) {
		configuration->changeCurrentItemValue(1000);
	} else if (duration > 2000) {
		configuration->changeCurrentItemValue(100);
	} else if (duration > 1000) {
		configuration->changeCurrentItemValue(10);
	} else if (duration > 100) {
		configuration->changeCurrentItemValue(1);
	}
}

