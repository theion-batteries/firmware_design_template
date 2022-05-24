/**
   @file ComHandler.hpp
   @author sami dhiab (sami@theion.de)
   @brief This Class handles serial communication layer
   @version 0.3
   @date 2022-05-13

   @copyright Copyright (c) 2022

*/
#ifndef _COMHANDLER_H_
#define _COMHANDLER_H_
#pragma once
#include "CmdPatternCallbacks.h"

/**
 * @brief this class is the interface of communication layer
 * 
 */
class ComManager {
  private:
  Stream* ComHandler;
  public:
  // if communication via usb cable
  //#define VIA_USB
  #ifdef VIA_USB
  ComManager();
  #endif
  // if communication via bluetooth
  #ifdef VIA_BLUETOOTH
  ComManager(Bluetooth& BltHandler ): ComHandler(BltHandler){}
  #endif
  // if communication via Wifi
  #ifdef VIA_Wifi
  ComManager(Wifi& BltHandler ): ComHandler(BltHandler){}
  #endif
  void initCom(unsigned long baudrate);

};

#endif