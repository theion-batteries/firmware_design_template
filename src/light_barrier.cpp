/**
 * @file light_barrier.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "light_barrier.hpp"
/**
 * @brief Construct a new lightBarrier::lightBarrier object
 * 
 * @param Pin 
 */
lightBarrier::lightBarrier(int Pin, bool TraversedState){
    this->TraversedState=TraversedState;
    this->Pin=Pin;
    pinMode(Pin, INPUT_PULLUP); //the input pin to mcu
  }
/**
 * @brief get current state
 * 
 * @return true 
 * @return false 
 */
bool lightBarrier::get_current_state()
{
      return digitalRead(Pin);
}
