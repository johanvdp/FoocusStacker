// The author disclaims copyright to this source code.
#ifndef STATEMANUAL_H
#define STATEMANUAL_H

// forward declaration of type
class StateManual;

#include "StateMachine.h"

class StateManual: public State {

public:

	StateManual(Clock* clk, StateMachine* s, Buttons* b, Page* p, Actuator* a);
	virtual ~StateManual();

	void read();
	void process();
	void write();

private:

	static const int MANUAL_DOWN = 0;
	static const int MANUAL_STOP = 3;
	static const int MANUAL_UP = 4;
	static const int MANUAL_CLICK = 7;

	Actuator* actuator;
	boolean displayUpdateRequired;
};
#endif
