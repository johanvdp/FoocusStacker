// The author disclaims copyright to this source code.
#ifndef STATEHOMING_H
#define STATEHOMING_H

// forward declaration of type
class StateHoming;

#include "StateMachine.h"
#include "../Actuator.h"

class StateHoming: public State {

public:

	StateHoming(Clock* clk, StateMachine* s, Buttons* b, Page* p, Actuator* a);
	virtual ~StateHoming();

	void read();
	void process();
	void write();

private:

	static const int HOMING_STOP = 3;

	Actuator* actuator;
};
#endif
