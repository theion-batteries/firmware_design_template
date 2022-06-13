/**
 * Author:Ab Kurk
 * version: 1.0
 * date: 24/01/2018
 * Description: 
 * This sketch is part of the beginners guide to putting your Arduino to sleep
 * tutorial. It is to demonstrate how to put your arduino into deep sleep and
 * how to wake it up.
 * Link To Tutorial http://www.thearduinomakerman.info/blog/2018/1/24/guide-to-arduino-sleep-mode
 */
#pragma once
#if defined(__AVR__)
#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define sleep_enable sleep_enable
#define sleep_disable sleep_disable 
#define set_sleep_mode set_sleep_mode
#define sleep_cpu sleep_cpu
#define SLEEP_MODE_PWR_DOWN SLEEP_MODE_PWR_DOWN
#elif defined(ESP8266)
#include <pgmspace.h>
#elif defined(ESP32)
#include <esp_sleep.h>
#define sleep_enable esp_sleep_enable_gpio_wakeup
#define sleep_disable esp_sleep_disable_wakeup_source(1)
#define set_sleep_mode esp_sleep_enable_ext0_wakeup
#define sleep_cpu esp_deep_sleep_start
#define Mode 1
#define GPIO_NUM 0
#endif
#include <Arduino.h>
class SleepHardware{
 private:
 int interruptPin;
 public:
    SleepHardware(int interruptPin)
    {
    pinMode(LED_BUILTIN,OUTPUT);//We use the led on pin 13 to indecate when Arduino is A sleep
    pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
    digitalWrite(LED_BUILTIN,HIGH);//turning LED on
    }
void Sleep(){
    sleep_enable();//Enabling sleep mode
    attachInterrupt(GPIO_NUM, SleepHardware::wakeUp, LOW);//attaching a interrupt to pin d2
    //set_sleep_mode(GPIO_NUM,Mode);//Setting the sleep mode, in our case full sleep
    digitalWrite(LED_BUILTIN,LOW);//turning LED off
    delay(1000); //wait a second to allow the led to be turned off before going to sleep
    sleep_cpu();//activating sleep mode
    Serial.println("just woke up!");//next line of code executed after the interrupt 
    digitalWrite(LED_BUILTIN,HIGH);//turning LED on
  }

static void wakeUp(){
  Serial.println("Interrrupt Fired");//Print message to serial monitor
  //sleep_disable;//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}
};