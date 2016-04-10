// The author disclaims copyright to this source code.
#include "PlaybackPage.h"

// included in implementation to avoid circular reference
#include "../States/StatePlayback.h"

/**
 * PAGE PLAYBACK
 *
 * <code>
 * &nbsp;&nbsp;012345678901234567890<br>
 * 1&nbsp;STOP&nbsp;&nbsp;PLAYBACK&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 2&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;0002/0005&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&gt;003~000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * 4&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;004~000000&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>
 * </code>
 *
 * - stop: stop playback
 *
 * - 0002/0005: progress, iteration of iterations
 * - 002~000000: step number, optional minus sign and actuator position
 */
PlaybackPage::PlaybackPage(LCD* l, Recording* r) :
		RecordPage(l, r) {
	statePlayback = NULL;
}

void PlaybackPage::setStatePlayback(StatePlayback* p) {
	statePlayback = p;
}

// 10 characters
String PlaybackPage::toProgress() {
	String iteration = toZeroFixed(statePlayback->getIteration(), 4);
	String iterations = toZeroFixed(recording->getIterations(), 4);
	return " " + iteration + "/" + iterations;
}

void PlaybackPage::display() {
	Debug::getInstance()->info("PlaybackPage::display");
	lcd->setCursor(0, 0);
	lcd->print("STOP  PLAYBACK      ");
	lcd->setCursor(0, 1);
	lcd->print("      " + toProgress() + "    ");
	lcd->setCursor(0, 2);
	lcd->print("     >" + toStepCurrent() + "    ");
	lcd->setCursor(0, 3);
	lcd->print("      " + toStepNext() + "    ");
}
