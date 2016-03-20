// The author disclaims copyright to this source code.
#include "FoocusStacker.h"

#define SDA D3
#define SCL D4

FoocusStacker::FoocusStacker() {

	// 0x27 is the I2C bus address for an unmodified module
	//                 lcd(addr,en,rw,rs,d4,d5,d6,d7)
	lcd = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5, 6, 7);

	clock = new Clock();
	information = new Information();
	buttons = new Buttons(clock);
	configuration = new Configuration();
	actuator = new Actuator(configuration);
	debug = Debug::createInstance(clock, configuration);
	recording = new Recording(configuration);
	camera = new Camera(clock, configuration);
	stateMachine = new StateMachine(clock, buttons, lcd, actuator, camera,
			configuration, recording, information);
}

void FoocusStacker::setup() {

	// I2C wire protocol for lcd and buttons
	Wire.begin(SDA, SCL);

	// external library
	lcd->setBacklightPin(3, POSITIVE);
	lcd->setBacklight(HIGH);
	lcd->begin(20, 4);
	lcd->clear();

	// all components
	clock->setup();
	information->setup();
	buttons->setup();
	configuration->setup();
	actuator->setup();
	debug->setup();
	recording->setup();
	camera->setup();
	stateMachine->setup();
}

void FoocusStacker::loop() {

	// read all inputs
	clock->read();
	buttons->read();
	actuator->read();
	stateMachine->read();

	// perform processing
	actuator->process();
	stateMachine->process();

	// write all outputs
	actuator->write();
	camera->write();
	stateMachine->write();
}

// =========================================================
// FOOCUS STACKER ENTRY POINT
// =========================================================

FoocusStacker instance;

void setup() {
	instance.setup();
}

void loop() {
	instance.loop();
}
