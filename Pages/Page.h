// The author disclaims copyright to this source code.
#ifndef PAGE_H
#define PAGE_H

#include <Arduino.h>
#include <LCD.h>
#include "../Component.h"
#include "../Debug.h"

class Page: public Component, public Output {

public:

	Page(LCD* l);
	virtual ~Page();

	void setup();
	void write();

	void update();
	void blink();

protected:

	virtual void display() = 0;
	String toFixed(String text, int fixedLength);
	String toZeroFixed(long number, int fixedLength);
	String toZeroFixedSigned(long number, int fixedLength);

	LCD* lcd;
	boolean updateRequested;
	// LCD 20 character line
	static const String blankTemplate;
	static const String zeroTemplate;
};

#endif
