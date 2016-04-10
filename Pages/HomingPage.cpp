// The author disclaims copyright to this source code.
#include "HomingPage.h"

/**
 * PAGE HOMING
 *
 * <code>
 * &nbsp;&nbsp;012345678901234567890<br>
 * 1&nbsp;STOP&nbsp;&nbsp;HOMING&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 4&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * </code>
 *
 * - stop: stop homing
 */
HomingPage::HomingPage(LCD* l, Actuator* a) :
		Page(l) {
	actuator = a;
}

void HomingPage::display() {
	Debug::getInstance()->info("HomingPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  HOMING        ");
	lcd->setCursor(0, 1);
	lcd->print("                    ");
	lcd->setCursor(0, 2);
	lcd->print("                    ");
	lcd->setCursor(0, 3);
	lcd->print("                    ");
}
