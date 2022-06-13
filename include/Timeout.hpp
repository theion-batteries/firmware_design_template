/**
 * @file Timeout.hpp
 * @author sami@theion.de
 * @brief timeout lib
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <Arduino.h>

class TaskTimer
{
  public:
  unsigned int interval;
  unsigned long timer=0;
  bool millisec =true;
  unsigned long (*InternalClock)(void);
  
  TaskTimer(unsigned int interval, unsigned long timer, bool millisec):interval(interval), timer(timer), millisec(true)
  {
    if (millisec)
    {
      InternalClock=&millis; 
    } 
    else{
      InternalClock=&micros; 
    }
  }
template<typename Function>
void taskSchedule( Function func)
{
  if(InternalClock()-timer>interval)
    {
      timer=InternalClock(); 
      func; //run func
    } 
}
  void timeStop()
  {

  }
  void printTimerValue()
  {
    Serial.print("timer value: ");
    Serial.println(timer);
  }
  

};



/*class TIMEOUT{
    TIMEOUT(unsigned long interval)
    {
      unsigned long previousMillis = 0;
      const long interval = 1000;
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval)
      {
        previousMillis = currentMillis;
      }
  };*/
