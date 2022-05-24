/**
 * @file Nema_8.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "DriverA4988.hpp"


/**
 * @brief child class nema8 from parent class stepper driver a4988
 * 
 */
class Nema8: public a4988{
   public:
   Nema8(int motor_steps, int ms1_pin, int ms2_pin, int ms3_pin, int dir_pin, int enable_pin, int step_pin, bool direction): a4988(motor_steps, ms1_pin, ms2_pin, ms3_pin, dir_pin, enable_pin, step_pin, direction)
   {
   this->enable_pin = enable_pin;
   this->dir_pin = dir_pin;
   this->ms1_pin = ms1_pin;
   this->ms2_pin = ms2_pin;
   this->ms3_pin = ms3_pin;
   this->step_pin = step_pin;
   this->direction=direction;
   // setup the pins on the microcontroller:
   pinMode(this->ms1_pin, OUTPUT);
   pinMode(this->ms2_pin, OUTPUT);
   pinMode(this->ms3_pin, OUTPUT);
   pinMode(this->dir_pin, OUTPUT);
   pinMode(this->enable_pin, OUTPUT);
   pinMode(this->step_pin, OUTPUT);
   if(motor_steps != 0)
      {
         this->motor_steps = motor_steps; 
      }
   else
      {
         this->motor_steps = 200;       // a common value for steppers
      }
   // use setDelay to change before stepping, otherwise default
   this->step_delay = STEP_DELAY;         // 20000 us (20 ms) as a default

   } 
};
