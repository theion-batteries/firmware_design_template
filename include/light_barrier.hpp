/**
 * @file light_barrier.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief endswitch class 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <ArduinoSTL.h>

class lightBarrier{
  public:
  bool current_state;
  bool last_state;
  bool IsTraversed=false;
  int Pin;
  bool TraversedState;
  lightBarrier();
  lightBarrier(int Pin, bool TraversedState);
  bool get_current_state();
 
};
