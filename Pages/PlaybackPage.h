// The author disclaims copyright to this source code.
#ifndef PLAYBACKPAGE_H
#define PLAYBACKPAGE_H

// forward declaration
class StatePlayback;

#include <Arduino.h>
#include <LCD.h>
#include "RecordPage.h"
#include "../Domain.h"

class PlaybackPage: public RecordPage {

public:

	PlaybackPage(LCD* l, Recording* r);
	void setStatePlayback(StatePlayback* p);

protected:

	void display();

private:

	String toProgress();

	StatePlayback* statePlayback;
};

#endif
