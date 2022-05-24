/**
 * @file Reset.h
 * @author sami dhiab (you@domain.com)
 * @brief class reset for hardware/software reset
 * @version 0.1
 * @date 2022-05-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Arduino.h"
#include "EndSwitch.hpp"
/**
 * @brief reset device: hw reset by connecting output pin to reset 
 * input pin and set to high or sw reset by calling resetFunc() internally.
 * 
 */
class ResetHardware
{
private:
int resetOutPin;
void (*resetFunc) (void) = 0; //declare reset function @ address 0

public:
ResetHardware(int resetOutPin):resetOutPin(resetOutPin){}

void hard_reset()
{
    pinMode(resetOutPin,OUTPUT);
}
void soft_reset()
{
resetFunc();
}

};