# FoocusStacker
An Arduino based application to control a linear actuator and digital camera.
Used to create a sequence of pictures (focus stack) that can be combined into one.  

Components:

*   WeMos D1mini (ESP8266) development board
*   C-beam linear actuator
*   with reed contacts as limit switches
*   NEMA-23 stepper motor
*   LCD 2004 a 20 character 4 line LCD panel
*   Buttons for menu navigation and control
*   Camera focus and shutter remote release control
 
Using an object oriented approach to divide the application into components.
Reducing complexity by making all components similar in structure and usage.

*   Component
*   Page
*   State
*   Actuator
*   Buttons
*   Clock
*   Camera
*   Recording
*   Configuration
*   Information

	



   