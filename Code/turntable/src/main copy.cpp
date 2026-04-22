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

  while (button_pressed())
  {
    motor_pwm(current_speed += 10);
  }
  
  motor_stop();

}