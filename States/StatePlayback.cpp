// The author disclaims copyright to this source code.
#include "StatePlayback.h"

StatePlayback::StatePlayback(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a, Configuration* c, Recording* r) :
		State(clk, s, b, p) {
	actuator = a;
	configuration = c;
	recording = r;
}

StatePlayback::~StatePlayback() {
}

void StatePlayback::setup() {

	Debug::getInstance()->info("StatePlayback::setup");

	// start playback at beginning of record
	recording->resetStepIndex();

	initialPosition = actuator->getPosition();
	targetPosition = initialPosition;

	// read configuration once
	stepCount = configuration->getStepCount();
	stepIntervalMs = configuration->getStepIntervalMs();
	clickCount = configuration->getClickCount();
	clickIntervalMs = configuration->getClickIntervalMs();
	iterations = configuration->getIterations();
	Debug::getInstance()->info("StatePlayback::setup stepCount:" + String(stepCount));
	Debug::getInstance()->info(
			"StatePlayback::setup stepIntervalMs:" + String(stepIntervalMs));
	Debug::getInstance()->info("StatePlayback::setup clickCount:" + String(clickCount));
	Debug::getInstance()->info(
			"StatePlayback::setup clickIntervalMs:" + String(clickIntervalMs));
	Debug::getInstance()->info("StatePlayback::setup iterations:" + String(iterations));

	// start at initial position
	clicks();
	targetPosition = initialPosition + recording->getCurrentStepPosition();
	Debug::getInstance()->info("StatePlayback::setup target:" + String(targetPosition));

	State::setup();
}

void StatePlayback::read() {
	State::read();

	actuator->read();
}

void StatePlayback::process() {
	State::process();

	if (buttons->isPressed(PLAYBACK_STOP)) {
		stateMachine->stateGotoStopped();
	} else {
		long actualPosition = actuator->getPosition();
		if (actualPosition < targetPosition) {
			targetForward();
		} else if (actualPosition > targetPosition) {
			targetReverse();
		} else {
			if (iterations > 0) {
				targetReached();
			} else {
				// finished
				stateMachine->stateGotoStopped();
			}
		}
	}

	actuator->process();
}

void StatePlayback::write() {
	actuator->write();

	State::write();
}

void StatePlayback::targetForward() {
	if (actuator->isLimitUp()) {
		// no limits should be hit during playback
		Debug::getInstance()->error("StatePlayback::targetForward limit hit");
		stateMachine->stateGotoStopped();
	} else {
		actuator->requestUp();
	}
}

void StatePlayback::targetReverse() {
	if (actuator->isLimitDown()) {
		// no limits should be hit during playback
		Debug::getInstance()->error("StatePlayback::targetReverse limit hit");
		stateMachine->stateGotoStopped();
	} else {
		actuator->requestDown();
	}
}

void StatePlayback::clicks() {
	Debug::getInstance()->info("StatePlayback::clicks");
	for (int i = 0; i < clickCount; i++) {
		page->blink();
		delay(clickIntervalMs);
	}
}


void StatePlayback::targetReached() {
	Debug::getInstance()->info("StatePlayback::targetReached");

	delay(stepIntervalMs);
	clicks();

	// progress to next step
	boolean success = recording->nextStepIndex();
	if (success) {
		// next step
		targetPosition = targetPosition + recording->getCurrentStepPosition();
	} else {
		// next iteration
		Debug::getInstance()->info(
				"StatePlayback::targetReached iteration:" + String(iterations));
		iterations--;

		if (iterations == 0) {
			// return to initial position if finished
			targetPosition = initialPosition;
		} else {
			// start playback at beginning of record
			recording->resetStepIndex();
			// continue relative movement
			targetPosition = targetPosition
					+ recording->getCurrentStepPosition();
		}
	}
	Debug::getInstance()->info(
			"StatePlayback::targetReached target:" + String(targetPosition));
	page->update();
}

