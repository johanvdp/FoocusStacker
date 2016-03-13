// The author disclaims copyright to this source code.
#ifndef STATERECORD_H
#define STATERECORD_H

// forward declaration of type
class StateRecord;

#include "StateMachine.h"

class StateRecord: public State {

public:

	StateRecord(Clock* clk, StateMachine* s, Buttons* b, Page* p,
			Configuration* c, Recording* r);
	virtual ~StateRecord();

	void process();

private:

	static const int RECORD_DOWN = 0;
	static const int RECORD_NEXT = 1;
	static const int RECORD_PREV = 2;
	static const int RECORD_STOP = 3;
	static const int RECORD_UP = 4;
	static const int RECORD_CLR = 7;

	void spinDown();
	void spinUp();

	Configuration* configuration;
	Recording* recording;
};

#endif
