// The author disclaims copyright to this source code.
#ifndef STATE_H
#define STATE_H

// forward declarations
class Clock;
class StateMachine;
class Buttons;
class Page;

#include "../Component.h"
#include "../Statistics.h"

class State: public FullProcess {

public:

	State(Clock* clk, StateMachine* s, Buttons* b, Page* p);
	virtual ~State();

	void setup();
	void read();
	void process();
	void write();

	Statistics* getStatistics();

protected:

	Clock* clock;
	StateMachine* stateMachine;
	Buttons* buttons;
	Page* page;

	Statistics* statistics;
	unsigned long lastProcessTimestamp;

	void resetProcessStatistics();
	void updateProcessStatistics();
};

#endif
