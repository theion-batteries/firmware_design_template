/**
   @file Alignment.hpp
   @author sami dhiab (sami@theion.de)
   @brief
   @version 0.1
   @date 2022-02-08

   @copyright Copyright (c) 2022

*/
#ifndef _ALIGNMENT_H_
#define _ALIGNMENT_H_

#include "EndSwitch.hpp"
#include "Configs.h"
#include "Nema_8.hpp"
#include "light_barrier.hpp"
#include "DistanceSensor.hpp"
class Alignment {
  public:
    Nema8 *Motor_x;
    Nema8 *Motor_y;
    Nema8 *Motor_z;
    Nema8 *Motor_PrintHead; 
    endSwitch *endSwitch_x;
    endSwitch *endSwitch_y;
    endSwitch *endSwitch_z;
    endSwitch *endSwitch_stop;
    lightBarrier *lightBarrier_x;
    lightBarrier *lightBarrier_y;
    lightBarrier *lightBarrier_z;
    DistanceSensor *DistanceM_x;
    DistanceSensor *DistanceM_y;
    DistanceSensor *DistanceM_z;

    const float MinDistanceToML = 10; // the min distance from ML to print safely ex: 3mm to ML
    const float MaxDistanceToMl = 60; // the max distance from ML to print safely ex: 5mm to ML
    float TargetDistancePHToMl=70;
    float TargetDistanceSensorToMl=165;
    //static
    int NumOfCycles=0;

    //Flags:
    bool homed = false;
    bool aligned = false;
    bool allDownMax = false;
    bool xDownMax = false;
    bool yDownMax = false;
    bool zDownMax = false;
    bool allUpMax = false;
    bool xUpMax = false;
    bool yUpMax = false;
    bool zUpMax = false;
    bool xUpDistanceArrived = false;
    bool yUpDistanceArrived = false;
    bool zUpDistanceArrived = false;
    bool allUpDistanceArrived = false;
    bool xDownDistanceArrived = false;
    bool yDownDistanceArrived = false;
    bool zDownDistanceArrived = false;
    bool allDownDistanceArrived = false;
      // Flags
  bool XAligned = false, YAligned = false, ZAligned = false;
    //constructors
    // with only 3motors/endtops
    Alignment(Nema8 *Motor_x, Nema8 *Motor_y, Nema8 *Motor_z, DistanceSensor *DistanceM_x, DistanceSensor *DistanceM_y, DistanceSensor *DistanceM_z,
              endSwitch *endSwitch_x, endSwitch *endSwitch_y, endSwitch *endSwitch_z);
    // overlaod with 3 Endstops and 3 light barrier
    Alignment(Nema8 *Motor_x, Nema8 *Motor_y, Nema8 *Motor_z, DistanceSensor *DistanceM_x, DistanceSensor *DistanceM_y, DistanceSensor *DistanceM_z,
              endSwitch *endSwitch_x, endSwitch *endSwitch_y, endSwitch *endSwitch_z,endSwitch *endSwitch_stop, lightBarrier *lightBarrier_x, lightBarrier *lightBarrier_y, lightBarrier *lightBarrier_z);
    // overlaod with 3 Endstops and 3 light barrier and printHead Motor
    Alignment(Nema8 *Motor_x, Nema8 *Motor_y, Nema8 *Motor_z, Nema8 *Motor_PrintHead, DistanceSensor *DistanceM_x, DistanceSensor *DistanceM_y, DistanceSensor *DistanceM_z,
              endSwitch *endSwitch_x, endSwitch *endSwitch_y, endSwitch *endSwitch_z,endSwitch *endSwitch_stop, lightBarrier *lightBarrier_x, lightBarrier *lightBarrier_y, lightBarrier *lightBarrier_z);
/******************************* API V3 ****************************
 * @brief API v3 comes with the new command design pattern and task scheduling
 * API v3 will use task scheduling. The old API used non blocking function
 * All loops were converted into non blocking func using counters, where only
 * the main loop was used loop(). The API V3 will use blcoking functions with
 * internal loops, but this will no matter any more if task scheduling is included.
 * please use the API V3 if you are advanced programmer in c++
*/
// general method take the motor as ref    
    retVal MoveDistanceMSafe(Nema8* Mref, int direction, float distance);    
    retVal MoveDistanceXloop(int direction, float distance); // move motor X a given distance   
    retVal MoveDistanceYloop(int direction, float distance); // move motor X a given distance   
    retVal MoveDistanceZloop(int direction, float distance); // move motor X a given distance   
    retVal RotateAnglePHloop(Nema8* Mref, int direction, float angle);    
    bool isStopButtonPressed();
    void initFirmwareUnit();
    
    
    
    
    // Basic Methods: API V2    
    retVal StepOnceX(int direction); // move motor X one step
    retVal StepOnceY(int direction); // move motor Y one Step
    retVal StepOnceZ(int direction); // move motor Z one Step
    retVal MoveDistanceX(int direction, float distance); // move motor X a given distance
    retVal MoveDistanceY(int direction, float distance); // move motor Y a given distance
    retVal MoveDistanceZ(int direction, float distance); // move motor Z a given distance
    retVal MoveDistanceAll(int direction, float distance); // move motor Z a given distance

    retVal MoveAngleX(int direction, float angle); // move motor X a given Angle
    retVal MoveAngleY(int direction, float angle); // move motor Y a given Angle
    retVal MoveAngleZ(int direction, float angle); // move motor Z a given Angle 
    retVal MoveAngleAll(int direction, float angle); // move motor Z a given Angle 

    inline double getValueSensorX(); // get mesured value on sensor X 
    inline double getValueSensorY(); // get mesured value on sensor Y 
    inline double getValueSensorZ(); // get mesured value on sensor X 
    inline bool getReadingEndstopX(); // get mesured Reading Endstop X 
    inline bool getReadingEndstopY(); // get mesured Reading Endstop Y 
    inline bool getReadingEndstopZ(); // get mesured Reading Endstop X 
    inline bool getReadingLightBarrierX(); // get mesured Reading LightBarrier X 
    inline bool getReadingLightBarrierY(); // get mesured Reading LightBarrier Y 
    inline bool getReadingLightBarrierZ(); // get mesured Reading LightBarrier X 
    // APIs V1 compatible
    retVal GoToReferenceDown(); // API compatible func if new refrence is set
    int convertDistanceToStepMicros(float distance); // if distance is in micrometer
    int convertAngleToStep(float angle); // if angle is degree
    // APIs V2 Complex
    inline float getDistancePrintHeadToMl(); // get distance between print head and Mother liquid
    inline float getDistancePrintHeadToMlX();  // get real distance on x axis
    inline float getDistancePrintHeadToMlY();  // get real distance on Y axis
    inline float getDistancePrintHeadToMlZ();  // get real distance on Z axis
    inline float getDistancePlatformToMlX(); // get distance between platform and Mother liquid X 
    inline float getDistancePlatformToMlY(); // get distance between platform and Mother liquid Y 
    inline float getDistancePlatformToMlZ(); // get distance between platform and Mother liquid Z
    inline float getDistancePlatformToMlXYZ(); // get distance between platform and Mother liquid: summe of 3 distance sensors divided by 3
    retVal GoToReferenceUp(); // new reference up  with light barrier
    retVal calibratePrintHead(); // new calibrate func using v2 methods
    inline bool checkLimitUpX(); // check if  light barrier is traversed
    inline bool checkLimitUpY(); // check if  light barrier is traversed
    inline bool checkLimitUpZ(); // check if  light barrier is traversed
    inline bool checkLimitUpXYZ(); // check if all traversed
    inline bool checkLimitDownX(); // check if  endstops is pressed
    inline bool checkLimitDownY(); // check if  endstops is pressed
    inline bool checkLimitDownZ(); // check if  endstops is pressed
    inline bool checkLimitDownXYZ(); // check if  all pressed
    retVal StepDownXMax(); // move x max down
    retVal StepDownYMax(); // move y max down
    retVal StepDownZMax(); // move z max down
    retVal StepUpXMax(); // move x max Up
    retVal StepUpYMax(); // move y max Up
    retVal StepUpZMax(); // move z max Up
    /********* move distance and check safety ********/
    retVal MoveDistanceXSafe(int direction, float distance);
    retVal MoveDistanceYSafe(int direction, float distance);
    retVal MoveDistanceZSafe(int direction, float distance);
    retVal MoveDistanceAllSafe(int direction, float distance);
    /******** move angle and chekc safety **************/
    retVal MoveAngleXSafe(int direction, float Angle);
    retVal MoveAngleYSafe(int direction, float Angle);
    retVal MoveAngleZSafe(int direction, float Angle);
    retVal MoveAngleAllSafe(int direction, float Angle);
    /********** rotate printHead in clockweise **********/
    retVal StepOncePH(int direction); // move motor PH one step
    retVal rotateFullRevPH(int direction); // move motor PH one rev
    retVal rotateAnglePH(int direction, float Angle); //rotate certain angle
    /************* oscillate system ***********************/
    retVal oscillateSys(float desired_angle, int num_revolutions, bool default_sens=clk, bool reverse_sense=true);
    retVal movePhToRefX();
    /************ keyence sensor **************/
    retVal initSensors();
    /************ increment counted steps inside class objects******/
    void incrementTotalStepCounted();
    /********** safety step counter reset **********/
    void resetStepCounter();
    









    // new features
    float getCurrentPosX(); // get pos on path
    float getCurrentPosY(); // get pos on path
    float getCurrentPosZ(); // get pos on path
    float CheckBoundaryX(float targetDistance, int direction);



    // Complex Methods: API v1 
    retVal InitAlign(bool enable = on);
    retVal EnableAll(bool enable = on);
    retVal DisableAll(bool enable = off);
    retVal MoveHomeAll(); // send motors to refrence: either up or down
    retVal AlignLoop(); // align 3 motors based on target distance: distance between Sensor and ML
    float getRemainingDistanceX();// X remaining distance based on config file setup
    float getRemainingDistanceY();// Y remaining distance based on config file setup
    float getRemainingDistanceZ();// Z remaining distance based on config file setup
    float getMinX(); // calculate the height X over values
    float getMinY(); // calculate the height Y over values
    float getMinZ(); // calculate the height Z over values
    float getMaxX(); // calculate the height X over values
    float getMaxY(); // calculate the height Y over values
    float getMaxZ(); // calculate the height Z over values
    retVal MoveUp(bool x, bool y, bool z, bool checkLimit);
    retVal MoveDown(bool x, bool y, bool z, bool checkLimit);
    retVal MoveUpTo(bool x, bool y, bool z, bool checkLimit, float distance);
    retVal MoveDownTo(bool x, bool y, bool z, bool checkLimit, float distance);
    retVal setTargetDistancePHToML(float distance);
    retVal setTargetDistanceSensorToML(float distance);
    int ConvertDistanceToStep(float distance);
};

#endif