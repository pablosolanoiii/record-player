
#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

#define BUTTON_PIN 2 
#define HALL_PIN 12
#define MAGNETS_PER_REVOLUTION 16

volatile unsigned long pulse_period = 0;
volatile unsigned long last_pulse_time = 0;

//Private functions
void hall_sensor_isr()
{
    unsigned long now = micros();
    if (last_pulse_time != 0)
        pulse_period = now - last_pulse_time;    
    last_pulse_time = now;
}

//Public functions
bool button_pressed()
{
    static unsigned long last_press_time = 0;
    static int last_state = HIGH;
    const unsigned long debounce_delay = 50;

    int state = digitalRead(BUTTON_PIN);

    if (state == LOW)
    {
        unsigned long now = millis();
        if (now - last_press_time > debounce_delay) 
        {
            last_press_time = now;
            last_state = state;
            return true;
        }
    }
    last_state = state;
    return false;   
}

void inputs_init()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(HALL_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(HALL_PIN), hall_sensor_isr, RISING);
}

float read_rpm()
{
    noInterrupts();
    unsigned long period = pulse_period;
    unsigned long last_time = last_pulse_time;
    interrupts();

    if (period == 0) return 0.0; 

    if ((micros() - last_time) > (period * 2))
        return 0.0;

    float seconds = period / 1000000.0;
    return 60.0 / (seconds * MAGNETS_PER_REVOLUTION);
}

#endif