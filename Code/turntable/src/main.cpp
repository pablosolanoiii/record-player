#include <Arduino.h>

//inputs 
#define BUTTON_PIN A0
#define HALL_PIN A1
#define UP_BUTTON_PIN A2
#define DOWN_BUTTON_PIN A3

//outputs 
#define LED_HALL_PIN 30 
#define LED_BUTTON_PIN 31
#define PWM_PIN 10


int PWM_value = 0;
unsigned long last_press_ = 0;



void setup()
{
  Serial.begin(9600);
  
  //inputs 
  pinMode(BUTTON_PIN, INPUT);
  pinMode(HALL_PIN, INPUT);
  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);  

  //ouputs
  pinMode(LED_HALL_PIN, OUTPUT);
  pinMode(LED_BUTTON_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
}

void loop()
{

  //Checks if the button is pressed, if it is, it waits until the button is released and then turns on the LED for 1 second
  /*if (digitalRead(BUTTON_PIN) == LOW)
  {
    while (digitalRead(BUTTON_PIN) == LOW)
    {
      delay(100);
    }

    digitalWrite(LED_BUTTON_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUTTON_PIN, LOW);
  }*/

  //Reads the value from the hall sensor through analog pin
  int hall_value = analogRead(HALL_PIN);

  //Testing the hall sensor value by printing it to the serial monitor
  Serial.println(hall_value);

  //if the hall sensor value is above 450, turn on the LED, otherwise turn it off
  if (hall_value > 450)
  {
    digitalWrite(LED_HALL_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_HALL_PIN, LOW);
  }


}