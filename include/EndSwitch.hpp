/**
 * @file EndSwitch.hpp
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


class endSwitch{
  public:
  bool current_state;
  bool last_state;
  bool Ispressed=false;
  int Pin;
  bool PressedState;
  endSwitch();
  endSwitch(int Pin, bool PressedState);
  bool get_current_state(bool debounceButton=false);
  bool debounce(); // check debouce online
 
};
