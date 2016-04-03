// The author disclaims copyright to this source code.
#include "PlaybackPage.h"

// =========================================================
// PAGE PLAYBACK
// =========================================================
//   012345678901234567890
// 1 STOP  PLAYBACK
// 2       002~000000
// 3      >003~000000
// 4       004~000000
//
// stop: stop playback
//
// 002~000000: step number, optional minus sign and actuator position
//
PlaybackPage::PlaybackPage(LCD* l, Recording* r) :
		RecordPage(l, r) {
}

void PlaybackPage::display() {
	Debug::getInstance()->info("PlaybackPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  PLAYBACK      ");
	lcd->setCursor(0, 1);
	lcd->print("      " + toStepPrevious() + "    ");
	lcd->setCursor(0, 2);
	lcd->print("     >" + toStepCurrent() + "    ");
	lcd->setCursor(0, 3);
	lcd->print("      " + toStepNext() + "    ");
}
