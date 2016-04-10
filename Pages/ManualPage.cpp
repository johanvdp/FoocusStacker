// The author disclaims copyright to this source code.
#include "ManualPage.h"

/**
 * PAGE MANUAL
 *
 * <code>
 * &nbsp;&nbsp;012345678901234567890<br>
 * 1&nbsp;STOP&nbsp;&nbsp;MANUAL&nbsp;&nbsp;&nbsp;&nbsp;CLICK<br>
 * 2&nbsp;&lt;&lt;&lt;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&gt;&gt;&gt;<br>
 * 3&nbsp;&lt;&lt;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~000000&nbsp;&nbsp;&nbsp;&gt;&gt;<br>
 * 4&nbsp;&lt;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&gt;<br>
 * </code>
 *
 * - stop : stop manual control
 * - &lt;&lt;&lt;  : move down faster
 * - &lt;&lt;   : move down fast
 * - &lt;    : move down
 * - &gt;    : move up
 * - &gt;&gt;   : move up fast
 * - &gt;&gt;&gt;  : move up faster
 * - click: camera click
 *
 * - 000000: optional minus sign and actuator position
 */
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
