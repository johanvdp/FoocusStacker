// The author disclaims copyright to this source code.
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <LCD.h>
#include "../Component.h"
#include "../Buttons.h"
#include "../Pages/Page.h"
#include "../Pages/StoppedPage.h"
#include "../Pages/HomingPage.h"
#include "../Pages/ManualPage.h"
#include "../Pages/RecordPage.h"
#include "../Pages/PlaybackPage.h"
#include "../Pages/ConfigurationPage.h"
#include "../Pages/InformationPage.h"
#include "../Actuator.h"
#include "../Domain.h"
#include "State.h"
#include "StateStopped.h"
#include "StateHoming.h"
#include "StateManual.h"
#include "StateRecord.h"
#include "StatePlayback.h"
#include "StateInfo.h"
#include "StateConfiguration.h"
#include "../Statistics.h"
#include "../Powersupply.h"

class StateMachine: public FullProcess {

public:

	StateMachine(Clock* clk, Buttons* b, LCD* l, Actuator* a, Camera* cam, Configuration* c,
			Recording* r, Information* i, Powersupply* psu);
	virtual ~StateMachine();

	void setup();
	void read();
	void process();
	void write();

	void stateGotoStopped();
	void stateGotoHoming();
	void stateGotoManual();
	void stateGotoRecord();
	void stateGotoPlayback();
	void stateGotoConfiguration();
	void stateGotoInfo();

	Statistics* getPlaybackStatistics();

private:

	State* current;
	StateConfiguration* configuration;
	StateStopped* stopped;
	StateHoming* homing;
	StateManual* manual;
	StateRecord* record;
	StatePlayback* playback;
	StateInfo* info;

	void gotoState(State* state);
};

#endif
