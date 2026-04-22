#include "timer.h"
#include "inputs.h"
#include "motor.h"
#include "pid.h"

// put function declarations here:
PIDController pid;
int current_speed = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;


void setup() {

  inputs_init();
  motor_init();
  pid_init(&pid, 1.0, 0.1, 0.05); // Example PID parameters

}

void loop() {

  if (button_pressed())
  {
    delay(100); // Debounce delay
    while (!button_pressed())
    {
        current_speed = pid_update(&pid, MOTOR_SPEED, read_rpm(), stopTimer(&startTime, &elapsedTime)); // Example control loop with dt = 0.1s
        startTimer(&startTime); // Start timer for next control loop iteration
        motor_pwm(current_speed);
    }
    
    motor_stop();
    pid_reset(&pid);

  }
  else
  {
    motor_stop();
    pid_reset(&pid);
  }
}