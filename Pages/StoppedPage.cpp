// The author disclaims copyright to this source code.
#include "StoppedPage.h"

/**
 * PAGE STOPPED
 *
 * <code>
 * &nbsp;&nbsp;012345678901234567890<br>
 * 1&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;STOPPED&nbsp;&nbsp;MANUAL<br>
 * 2&nbsp;HOME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;RECORD<br>
 * 3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PLAY<br>
 * 4&nbsp;INFO&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;CONF<br>
 * </code>
 *
 * - info  : display information
 * - home  : perform homing procedure
 * - manual: start manual control
 * - record: edit recording
 * - play  : playback recording
 * - conf  : edit configuration
 */
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
