/**
 * @file EndSwitch.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "EndSwitch.hpp"
/**
 * @brief Construct a new end Switch::end Switch object
 * 
 * @param Pin 
 */
endSwitch::endSwitch(int Pin, bool PressedState){
    this->PressedState=PressedState;
    this->Pin=Pin;
    pinMode(Pin, INPUT_PULLUP); //the button pin
  }
/**
 * @brief get current state
 * 
 * @return true 
 * @return false 
 */
bool endSwitch::get_current_state(bool debounceButton/*=false*/){
    if (debounceButton==true){
      current_state=debounce();
       return current_state;
    }
    else{
      current_state=digitalRead(Pin);
      return current_state;
  }
}
/**
 * @brief debounce a button
 * 
 */
bool endSwitch::debounce(){
    int buttonState;       // the current reading from the input pin
    static int lastButtonState = HIGH;   // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(Pin);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      }
    }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  return lastButtonState;
  }