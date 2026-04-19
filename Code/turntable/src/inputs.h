#ifndef INPUTS_H 
#define INPUTS_H

void inputs_init();
/*
Initializes all input hardware used by the system.

This function configures the physical input pins for the 
button and Hall sensor 

Typical tasks performed here:
-set button pin mode 
-set Hall sensor pin more

must be called during system startup in setup()
*/

bool button_pressed();
/*
Checks if the start/stop button has been pressed.

Returns:
true    -button has been pressed 
false   -button has not been pressed 

Debounced logic will be applied 

The main controller will use this to toggle motor on/off
*/

float rpm();
/*
Calculates the current platter speed in RPM.

Returns:
current platter rotational speed (RPM)

This function reads timing information from the Hall sensor.
Each magnet passing the sensor produces as pulse using.

RPM is calculated from the time between pulses using: 

RPM = 60 / (pulse_period_seconds * 16)
*/

#endif