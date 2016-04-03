// The author disclaims copyright to this source code.
#ifndef FOOCUSSTACKER_H
#define FOOCUSSTACKER_H

// external libraries
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// project components
#include "Clock.h"
#include "Domain.h"
#include "Buttons.h"
#include "Actuator.h"
#include "Camera.h"
#include "Pages/Page.h"
#include "Statistics.h"
#include "States/StateMachine.h"
#include "Debug.h"

/**
 * The FoocusStacker application.
 * A singleton that is invoked by the Arduino setup and loop methods.
 *
 * D1mini edge connector
 * ---------------------
 *
 * pin   | label | ESP  | arduino | circuitry                             | function            |
 * :---: | :---: | :--: | :-----: | :------------------------------------ | :------------------ |
 * JP1.1 | 5V    |      |         | USB 5V                                |                     |
 * JP1.2 |  G    |      |         |                                       |                     |
 * JP1.3 | D4    | IO2  |      2  | pull-up 10k, I2C SCL, LED active low  | SCL                 |
 * JP1.4 | D3    | IO0  |      0  | pull-up 10k, I2C SDA                  | SDA                 |
 * JP1.5 | D2    | IO4  |      4  |                                       | ACTUATOR PULSE      |
 * JP1.6 | D1    | IO5  |      5  |                                       | ACTUATOR DIRECTION  |
 * JP1.7 | RX    |      |         |                                       |                     |
 * JP1.8 | TX    |      |         |                                       |                     |
 * JP2.1 | 3V3   |      |         |                                       |                     |
 * JP2.2 | D8    | IO15 |     15  | pull-down 10k                         | ACTUATOR ENABLE     |
 * JP2.3 | D7    | IO13 |     13  |                                       | CAMERA FOCUS        |
 * JP2.4 | D6    | IO12 |     12  |                                       | CAMERA SHUTTER      |
 * JP2.5 | D5    | IO14 |     14  |                                       | ACTUATOR LIMIT DOWN |
 * JP2.6 | D0    | IO16 |     16  |                                       | ACTUATOR LIMIT UP   |
 * JP2.7 | A0    |      |         | 100k/220k divider                     |                     |
 * JP2.8 | RST   |      |         | active low                            |                     |
 *
 */
class FoocusStacker {

public:

	FoocusStacker();

	void setup();
	void loop();

private:

	Debug* debug;
	LiquidCrystal_I2C* lcd;
	Clock* clock;
	Information* information;
	Buttons* buttons;
	Actuator* actuator;
	Camera* camera;
	Powersupply* powersupply;
	Configuration* configuration;
	Recording* recording;
	StateMachine* stateMachine;
};

#endif
