// The author disclaims copyright to this source code.
#ifndef STATESTOPPED_H
#define STATESTOPPED_H

// forward declaration of type
class StateStopped;

#include "StateMachine.h"

class StateStopped: public State {

public:

	StateStopped(Clock* clk, StateMachine* s, Buttons* b, Page* p);
	virtual ~StateStopped();

	void process();

private:

	static const int STOPPED_INFO = 0;
	static const int STOPPED_HOME = 2;
	static const int STOPPED_CONF = 7;
	static const int STOPPED_PLAY = 6;
	static const int STOPPED_RECORD = 5;
	static const int STOPPED_MANUAL = 4;
};
#endif
