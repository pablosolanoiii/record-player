#include <Arduino.h>

#include "inputs.h"
#include "motor.h"
#include "pid.h"

PIDController pid;

static bool motor_running = false;
static const float target_rpm = 33.3;

unsigned long last_update_time = 0;

void setup() 
{
    inputs_init();
    motor_init(10);

    pid_update(&pid, 2.0, 0.5, 1.0); //We have to tune this for our system

    last_update_time = millis();
}

void loop() 
{
    if (button_pressed())
    {
        motor_running = !motor_running;

        if (!motor_running) 
        {
            motor_stop();
            pid_reset(&pid);
        }

        delay(200);
    }

    if(!motor_running) return;

    unsigned long now = millis();
    float dt = (now - last_update_time) / 1000.0;
    last_update_time = now;

    float current_rpm = read_rpm();

    float correction = pid_update(&pid, target_rpm, current_rpm, dt);

    int pwm = (int)correction;
    motor_pwm(pwm);

    delay(10);
}