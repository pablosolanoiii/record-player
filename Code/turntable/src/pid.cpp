#include <Arduino.h>
#include "pid.h"

void pid_init(PIDController *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->integral = 0.0f;
    pid->previous_error = 0.0;
}

float pid_update(PIDController *pid, float target, float measured, float dt)
{
    float error = target - measured;

    pid->integral += error * dt;

    float derivative = 0.0f;

    if(dt > 0.0f) derivative = (error - pid->previous_error) / dt;

    float output = (pid->kp * error) + (pid->ki * pid->integral) + (pid->kd * derivative);

    pid->previous_error = error;

    return output;
}

void pid_reset(PIDController *pid)
{
    pid->integral = 0.0f;
    pid->previous_error = 0.0f;
}