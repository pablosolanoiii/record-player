#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>


static const int MOTOR_PIN = 10;
static int current_pwm = 0;
static const float MOTOR_SPEED = 33.33; // RPM for 33 1/3 record 

void motor_init()
{
    pinMode(MOTOR_PIN, OUTPUT);
    analogWrite(MOTOR_PIN, 0);
    current_pwm = 0;
}

void motor_pwm(int pwm)
{
    if (pwm < 0) pwm = 0;
    if (pwm > 255) pwm = 255;

    current_pwm = pwm;
    analogWrite(MOTOR_PIN, pwm);
}

void motor_stop()
{
    while (current_pwm > 0) 
    {
        current_pwm -= 5;
        if (current_pwm < 0) current_pwm = 0;

        analogWrite(MOTOR_PIN, current_pwm);
        delay(50); 
    }
}

#endif
