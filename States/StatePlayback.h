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

	StatePlayback(Clock* clk, StateMachine* s, Buttons* b, Page* p, Actuator* a, Camera* cam,
			Configuration* c, Recording* r);
	virtual ~StatePlayback();

	void setup();
	void read();
	void process();
	void write();

private:

	static const int PLAYBACK_STOP = 3;

	void clicks();
	void nextIteration();

	Actuator* actuator;
	Camera* camera;
	Configuration* configuration;
	Recording* recording;

	long stepCount = 0;
	long stepIntervalMs = 0;
	int clickCount = 0;
	long clickIntervalMs = 0;
	long iterations = 0;
	long initialPosition = 0;
};
#endif
