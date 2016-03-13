// The author disclaims copyright to this source code.
#ifndef STATECONFIGURATION_H
#define STATECONFIGURATION_H

// forward declaration of type
class StateConfiguration;

#include "StateMachine.h"

class StateConfiguration: public State {

public:

	StateConfiguration(Clock* clk, StateMachine* s, Buttons* b, Page* p,
			Configuration* c);
	virtual ~StateConfiguration();

	void process();

private:

	static const int CONFIGURE_DOWN = 0;
	static const int CONFIGURE_NEXT = 1;
	static const int CONFIGURE_PREV = 2;
	static const int CONFIGURE_STOP = 3;
	static const int CONFIGURE_UP = 4;

	void changeItemValueSpinDown();
	void changeItemValueSpinUp();

	Configuration* configuration;
};
#endif
