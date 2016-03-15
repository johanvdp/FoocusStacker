// The author disclaims copyright to this source code.
#ifndef STATEMANUAL_H
#define STATEMANUAL_H

// forward declaration of type
class StateManual;

#include "StateMachine.h"
#include "../Camera.h"

class StateManual: public State {

public:

	StateManual(Clock* clk, StateMachine* s, Buttons* b, Page* p, Actuator* a, Camera* cam);
	virtual ~StateManual();

	void setup();
	void read();
	void process();
	void write();

private:

	static const int MANUAL_DOWN = 0;
	static const int MANUAL_DOWN_FAST = 1;
	static const int MANUAL_DOWN_FASTER = 2;
	static const int MANUAL_STOP = 3;
	static const int MANUAL_UP = 4;
	static const int MANUAL_UP_FAST = 5;
	static const int MANUAL_UP_FASTER = 6;
	static const int MANUAL_CLICK = 7;

	Actuator* actuator;
	Camera* camera;
	boolean displayUpdateRequired;
};
#endif
