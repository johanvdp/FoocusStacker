// The author disclaims copyright to this source code.
#ifndef PLAYBACKPAGE_H_
#define PLAYBACKPAGE_H_

#include <Arduino.h>
#include <LCD.h>
#include "RecordPage.h"
#include "../Domain.h"

class PlaybackPage: public RecordPage {

public:

	PlaybackPage(LCD* l, Recording* r, Configuration* c);

protected:

	void display();
};

#endif
