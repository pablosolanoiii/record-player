#include <Arduino.h>
#include "inputs.h"
#include "motor.h"
#include "pid.h"

PIDController pid;
bool motor_running = false;
unsigned long lastTime = 0;

void setup() {
  inputs_init();
  motor_init();
  pid_init(&pid, 1.0f, 0.1f, 0.0f);   // start with PI, not PID
  lastTime = millis();
}

void loop() {
  static bool last_button_state = false;
  bool pressed = button_pressed();

  if (pressed && !last_button_state) {
    motor_running = !motor_running;

  if (!motor_running) {
    motor_stop();
    pid_reset(&pid);
  } else {
    pid_reset(&pid);
    lastTime = millis();
  }

  delay(50); // simple debounce
  }

  last_button_state = pressed;

  if (motor_running) {
    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0f;

    if (dt > 0.0f) {
      lastTime = now;

      float rpm = read_rpm();
      float output = pid_update(&pid, MOTOR_SPEED, rpm, dt);

      if (output < 0.0f) output = 0.0f;
      if (output > 255.0f) output = 255.0f;

      motor_pwm((int)output);
    }
  } else {
    motor_stop();
  }
}