// The author disclaims copyright to this source code.
#ifndef STATEPLAYBACK_H
#define STATEPLAYBACK_H

// forward declaration of type
class StatePlayback;

#include "StateMachine.h"
#include "../Actuator.h"
#include "../Camera.h"
#include "../Domain.h"

class StatePlayback: public State {

public:
	enum PlaybackState {
		WAIT_FOR_CAMERA, WAIT_FOR_ACTUATOR
	};

	StatePlayback(Clock* clk, StateMachine* s, Buttons* b, Page* p, Actuator* a,
			Camera* cam, Recording* r);
	virtual ~StatePlayback();

	void setup();
	void process();

private:

	static const int PLAYBACK_STOP = 3;

	void click();
	void nextIteration();

	Actuator* actuator;
	Camera* camera;
	Recording* recording;

	PlaybackState playbackState;
	long stepIntervalMs = 0;
	long clickIntervalMs = 0;
	long iterations = 0;
	long initialPosition = 0;
	boolean firstStep = true;
};
#endif
