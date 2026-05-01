#include <Arduino.h>

// inputs 
#define BUTTON_PIN A0
#define BUTTON_PIN_2 A1

// outputs 
#define PWM_PIN 10

int PWM_value = 10;
unsigned long lastPressTime = 0;
const int debounceDelay = 200;

void setup()
{
  Serial.begin(9600);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);

  pinMode(PWM_PIN, OUTPUT);
}

void loop()
{
  unsigned long currentTime = millis();

  int state1 = digitalRead(BUTTON_PIN);
  int state2 = digitalRead(BUTTON_PIN_2);

  // Decrease PWM
  if (state1 == LOW && (currentTime - lastPressTime > debounceDelay))
  {
    PWM_value -= 5;
    if (PWM_value < 0) PWM_value = 0;
    lastPressTime = currentTime;
  }

  // Increase PWM
  if (state2 == LOW && (currentTime - lastPressTime > debounceDelay))
  {
    PWM_value += 5;
    if (PWM_value > 255) PWM_value = 255;
    lastPressTime = currentTime;
  }

  analogWrite(PWM_PIN, PWM_value);

  Serial.println(PWM_value);
}
