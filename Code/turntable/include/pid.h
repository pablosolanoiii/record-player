#ifndef PID_H
#define PID_H

typedef struct
{
    float kp; // Proportional gain: How we react to the current error
    float ki; // Integral gain: How we react to long-term accumulated error
    float kd; // Derivative gain: How strongly we react to reate of change of error 

    float integral; // Stores the accumulated error over time 
    float previous_error; // Stores the error from the previous control cycle
} PIDController;

void pid_init(PIDController *pid, float kp, float ki, float kd);
/*
Initializes the PID controller.

Parameters:

pid     -pointer to the PID controller struct
kp      -proportional gain 
ki      -integral gain
kd      -derivative gain

This function sets the controller gains and resets the internal state
*/

float pid_update(PIDController *pid, float target, float measured, float dt);
/*
Updates the PID controller and computes a correction value.

Parameters:
pid         -pointer to the PID controller struct
target      -desired values (target RPM)
measured    -current measuered value (sensor RPM)
dt          -time step since last update (seconds)

This function computes the PID control equation and returns 
a correction value that should be used to adjust motor power.  
*/

void pid_reset(PIDController *pid);
/*
Resets the internal memory of the PID controller.

This clears the accumulated integral error and previous errors.
So it leaves a clean state for MCU after restarting.
*/

#endif
