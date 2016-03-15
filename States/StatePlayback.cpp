// The author disclaims copyright to this source code.
#include "StatePlayback.h"

StatePlayback::StatePlayback(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a, Camera* cam, Configuration* c, Recording* r) :
		State(clk, s, b, p) {
	actuator = a;
	camera = cam;
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
	Debug::getInstance()->info(
			"StatePlayback::setup initialPosition:" + String(initialPosition));

	// read configuration once
	stepCount = configuration->getStepCount();
	stepIntervalMs = configuration->getStepIntervalMs();
	clickCount = configuration->getClickCount();
	clickIntervalMs = configuration->getClickIntervalMs();
	iterations = configuration->getIterations();
	Debug::getInstance()->info(
			"StatePlayback::setup stepCount:" + String(stepCount));
	Debug::getInstance()->info(
			"StatePlayback::setup stepIntervalMs:" + String(stepIntervalMs));
	Debug::getInstance()->info(
			"StatePlayback::setup clickCount:" + String(clickCount));
	Debug::getInstance()->info(
			"StatePlayback::setup clickIntervalMs:" + String(clickIntervalMs));
	Debug::getInstance()->info(
			"StatePlayback::setup iterations:" + String(iterations));

	actuator->setup();
	camera->setup();

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
	} else if (actuator->getState() == Actuator::State::STOPPED) {
		Debug::getInstance()->info(
				"StatePlayback::process iteration:" + String(iterations));
		if (iterations == configuration->getIterations()) {
			Debug::getInstance()->info("StatePlayback::process first");
			clicks();
			actuator->setTargetPosition(actuator->getPosition() + recording->getCurrentStepPosition());
			iterations--;
		} else if (iterations > 0) {
			Debug::getInstance()->info("StatePlayback::process next");
			delay(stepIntervalMs);
			clicks();
			recording->nextStepIndex();
			actuator->setTargetPosition(actuator->getPosition() + recording->getCurrentStepPosition());
			iterations--;
		} else if (iterations == 0) {
			Debug::getInstance()->info("StatePlayback::process last");
			clicks();
			actuator->setTargetPosition(initialPosition);
			iterations--;
		} else {
			// finished
			Debug::getInstance()->info("StatePlayback::process stopped");
			stateMachine->stateGotoStopped();
		}
	}

	actuator->process();
}

void StatePlayback::write() {
	actuator->write();
	camera->write();

	State::write();
}

void StatePlayback::clicks() {
	Debug::getInstance()->info("StatePlayback::clicks");
	for (int i = 0; i < clickCount; i++) {
		delay(clickIntervalMs);
		page->blink();
	}
}

