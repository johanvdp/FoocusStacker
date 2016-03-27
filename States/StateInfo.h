// The author disclaims copyright to this source code.
#ifndef STATEINFO_H
#define STATEINFO_H

// forward declaration of type
class StateInfo;

#include "StateMachine.h"
#include "../Powersupply.h"

class StateInfo: public State {

public:

	StateInfo(Clock* clk, StateMachine* s, Buttons* b, Page* p, Information* i, Powersupply* psu);
	virtual ~StateInfo();

	void setup();
	void read();
	void process();

private:

	static const int INFO_STOP = 3;
	static const int INFO_NEXT = 4;

	Information* info;
	Powersupply* powersupply;
};
#endif
