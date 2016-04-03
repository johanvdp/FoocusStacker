// The author disclaims copyright to this source code.
#include "RecordPage.h"

// =========================================================
// PAGE RECORD
// =========================================================
//   012345678901234567890
// 1 STOP  RECORD      CLR
// 2 PREV  002~000000
// 3 NEXT >003~000000
// 4 DOWN  004~000000   UP
//
// stop: stop recording
// prev: select previous step
// next: select next step
// clr : clear recording
// down: move down
// up  : move up
//
// 002~000000: step number, optional minus sign and actuator position
//
RecordPage::RecordPage(LCD* l, Recording* r) :
		Page(l) {
	recording = r;
}

// 10 characters
String RecordPage::toStepPrevious() {
	int recordStepPrevious = recording->getStepIndex() - 1;
	if (recordStepPrevious < 0) {
		return "          ";
	} else {
		String step = toZeroFixed(recordStepPrevious + 1, 3);
		String value = toZeroFixedSigned(
				recording->getStepPosition(recordStepPrevious), 7);
		return step + value;
	}
}

// 10 characters
String RecordPage::toStepCurrent() {
	int recordStepCurrent = recording->getStepIndex();
	String step = toZeroFixed(recordStepCurrent + 1, 3);
	String value = toZeroFixedSigned(
			recording->getStepPosition(recordStepCurrent), 7);
	return step + value;
}

// 10 characters
String RecordPage::toStepNext() {
	int recordStepNext = recording->getStepIndex() + 1;
	if (recordStepNext >= recording->getStepCount()) {
		return "          ";
	} else {
		String step = toZeroFixed(recordStepNext + 1, 3);
		String value = toZeroFixedSigned(
				recording->getStepPosition(recordStepNext), 7);
		return step + value;
	}
}

void RecordPage::display() {
	Debug::getInstance()->info("RecordPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  RECORD     CLR");
	lcd->setCursor(0, 1);
	lcd->print("PREV  " + toStepPrevious() + "    ");
	lcd->setCursor(0, 2);
	lcd->print("NEXT >" + toStepCurrent() + "    ");
	lcd->setCursor(0, 3);
	lcd->print("DOWN  " + toStepNext() + "  UP");
}
