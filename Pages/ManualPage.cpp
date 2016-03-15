// The author disclaims copyright to this source code.
#include "ManualPage.h"

// =========================================================
// PAGE MANUAL
// =========================================================
//   012345678901234567890
// 1 STOP  MANUAL    CLICK
// 2 <<<               >>>
// 3 <<       ~000000   >>
// 4 <                   >
//
// stop : stop manual control
// <<<  : move down faster
// <<   : move down fast
// <    : move down
// >    : move up
// >>   : move up fast
// >>>  : move up faster
// click: camera click
//
// 000000: optional minus sign and actuator position
//
ManualPage::ManualPage(LCD* l, Actuator* a) :
		Page(l) {
	actuator = a;
}

void ManualPage::display() {
	Debug::getInstance()->info("ManualPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  MANUAL   CLICK");
	lcd->setCursor(0, 1);
	lcd->print("<<<              >>>");
	lcd->setCursor(0, 2);
	lcd->print("<<       " + toZeroFixedSigned(actuator->getPosition(), 7)	+ "  >>");
	lcd->setCursor(0, 3);
	lcd->print("<                  >");
}
