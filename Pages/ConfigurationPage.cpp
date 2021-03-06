// The author disclaims copyright to this source code.
#include "ConfigurationPage.h"

/**
 * PAGE CONFIGURE
 *
 * <code>
 * &nbsp;&nbsp;012345678901234567890<br>
 * 1&nbsp;STOP&nbsp;&nbsp;CONFIGURE&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 2&nbsp;PREV&nbsp;>item name&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 3&nbsp;NEXT&nbsp;&nbsp;item&nbsp;value&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 4&nbsp;DOWN&nbsp;&nbsp;item&nbsp;unit&nbsp;&nbsp;&nbsp;&nbsp;UP<br>
 * </code>
 *
 * - stop: stop configure
 * - prev: select previous item
 * - next: select next item
 * - down: change item value down
 * - up  : change item value up
 *
 * - item name: 14 characters
 * - item value: 14 characters
 * - item unit: 12 characters
 */
ConfigurationPage::ConfigurationPage(LCD* l, Configuration* c) :
		Page(l) {
	configuration = c;
}

// 14 characters
String ConfigurationPage::toConfigurationItemName() {
	return toFixed(configuration->getCurrentItemName(), 14);
}

// 14 characters
String ConfigurationPage::toConfigurationItemValue() {
	return toFixed(String(configuration->getCurrentItemValue()), 14);
}

// 12 characters
String ConfigurationPage::toConfigurationItemUnit() {
	return toFixed(configuration->getCurrentItemUnit(), 12);
}

void ConfigurationPage::display() {
	Debug::getInstance()->info("ConfigurationPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  CONFIGURE     ");
	lcd->setCursor(0, 1);
	lcd->print("PREV >" + toConfigurationItemName());
	lcd->setCursor(0, 2);
	lcd->print("NEXT  " + toConfigurationItemValue());
	lcd->setCursor(0, 3);
	lcd->print("DOWN  " + toConfigurationItemUnit() + "UP");
}
