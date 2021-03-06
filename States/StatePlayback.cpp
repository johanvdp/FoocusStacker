// The author disclaims copyright to this source code.
#include "StatePlayback.h"

StatePlayback::StatePlayback(Clock* clk, StateMachine* s, Buttons* b, Page* p,
		Actuator* a, Camera* cam, Recording* r) :
		State(clk, s, b, p) {
	actuator = a;
	camera = cam;
	recording = r;
	playbackState = WAIT_FOR_CAMERA;
}

StatePlayback::~StatePlayback() {
}

void StatePlayback::setup() {

	Debug::getInstance()->debug("StatePlayback::setup");

	initialPosition = actuator->getPosition();

	// read configuration once
	stepIntervalMs = recording->getStepIntervalMs();
	// count back number of iterations
	iteration = recording->getIterations();

	// start playback at beginning of record
	recording->resetStepIndex();
	firstStep = true;
	click();
	playbackState = WAIT_FOR_CAMERA;

	State::setup();
}

void StatePlayback::process() {
	State::process();

	if (buttons->isPressed(PLAYBACK_STOP)) {
		stateMachine->stateGotoStopped();
	} else if (playbackState == WAIT_FOR_CAMERA && camera->isReady()) {
		if (firstStep) {
			firstStep = false;
			Debug::getInstance()->info("StatePlayback::process first step");
			actuator->gotoPosition(
					actuator->getPosition()
							+ recording->getCurrentStepPosition());
			playbackState = WAIT_FOR_ACTUATOR;
		} else {
			boolean hasNext = recording->nextStepIndex();
			if (hasNext) {
				// goto next step
				Debug::getInstance()->info("StatePlayback::process next step");
				actuator->gotoPosition(
						actuator->getPosition()
								+ recording->getCurrentStepPosition());
				playbackState = WAIT_FOR_ACTUATOR;
			} else {
				// end of steps
				if (iteration > 1) {
					// next iteration
					Debug::getInstance()->info(
							"StatePlayback::process next iteration");
					iteration--;
					// start playback at beginning of record
					recording->resetStepIndex();
					firstStep = false;
					actuator->gotoPosition(
							actuator->getPosition()
									+ recording->getCurrentStepPosition());
					playbackState = WAIT_FOR_ACTUATOR;
				} else {
					// return to initial position
					Debug::getInstance()->info("StatePlayback::process return");
					iteration--;
					actuator->gotoPosition(initialPosition);
					playbackState = WAIT_FOR_ACTUATOR;
				}
			}
			page->update();
		}
	} else if (playbackState == WAIT_FOR_ACTUATOR && actuator->isStopped()) {
		if (iteration > 0) {
			click();
			playbackState = WAIT_FOR_CAMERA;
		} else {
			stateMachine->stateGotoStopped();
		}
	}
}

int StatePlayback::getIteration() {
	return iteration;
}

void StatePlayback::click() {
	delay(stepIntervalMs);
	page->blink();
	camera->click();
}

