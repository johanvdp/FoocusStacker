// The author disclaims copyright to this source code.
#include "InformationPage.h"

// =========================================================
// PAGE INFO
// =========================================================
//   012345678901234567890
// 1 STOP  INFO       NEXT
// 2 item name
// 3 item value
// 4 item unit
//
// stop: stop info
// next: next item
//
// item name: 20 characters
// item value: 20 characters
// item unit: 20 characters
//
InformationPage::InformationPage(LCD* l, Information* i) :
		Page(l) {
	info = i;
}

// 20 characters
String InformationPage::toInfoItemName() {
	return toFixed(info->getCurrentItemName(), 20);
}

String InformationPage::toInfoItemUnit() {
	return toFixed(info->getCurrentItemUnit(), 20);
}

String InformationPage::toInfoItemValue() {
	return toFixed(String(info->getCurrentItemValue()), 20);
}

void InformationPage::display() {
	Debug::getInstance()->info("InformationPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  INFO      NEXT");
	lcd->setCursor(0, 1);
	lcd->print(toInfoItemName());
	lcd->setCursor(0, 2);
	lcd->print(toInfoItemValue());
	lcd->setCursor(0, 3);
	lcd->print(toInfoItemUnit());
}

