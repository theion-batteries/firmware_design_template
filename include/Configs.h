/**
   @file Configs.h
   @author sami dhiab (sami@theion.de)
   @brief Place the definition of Macros here like pins, enumerate and so on
   @version 0.1
   @date 2022-02-10

   @copyright Copyright (c) 2022

*/
/**********MACROS****************/
#pragma once
#include <ArduinoSTL.h>
//#define VIRTUAL
//#define DEBUG_ALIGN
//#define MICRO // define this to switch to micrometers
#define DEBUG
#define USBPORT Serial
#define BAUDRATE 115200
#define PIN_OUTPUT_RESET 50
#define InterruptSleepPin 32
//#define COMMUNICATION
//#define TEST
//#define RELEASE
#define TIMEOUT false
//#define DEBUG_UP_DISTANCE
//#define DEBUG_UP
//#define DEBUG_DOWN
//#define DEBUG_DOWN_DISTANCE
/*********** define Motors***************/
#define STEP_DELAY 200
#define STEP_DELAY_PRINTHEAD_MOTOR 20000
// M1->Motor X
#define XEnable_pin 8 // 8 sme enble for 3 motors
#define XMs1_pin 9 // microsteps re coupled together in hrdwre
#define XMs2_pin 10
#define XMs3_pin 11
#define XStep_pin 12
#define XDir_pin 13

// M2->Motor Y
#define YEnable_pin 14 // same pin for 3
#define YMs1_pin 15
#define YMs2_pin 53
#define YMs3_pin 51
#define YStep_pin 49
#define YDir_pin 47
// M3->Motor Z
#define ZEnable_pin 45
#define ZMs1_pin 43
#define ZMs2_pin 41
#define ZMs3_pin 39
#define ZStep_pin 37
#define ZDir_pin 35
// M4->PrintHEad motor
#define PHEnable_pin 33
#define PHMs1_pin 31
#define PHMs2_pin 29
#define PHMs3_pin 27
#define PHStep_pin 25
#define PHDir_pin 23 //12
/************* endstops***********/
// Endswitch
#define E_X A5//12
// Endswitch
#define E_Y A6//13
// Endswitch
#define E_Z A7
// define light barriers
#define LB_X A2//9
#define LB_Y A3//10
#define LB_Z A4//11
// safety
#define E_Emergency 2
/*********** Distance sensors *********/
//define which distance sensor is used: uncomment the wrong one
//#define hc_sr04
#define keyence
#ifdef hc_sr04
#define Trig A10
#define Echo A10
// Distance Sensor
#define D_X A10 // echo 
#define DT_x A10 // Trigger
// Distance Sensor
#define D_Y A10 //echo 
#define DT_y A10 // Trigger
// Distance Sensor
#define D_Z A10 // echo
#define DT_z A10 // Trigger
#endif
#ifdef keyence
// serial handler
#define KEYENCE_SERIAL_HANDLER Serial
// serial baudrate
#define KEYENCE_SERIAL_BAUDRATE 115200
// map each sensor head to axis
#define XSensorHead 1
#define YSensorHead 2
#define ZSensorHead 3
#endif

/******** define generic direction*********/
#define up 1
#define down 0
#define on 0
#define off 1
#define clk 1
#define cclk 0

/***** define generic formula****/
//#define USE_GENERIC_FORMULA
#ifdef USE_GENERIC_FORMULA
// parameters

//#define MEASUREMENT 0 //T mesurement is done later
#define SENSOR_HEIGHT 30 //S: random value
// Generic formula
#define AIR_GAP_BETWEEN_PRINTHEAD_AND_ML -DISTANCE_PRINTHEAD_PLATFORM-PLATFORM_THICKNESS-SENSOR_HEIGHT

#define SENSOR_ABOVE_PLATFORM
//#define SENSOR_UNDER_PLATFORM-
#ifdef SENSOR_ABOVE_PLATFORM
#define SENSOR_HEIGHT 0 //S
#define PLATFORM_THICKNESS 12.5 //mm Z
#endif
#ifdef SENSOR_UNDER_PLATFORM
#define SENSOR_HEIGHT -SENSOR_HEIGHT
#define PLATFORM_THICKNESS 0
#endif
#endif

/*************** mechanical parameters**********/
// Generic Values
#define MotorLength 31.27 //mm
#define LeadScrewLEngth 95 //mm
#define Linear_travel_per_step 0.006 //mm
#define Angle_per_step 1.8 //degree
#define InclinationPH 20
#define EndeffectorThickness 28 //mm
#define RodLength 100.61 //mm Stab
#define MotorSensorHolderThickness 13 //mm
#define DISTANCE_PRINTHEAD_PLATFORM 126.34 //mm Y
#define SensorThreashold 0.4 //mm
#define SensorThickness 0 // mm
#define AllowedPath LeadScrewLEngth-(MotorLength+MotorSensorHolderThickness) //
#define RodLength_EndeffectorThickness RodLength+EndeffectorThickness // min =< 115+28=143, mesured + SensorThickness
// RodLength_EndeffectorThickness + LeadScrewLEngth = max >=95 + 143 = 238
#define MicroResolution 0 // 

/********** enumerations*********/
enum retVal {
  ok = 0,
  err = 1,
};

