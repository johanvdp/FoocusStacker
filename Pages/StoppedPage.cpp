// The author disclaims copyright to this source code.
#include "StoppedPage.h"

// =========================================================
// PAGE STOPPED
// =========================================================
//   012345678901234567890
// 1       STOPPED  MANUAL
// 2 HOME           RECORD
// 3                  PLAY
// 4 INFO             CONF
//
// info  : display information
// home  : perform homing procedure
// manual: start manual control
// record: edit recording
// play  : playback recording
// conf  : edit configuration
//
StoppedPage::StoppedPage(LCD* l) :
		Page(l) {
}

void StoppedPage::display() {
	Debug::getInstance()->info("StoppedPage::display");
	lcd->setCursor(0, 0);
	lcd->print("      STOPPED MANUAL");
	lcd->setCursor(0, 1);
	lcd->print("HOME          RECORD");
	lcd->setCursor(0, 2);
	lcd->print("                PLAY");
	lcd->setCursor(0, 3);
	lcd->print("INFO            CONF");
}
