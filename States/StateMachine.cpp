// The author disclaims copyright to this source code.
#include "StateMachine.h"

StateMachine::StateMachine(Clock* clk, Buttons* b, LCD* l, Actuator* a,
		Configuration* c, Recording* r, Information* i) {

	StoppedPage* stoppedPage = new StoppedPage(l);
	HomingPage* homingPage = new HomingPage(l, a);
	ManualPage* manualPage = new ManualPage(l, a);
	RecordPage* recordPage = new RecordPage(l, r, c);
	PlaybackPage* playbackPage = new PlaybackPage(l, r, c);
	ConfigurationPage* configurationPage = new ConfigurationPage(l, c);
	InformationPage* informationPage = new InformationPage(l, i);

	stopped = new StateStopped(clk, this, b, stoppedPage);
	homing = new StateHoming(clk, this, b, homingPage, a);
	manual = new StateManual(clk, this, b, manualPage, a);
	record = new StateRecord(clk, this, b, recordPage, c, r);
	playback = new StatePlayback(clk, this, b, playbackPage, a, c, r);
	configuration = new StateConfiguration(clk, this, b, configurationPage, c);
	info = new StateInfo(clk, this, b, informationPage, i);

	current = stopped;
}

StateMachine::~StateMachine() {
}

void StateMachine::setup() {
	Debug::getInstance()->info("StateMachine::setup");
	current = stopped;
	current->setup();
}

void StateMachine::read() {
	current->read();
}

void StateMachine::process() {
	current->process();
}

void StateMachine::write() {
	current->write();
}

void StateMachine::stateGotoStopped() {
	Debug::getInstance()->info("StateMachine::stateGotoStopped");
	gotoState(stopped);
}

void StateMachine::stateGotoHoming() {
	Debug::getInstance()->info("StateMachine::stateGotoHoming");
	gotoState(homing);
}

void StateMachine::stateGotoManual() {
	Debug::getInstance()->info("StateMachine::stateGotoManual");
	gotoState(manual);
}

void StateMachine::stateGotoRecord() {
	Debug::getInstance()->info("StateMachine::stateGotoRecord");
	gotoState(record);
}

void StateMachine::stateGotoPlayback() {
	Debug::getInstance()->info("StateMachine::stateGotoPlayback");
	current = playback;
	gotoState(playback);
}

void StateMachine::stateGotoConfiguration() {
	Debug::getInstance()->info("StateMachine::stateGotoConfiguration");
	gotoState(configuration);
}

void StateMachine::stateGotoInfo() {
	Debug::getInstance()->info("StateMachine::stateGotoInfo");
	gotoState(info);
}

void StateMachine::gotoState(State* state) {
	current = state;
	current->setup();
}

Statistics* StateMachine::getPlaybackStatistics() {
	return playback->getStatistics();
}
