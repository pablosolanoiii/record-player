#ifndef MOTOR_H
#define MOTOR_H

void motor_init(int pin);
/*
Initializes the motor control hardware 

Parameters:
pin -PWM output pin connedt to the motor driver 

This function configures the specified pin as an output 
and prepares it for PWM control using Arduinos' analogWrite()
*/

void motor_pwm(int pwm);
/*
Sets the motor power using PWM

Parameters:
pwm - PWM duty cycle value 

Valid range:
0 -> motor off
255 -> max motor power

The PWM signal controls the average voltage delivered to the motor. 
Higher values increases motor speed.  
*/

void motor_stop();
/*
Slows down the motor gradually to a stop.
*/
#endif 