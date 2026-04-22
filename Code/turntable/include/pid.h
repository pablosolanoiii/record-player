#ifndef PID_H
#define PID_H

#include <Arduino.h>

typedef struct
{
    float kp; // Proportional gain: How we react to the current error
    float ki; // Integral gain: How we react to long-term accumulated error
    float kd; // Derivative gain: How strongly we react to reate of change of error 

    float integral; // Stores the accumulated error over time 
    float previous_error; // Stores the error from the previous control cycle
} PIDController;


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

#endif
