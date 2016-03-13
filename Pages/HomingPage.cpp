// The author disclaims copyright to this source code.
#include "HomingPage.h"

// =========================================================
// PAGE HOMING
// =========================================================
//   012345678901234567890
// 1 STOP  HOMING
// 2
// 3
// 4
//
// stop: stop homing
//
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
