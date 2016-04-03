// The author disclaims copyright to this source code.
#ifndef PLAYBACKPAGE_H
#define PLAYBACKPAGE_H

#include <Arduino.h>
#include <LCD.h>
#include "RecordPage.h"
#include "../Domain.h"

class PlaybackPage: public RecordPage {

public:

	PlaybackPage(LCD* l, Recording* r);

protected:

	void display();
};

#endif
