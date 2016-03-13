// The author disclaims copyright to this source code.
#ifndef _FoocusStacker_H
#define _FoocusStacker_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "Clock.h"
#include "Domain.h"
#include "Buttons.h"
#include "Actuator.h"
#include "Pages/Page.h"
#include "Statistics.h"
#include "States/StateMachine.h"
#include "Debug.h"

// =====================
// D1mini edge connector
// =====================
// JP1 label  ESP info
//   1    5V      USB ->|- 5V
//   2     G
//   3    D4  IO2 pull-up 10k, I2C SCL, LED active low
//   4    D3  IO0 pull-up 10k, I2C SDA
//   5    D2  IO4
//   6    D1  IO5
//   7    RX
//   8    TX
//
// JP2 label  ESP info
//   1   3V3
//   2    D8 IO15 pull-down 10k
//   3    D7 IO13
//   4    D6 IO12
//   5    D5 IO14
//   6    D0 IO16
//   7    A0      100k/220k divider
//   8   RST      active low

// ===================
// Arduino pin mapping
// ===================
// D1mini arduino pin number
// D0          16
// D1           5
// D2           4
// D3           0
// D4           2
// D5          14
// D6          12
// D7          13
// D8          15

// =========================
// FoocusStacker pin mapping
// =========================
// D1mini arduino pin number
// D0          16 ACTUATOR LIMIT UP
// D1           5 ACTUATOR DIRECTION
// D2           4 ACTUATOR PULSE
// D3           0 SDA
// D4           2 SCL
// D5          14 ACTUATOR LIMIT DOWN
// D6          12
// D7          13
// D8          15

class FoocusStacker {

public:

	FoocusStacker();
	LiquidCrystal_I2C* getLCD();
	Clock* getClock();
	Information* getInformation();
	Buttons* getButtons();
	Actuator* getActuator();
	Configuration* getConfiguration();
	Recording* getRecording();
	StateMachine* getStateMachine();

	void setup();
	void loop();

private:

	Debug* debug;
	LiquidCrystal_I2C* lcd;
	Clock* clock;
	Information* information;
	Buttons* buttons;
	Actuator* actuator;
	Configuration* configuration;
	Recording* recording;
	StateMachine* stateMachine;
};

#endif
