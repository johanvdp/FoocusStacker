// The author disclaims copyright to this source code.
#include "Page.h"

Page::Page(LCD* l) {
	lcd = l;
	updateRequested = false;
}

Page::~Page() {
}

void Page::setup() {
	Debug::getInstance()->info("Page::setup");
}

void Page::write() {
	if (updateRequested) {
		display();
		updateRequested = false;
	}
}

void Page::update() {
	updateRequested = true;
}

void Page::blink() {
	Debug::getInstance()->info("Page::blink");
	lcd->setBacklight(LOW);
	delay(10);
	lcd->setBacklight(HIGH);
}

// 20 character LCD
const String Page::blankTemplate = "                    ";
const String Page::zeroTemplate = "00000000000000000000";

//void Page::display() {
//	Debug::getInstance()->info("Page::display should be overriden");
//}

String Page::toFixed(String text, int fixedLength) {
	String maxed = text.substring(0, fixedLength);
	int padLength = fixedLength - maxed.length();
	String padding = blankTemplate.substring(0, padLength);
	String result = maxed + padding;
	return result;
}

String Page::toZeroFixed(long number, int fixedLength) {
	String text = String(number);
	String maxed = text.substring(0, fixedLength);
	int padLength = fixedLength - maxed.length();
	String padding = zeroTemplate.substring(0, padLength);
	String result = padding + maxed;
	return result;
}

String Page::toZeroFixedSigned(long number, int fixedLength) {
	String prefix = "+";
	if (number < 0) {
		prefix = "-";
		number = -number;
	}
	fixedLength--;
	String text = String(number);
	String maxed = text.substring(0, fixedLength);
	int padLength = fixedLength - maxed.length();
	String padding = zeroTemplate.substring(0, padLength);
	String result = prefix + padding + maxed;
	return result;
}
