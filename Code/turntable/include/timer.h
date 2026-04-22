#ifndef timer_h
#define timer_h
#include <Arduino.h>


void startTimer(unsigned long *startTime) {
    if (*startTime == 0)
    {
        *startTime = millis();
    }
    
}

unsigned long stopTimer(unsigned long *startTime, unsigned long *elapsedTime) {
    if (*startTime != 0)
    {
        *elapsedTime = millis() - *startTime;
        *startTime = 0;
    }
    return *elapsedTime;
}

#endif