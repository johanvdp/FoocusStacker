// The author disclaims copyright to this source code.
#include "StateMachine.h"

StateMachine::StateMachine(Clock* clk, Buttons* b, LCD* l, Actuator* a,
		Camera* cam, Recording* r, Information* i, Powersupply* psu) {

	StoppedPage* stoppedPage = new StoppedPage(l);
	HomingPage* homingPage = new HomingPage(l, a);
	ManualPage* manualPage = new ManualPage(l, a);
	RecordPage* recordPage = new RecordPage(l, r);
	PlaybackPage* playbackPage = new PlaybackPage(l, r);
	AbstractConfiguration* recordingConfiguration =
			(AbstractConfiguration*) r->getConfiguration();
	AbstractConfiguration* cameraConfiguration =
			(AbstractConfiguration*) cam->getConfiguration();
	AbstractConfiguration* actuatorConfiguration =
			(AbstractConfiguration*) a->getConfiguration();
	AbstractConfiguration* debugConfiguration =
			(AbstractConfiguration*) Debug::getInstance()->getConfiguration();
	CompositeConfiguration* compositeConfiguration = new CompositeConfiguration(
			recordingConfiguration, cameraConfiguration, actuatorConfiguration,
			debugConfiguration);
	ConfigurationPage* configurationPage = new ConfigurationPage(l,
			compositeConfiguration);
	InformationPage* informationPage = new InformationPage(l, i);

	stopped = new StateStopped(clk, this, b, stoppedPage);
	homing = new StateHoming(clk, this, b, homingPage, a);
	manual = new StateManual(clk, this, b, manualPage, a, cam);
	record = new StateRecord(clk, this, b, recordPage, r);
	playback = new StatePlayback(clk, this, b, playbackPage, a, cam, r);
	playbackPage->setStatePlayback(playback);
	configuration = new StateConfiguration(clk, this, b, configurationPage,
			compositeConfiguration);
	info = new StateInfo(clk, this, b, informationPage, i, psu);

	current = stopped;
}

StateMachine::~StateMachine() {
}

void StateMachine::setup() {
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
	gotoState(stopped);
}

void StateMachine::stateGotoHoming() {
	gotoState(homing);
}

void StateMachine::stateGotoManual() {
	gotoState(manual);
}

void StateMachine::stateGotoRecord() {
	gotoState(record);
}

void StateMachine::stateGotoPlayback() {
	current = playback;
	gotoState(playback);
}

void StateMachine::stateGotoConfiguration() {
	gotoState(configuration);
}

void StateMachine::stateGotoInfo() {
	gotoState(info);
}

void StateMachine::gotoState(State* state) {
	current = state;
	current->setup();
}

Statistics* StateMachine::getPlaybackStatistics() {
	return playback->getStatistics();
}
