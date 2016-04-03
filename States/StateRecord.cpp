// The author disclaims copyright to this source code.
#include "StateRecord.h"

StateRecord::StateRecord(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Recording* r) :
		State(clk, s, b, p) {
	recording = r;
}

StateRecord::~StateRecord() {
}

void StateRecord::spinDown() {
	unsigned long duration = buttons->getActiveDuration(RECORD_DOWN);
	if (duration > 3000) {
		recording->changeCurrentStepPosition(-1000);
	} else if (duration > 2000) {
		recording->changeCurrentStepPosition(-100);
	} else if (duration > 1000) {
		recording->changeCurrentStepPosition(-10);
	} else if (duration > 100) {
		recording->changeCurrentStepPosition(-1);
	}
}

void StateRecord::spinUp() {
	unsigned long duration = buttons->getActiveDuration(RECORD_UP);
	if (duration > 3000) {
		recording->changeCurrentStepPosition(1000);
	} else if (duration > 2000) {
		recording->changeCurrentStepPosition(100);
	} else if (duration > 1000) {
		recording->changeCurrentStepPosition(10);
	} else if (duration > 100) {
		recording->changeCurrentStepPosition(1);
	}
}

void StateRecord::process() {
	State::process();

	if (buttons->isPressed(RECORD_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (buttons->isPressed(RECORD_PREV)) {
		recording->previousStepIndex();
		page->update();
	} else if (buttons->isPressed(RECORD_NEXT)) {
		recording->nextStepIndex();
		page->update();
	} else if (buttons->isPressed(RECORD_DOWN)) {
		recording->changeCurrentStepPosition(-1);
		page->update();
	} else if (buttons->isActive(RECORD_DOWN)) {
		spinDown();
		page->update();
	} else if (buttons->isPressed(RECORD_UP)) {
		recording->changeCurrentStepPosition(1);
		page->update();
	} else if (buttons->isActive(RECORD_UP)) {
		spinUp();
		page->update();
	} else if (buttons->isPressed(RECORD_CLR)) {
		recording->clearStepPositions();
		page->update();
	}
}
