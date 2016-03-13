// The author disclaims copyright to this source code.
#ifndef STATEINFO_H
#define STATEINFO_H

// forward declaration of type
class StateInfo;

#include "StateMachine.h"

class StateInfo: public State {

public:

	StateInfo(Clock* clk, StateMachine* s, Buttons* b, Page* p, Information* i);
	virtual ~StateInfo();

	void setup();
	void process();

private:

	static const int INFO_STOP = 3;
	static const int INFO_NEXT = 7;

	Information* info;
};
#endif
