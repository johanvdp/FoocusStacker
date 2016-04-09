// The author disclaims copyright to this source code.
#include "FoocusStacker.h"

/**
 * Construct the application by constructing all its components.
 */
FoocusStacker::FoocusStacker() {

	// 0x27 is the I2C bus address for an unmodified module
	//                 lcd(addr,en,rw,rs,d4,d5,d6,d7)
	lcd = new LiquidCrystal_I2C(I2C_LCD, 2, 1, 0, 4, 5, 6, 7);

	clock = new Clock();
	information = new Information();
	buttons = new Buttons(clock);
	actuator = new Actuator();
	debug = Debug::createInstance(clock);
	recording = new Recording();
	camera = new Camera(clock);
	powersupply = new Powersupply(clock);
	stateMachine = new StateMachine(clock, buttons, lcd, actuator, camera,
			recording, information, powersupply);
}

/**
 * Called once to setup the application.
 *
 * Will initialize (setup) all external libraries and components that make up the application.
 */
void FoocusStacker::setup() {

	// I2C wire protocol for lcd and buttons
	Wire.begin(SDA, SCL);

	// external library
	lcd->setBacklightPin(3, POSITIVE);
	lcd->setBacklight(HIGH);
	lcd->begin(20, 4);
	lcd->clear();

	// all components
	debug->setup();
	clock->setup();
	information->setup();
	buttons->setup();
	actuator->setup();
	powersupply->setup();
	recording->setup();
	camera->setup();
	stateMachine->setup();
}

/**
 * Called continuously to keep the application going.
 *
 * The application must execute and return quickly.
 * If not, the ESP Arduino implementation can not perform its housekeeping tasks and the built-in watchdog timer will reset the chip/application.
 *
 * The components that make up the application are triggered to perform their respective Input, Process, and Output operations (in that order).
 */
void FoocusStacker::loop() {

	// read all inputs
	clock->read();
	buttons->read();
	actuator->read();
	powersupply->read();
	stateMachine->read();

	// perform processing
	stateMachine->process();

	// write all outputs
	actuator->write();
	camera->write();
	powersupply->write();
	stateMachine->write();
}

/**
 * The singleton instance of the FoocusStacker application.
 */
FoocusStacker instance;

/**
 * Arduino setup entry point.
 * Forwards the call into the application instance.
 */
void setup() {
	instance.setup();
}

/**
 * Arduino loop entry point.
 * Forwards the call into the application instance.
 */
void loop() {
	instance.loop();
}
