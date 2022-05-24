/**
   @file ComHandler.cpp
   @author sami dhiab (sami@theion.de)
   @brief This Class handles serial communication layer
   @version 0.3
   @date 2022-05-13

   @copyright Copyright (c) 2022

*/
#include "ComHandler.hpp"

void ComManager::initCom(unsigned long baudrate) {
  Serial.begin(baudrate);
  // init this firmware if any hardware need it
  // either inside class or outside
  // firmware.init();
}

