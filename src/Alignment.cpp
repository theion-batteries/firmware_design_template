/**
   @file Alignment.cpp
   @author sami dhiab (sami@theion.de)
   @brief
   @version 0.1
   @date 2022-02-11

   @copyright Copyright (c) 2022

*/
#include "Alignment.hpp"

Alignment::Alignment(Nema8* Motor_x, Nema8* Motor_y, Nema8* Motor_z, DistanceSensor* DistanceM_x, DistanceSensor* DistanceM_y, DistanceSensor* DistanceM_z,
                     endSwitch* endSwitch_x, endSwitch* endSwitch_y, endSwitch* endSwitch_z)
{
  this->Motor_x = Motor_x;
  this->Motor_y = Motor_y;
  this->Motor_z = Motor_z;
  this->DistanceM_x = DistanceM_x;
  this->DistanceM_y = DistanceM_y;
  this->DistanceM_z = DistanceM_z;
  this->endSwitch_x = endSwitch_x;
  this->endSwitch_y = endSwitch_y;
  this->endSwitch_z = endSwitch_z;
}

Alignment::Alignment(Nema8* Motor_x, Nema8* Motor_y, Nema8* Motor_z, DistanceSensor* DistanceM_x, DistanceSensor* DistanceM_y, DistanceSensor* DistanceM_z,
                     endSwitch* endSwitch_x, endSwitch* endSwitch_y, endSwitch* endSwitch_z, endSwitch* endSwitch_stop, lightBarrier* lightBarrier_x, lightBarrier* lightBarrier_y, lightBarrier* lightBarrier_z)
{
  this->Motor_x = Motor_x;
  this->Motor_y = Motor_y;
  this->Motor_z = Motor_z;
  this->DistanceM_x = DistanceM_x;
  this->DistanceM_y = DistanceM_y;
  this->DistanceM_z = DistanceM_z;
  this->endSwitch_x = endSwitch_x;
  this->endSwitch_y = endSwitch_y;
  this->endSwitch_z = endSwitch_z;
  this->lightBarrier_x = lightBarrier_x;
  this->lightBarrier_y = lightBarrier_y;
  this->lightBarrier_z = lightBarrier_z;
  this->endSwitch_stop = endSwitch_stop;
}
Alignment::Alignment(Nema8* Motor_x, Nema8* Motor_y, Nema8* Motor_z,Nema8 *Motor_PrintHead, DistanceSensor* DistanceM_x, DistanceSensor* DistanceM_y, DistanceSensor* DistanceM_z,
                     endSwitch* endSwitch_x, endSwitch* endSwitch_y, endSwitch* endSwitch_z, endSwitch* endSwitch_stop, lightBarrier* lightBarrier_x, lightBarrier* lightBarrier_y, lightBarrier* lightBarrier_z)
{
  this->Motor_x = Motor_x;
  this->Motor_y = Motor_y;
  this->Motor_z = Motor_z;
  this->Motor_PrintHead=Motor_PrintHead;
  this->DistanceM_x = DistanceM_x;
  this->DistanceM_y = DistanceM_y;
  this->DistanceM_z = DistanceM_z;
  this->endSwitch_x = endSwitch_x;
  this->endSwitch_y = endSwitch_y;
  this->endSwitch_z = endSwitch_z;
  this->lightBarrier_x = lightBarrier_x;
  this->lightBarrier_y = lightBarrier_y;
  this->lightBarrier_z = lightBarrier_z;
  this->endSwitch_stop = endSwitch_stop;
}

/******************************* API V3 ****************************
 * @brief API v3 comes with the new command design pattern and task scheduling.
 * API v3 will use task scheduling. The old API used non blocking functions.
 * All loops were converted into non blocking func using counters, where only
 * the main loop was used loop(). The API V3 will use blcoking functions with
 * internal loops, but this will no matter any more if task scheduling is included.
 * please use the API V3 if you are advanced programmer in c++
*/
// general method take the motor as ref
retVal Alignment::MoveDistanceMSafe(Nema8* Mref, int direction, float distance)
{
  if(Mref==Motor_x) MoveDistanceXloop(direction,distance);
  if(Mref==Motor_y) MoveDistanceYloop(direction,distance);
  if(Mref==Motor_z) MoveDistanceZloop(direction,distance);
}    
/************ new loops Move Calls for API v3 *************/
retVal Alignment::MoveDistanceXloop(int direction, float distance) // move motor X a given distance 
{     
      retVal X;
      do {
        yield();
      if (checkLimitUpX() || !isStopButtonPressed()){
      Serial.println("breaking move loop");
      Motor_x->StepCounter=0;
      X=ok;
      break;
      }
      X= MoveDistanceX(direction,distance);
      }
      while (X!=ok);
}  
retVal Alignment::MoveDistanceYloop(int direction, float distance) // move motor Y a given distance 
{
      retVal Y;
      do {
        yield();
      if (checkLimitUpY() || !isStopButtonPressed()){
      Serial.println("breaking move loop");
      Motor_y->StepCounter=0;
      Y=ok;
      break;
      }
      Y= MoveDistanceY(direction,distance);
      }
      while (Y!=ok);
} 
retVal Alignment::MoveDistanceZloop(int direction, float distance) // move motor Z a given distance 
{
      retVal Z;
      do {
        yield();
      if (checkLimitUpZ() || !isStopButtonPressed()){
      Serial.println("breaking move loop");
      Motor_z->StepCounter=0;
      Z=ok;
      break;
      }
      Z= MoveDistanceZ(direction,distance);
      }
      while (Z!=ok);
} 
retVal Alignment::RotateAnglePHloop(Nema8* Mref, int direction, float angle) // rotate motor ph a given angle 
{
        retVal ph;
        do {
              yield();
            if(!isStopButtonPressed()) 
            {
              Serial.println("breaking rotation loop"); 
              break;
            }
            ph= rotateAnglePH(direction, angle);
        }
        while (ph!=ok);
} 
// if endstop is pressed, break current event loop
// Note: this is not forseen as hardware complete reset
bool Alignment::isStopButtonPressed()
{
  if (endSwitch_stop->get_current_state(true)) return true;
  return false;
}

void Alignment::initFirmwareUnit()
{
    Motor_PrintHead->setDelay(STEP_DELAY_PRINTHEAD_MOTOR);
  DisableAll(off);
  initSensors();
}

// Basic Methods: API V2
inline retVal Alignment::StepOnceX(int direction) // move motor X one step
{
  Motor_x->setDirection(direction); // set direction
  Motor_x->stepOnce(); // loop steps
  return ok;
}
inline retVal Alignment::StepOnceY(int direction) // move motor Y one Step
{
  Motor_y->setDirection(direction);
  Motor_y->stepOnce();
  return ok;
}
inline retVal Alignment::StepOnceZ(int direction) // move motor Z one Step
{
  Motor_z->setDirection(direction); // move up
  Motor_z->stepOnce(); // move up
  return ok;
}
inline retVal Alignment::MoveDistanceX(int direction, float distance) // move motor X a given distance
{
  //static int stepCounterX = 0;
  int steps = ConvertDistanceToStep(distance);
  if (Motor_x->StepCounter < steps)
  {
    
    Motor_x->StepCounter++;
    StepOnceX(direction);
    #ifdef DEBUG
    Serial.println("required steps X:");
    Serial.println(steps);
    Serial.println("Steps counter X:");
    Serial.println(Motor_x->StepCounter);
    Serial.println("total steps counted X:");
    Serial.println(Motor_x->TotalStepCounted);
    #endif
    if (Motor_x->StepCounter == steps)
    {
      Motor_x->StepCounter = 0;
      return ok;
    }
  }
  return err;
}

retVal Alignment::MoveDistanceY(int direction, float distance) // move motor Y a given distance
{
  //static int stepCounterY = 0;
  int steps = ConvertDistanceToStep(distance);
  if (Motor_y->StepCounter < steps)
  {
    
    Motor_y->StepCounter++;
    StepOnceY(direction);
    #ifdef DEBUG
    Serial.println("required steps Y:");
    Serial.println(steps);
    Serial.println("Steps counter Y:");
    Serial.println(Motor_y->StepCounter);
    Serial.println("total steps counted Y:");
    Serial.println(Motor_y->TotalStepCounted);
    #endif
    if (Motor_y->StepCounter == steps)
    {
      Motor_y->StepCounter = 0;
      return ok;
    }
  }
  return err;
}
retVal Alignment::MoveDistanceZ(int direction, float distance) // move motor Z a given distance
{
  //static int stepCounterZ = 0;
  int steps = ConvertDistanceToStep(distance);
  if (Motor_z->StepCounter < steps)
  {
    
    Motor_z->StepCounter++;
    StepOnceZ(direction);
    #ifdef DEBUG
    Serial.println("required steps Z:");
    Serial.println(steps);
    Serial.println("Steps counter Z:");
    Serial.println(Motor_z->StepCounter);
    Serial.println("total steps counted Z:");
    Serial.println(Motor_z->TotalStepCounted);
    #endif
    if (Motor_z->StepCounter == steps)
    {
      Motor_z->StepCounter = 0;
      return ok;
    }
  }
  return err;
}
retVal Alignment::MoveDistanceAll(int direction, float distance) // move motor Z a given distance
{
  retVal X = MoveDistanceX(direction,distance);
  retVal Y = MoveDistanceY(direction,distance);
  retVal Z = MoveDistanceZ(direction,distance);
  if (X==ok && Y==ok && Z==ok) return ok;
  return err;
}
/*********** Move Angle *************/
retVal Alignment::MoveAngleX(int direction, float angle) // move motor X a given Angle
{
  //static int stepCounterX = 0;
  int steps = convertAngleToStep(angle);
  if (Motor_x->StepCounter < steps)
  {
    Motor_x->StepCounter++;
    StepOnceX(direction);
    if (Motor_x->StepCounter == steps)
    {
      Motor_x->StepCounter = 0;
      return ok;
    }
  }
  return err;
}
retVal Alignment::MoveAngleY(int direction, float angle) // move motor Y a given Angle
{
  //static int stepCounterY = 0;
  int steps = convertAngleToStep(angle);
  if (Motor_y->StepCounter < steps)
  {
    Motor_y->StepCounter++;
    StepOnceY(direction);
    if (Motor_y->StepCounter == steps)
    {
      Motor_y->StepCounter = 0;
      return ok;
    }
  }
  return err;
}
retVal Alignment::MoveAngleZ(int direction, float angle) // move motor Z a given Angle
{
  //static int stepCounterZ = 0;
  int steps = convertAngleToStep(angle);
  if (Motor_z->StepCounter < steps)
  {
    Motor_z->StepCounter++;
    StepOnceZ(direction);
    if (Motor_z->StepCounter == steps)
    {
      Motor_z->StepCounter = 0;
      return ok;
    }
  }
  return err;
}
retVal Alignment::MoveAngleAll(int direction, float Angle) // 
{
  retVal X = MoveAngleX(direction,Angle);
  retVal Y = MoveAngleY(direction,Angle);
  retVal Z = MoveAngleZ(direction,Angle);
  if (X==ok && Y==ok && Z==ok) return ok;
  return err;
}
/******** get sensors values **************/
inline double Alignment::getValueSensorX() // get mesured value on sensor X
{
  return DistanceM_x->getCurrentDistance();
}
inline double Alignment::getValueSensorY() // get mesured value on sensor Y
{
  return DistanceM_y->getCurrentDistance();
}
inline double Alignment::getValueSensorZ() // get mesured value on sensor X
{
  return DistanceM_z->getCurrentDistance();
}
/********** get reading endstopps *************/
inline bool Alignment::getReadingEndstopX() // get mesured Reading Endstop X
{
  return endSwitch_x->get_current_state(true);
}
inline bool Alignment::getReadingEndstopY() // get mesured Reading Endstop Y
{
  return endSwitch_y->get_current_state(true);
}
inline bool Alignment::getReadingEndstopZ() // get mesured Reading Endstop X
{
  return endSwitch_z->get_current_state(true);
}
/*********** get readings light barrier *************/
inline bool Alignment::getReadingLightBarrierX()
{
  return lightBarrier_x->get_current_state();
} // Alignment::t mesured Reading LightBarrier X
inline bool Alignment::getReadingLightBarrierY()
{
  return lightBarrier_y->get_current_state();
} // get mesured Reading LightBarrier Y
inline bool Alignment::getReadingLightBarrierZ()
{
  return lightBarrier_z->get_current_state();
} // get mesured Reading LightBarrier X

/************** check limit up ********************/
inline bool Alignment::checkLimitUpX() // check if  light barrier is traversed
{
  if (getReadingLightBarrierX() == lightBarrier_x->TraversedState) return true;
  return false;
}
inline bool Alignment::checkLimitUpY() // check if  light barrier is traversed
{
  if (getReadingLightBarrierY() == lightBarrier_y->TraversedState) return true;
  return false;
}
inline bool Alignment::checkLimitUpZ() // check if  light barrier is traversed
{
  if (getReadingLightBarrierZ() == lightBarrier_y->TraversedState) return true;
  return false;
}
inline bool Alignment::checkLimitUpXYZ() // check if  light barrier is traversed
{
  if (checkLimitUpX()==true && checkLimitUpY()==true && checkLimitUpZ()==true) return true;
  return false;
}
/********** check limit down ****************/
inline bool Alignment::checkLimitDownX() // check if  endstops is pressed
{
  if (getReadingEndstopX() == endSwitch_x->PressedState) return true;
  return false;
}
inline bool Alignment::checkLimitDownY() // check if  endstops is pressed
{
  if (getReadingEndstopY() == endSwitch_y->PressedState) return true;
  return false;
}
inline bool Alignment::checkLimitDownZ() // check if  endstops is pressed
{
  if (getReadingEndstopZ() == endSwitch_z->PressedState) return true;
  return false;
}
inline bool Alignment::checkLimitDownXYZ() // check if  light barrier is traversed
{
  if (checkLimitDownX()==true && checkLimitDownY()==true && checkLimitDownZ()==true) return true;
  return false;
}
// APIs V1 compatible
/************ go to reference down ************/
retVal Alignment::GoToReferenceDown()// API compatible func if new refrence is set
{
  return MoveHomeAll();
}
int Alignment::convertDistanceToStepMicros(float distance)// if distance is in micrometer
{
  return round(distance / Linear_travel_per_step) * MicroResolution; //distance in µm
}
int Alignment::convertAngleToStep(float angle) // if angle is degree
{
  return round(angle / Angle_per_step); //distance in mm / mm
}
// APIs V2 Complex
inline float Alignment::getDistancePrintHeadToMl()
{
#ifdef USE_GENERIC_FORMULA
  return AIR_GAP_BETWEEN_PRINTHEAD_AND_ML + getDistancePlatformToMlXYZ();
#else
  // in our case: sensor above
  return getDistancePlatformToMlXYZ() - DISTANCE_PRINTHEAD_PLATFORM;
#endif
}
/*********** get distance between printhead bottom and ML ************/
inline float Alignment::getDistancePrintHeadToMlX()
{
#ifdef USE_GENERIC_FORMULA
  return AIR_GAP_BETWEEN_PRINTHEAD_AND_ML + getDistancePlatformToMlX();
#else
  // in our case: sensor above
  return getDistancePlatformToMlX() - DISTANCE_PRINTHEAD_PLATFORM;
#endif
}
inline float Alignment::getDistancePrintHeadToMlY()
{
#ifdef USE_GENERIC_FORMULA
  return AIR_GAP_BETWEEN_PRINTHEAD_AND_ML + getDistancePlatformToMlY();
#else
  // in our case: sensor above
  return getDistancePlatformToMlY() - DISTANCE_PRINTHEAD_PLATFORM;
#endif
}
inline float Alignment::getDistancePrintHeadToMlZ()
{
#ifdef USE_GENERIC_FORMULA
  return AIR_GAP_BETWEEN_PRINTHEAD_AND_ML + getDistancePlatformToMlZ();
#else
  // in our case: sensor above
  return getDistancePlatformToMlZ() - DISTANCE_PRINTHEAD_PLATFORM;
#endif
}
/*********** get distance between platform bottom and and ML ************/
inline float Alignment::getDistancePlatformToMlX()
{
  return getValueSensorX() - MotorSensorHolderThickness;
}
inline float Alignment::getDistancePlatformToMlY()
{
  return getValueSensorY() - MotorSensorHolderThickness;
}
inline float Alignment::getDistancePlatformToMlZ()
{
  return getValueSensorZ() - MotorSensorHolderThickness;
}
float Alignment::getDistancePlatformToMlXYZ()
{
  return (getDistancePlatformToMlX() + getDistancePlatformToMlY() + getDistancePlatformToMlZ()) / 3;
}
retVal Alignment::GoToReferenceUp() // new reference up  with light barrier
{
  /**
    @brief go to ref up

  */
 // test with ph rotation
 //rotateFullRevPH(clk);
  // check if  light barrier is not traversed
  bool condition1 = (checkLimitUpX() == false) && (lightBarrier_x->IsTraversed == false);
  bool condition2 = (checkLimitUpY() == false) && (lightBarrier_y->IsTraversed == false);
  bool condition3 = (checkLimitUpZ() == false) && (lightBarrier_z->IsTraversed == false);
  // check if  light barrier is traversed
  bool Acondition1 = checkLimitUpX() == true;
  bool Acondition2 = checkLimitUpY() == true;
  bool Acondition3 = checkLimitUpZ() == true;
  // check if all light barrier are traversed
  bool OKcondition = lightBarrier_x->IsTraversed && lightBarrier_y->IsTraversed && lightBarrier_z->IsTraversed ;


  if (condition1)
  { //while light barrier not Traversed, move up
    // old implementation
    //Motor_x->setDirection(up); // set direction
    //Motor_x->stepOnce(); // loop steps
    StepOnceX(up);
  }
  if (Acondition1)
  {
    // if light barrier Traversed, reverse direction and go down by 1 mm, set Traversed true
    //Motor_x->setDirection(down); // set direction
    //Motor_x->step(ConvertDistanceToStep(1)); // loop steps
    MoveDistanceX(down, 1);
    lightBarrier_x->IsTraversed = true;
  }
  if (condition2)
  { //if light barrier not Traversed, move up
    //Motor_y->setDirection(up);
    //Motor_y->stepOnce();
    StepOnceY(up);
  }
  if (Acondition2)
  {
    //Motor_y->setDirection(down);
    //Motor_y->step(ConvertDistanceToStep(1)); //
    MoveDistanceY(down, 1);
    lightBarrier_y->IsTraversed = true;
  }
  if (condition3)
  { //if light barrier not Traversed, move up
    //Motor_z->setDirection(up); // move up
    //Motor_z->stepOnce(); // move up
    StepOnceZ(up);
  }
  if (Acondition3)
  {
    //Motor_z->setDirection(down); // move up
    //Motor_z->step(ConvertDistanceToStep(1)); // move up
    MoveDistanceZ(down, 1);
    lightBarrier_z->IsTraversed = true;
  }
  if (OKcondition) {
    lightBarrier_x->IsTraversed = false;
    lightBarrier_y->IsTraversed = false;
    lightBarrier_z->IsTraversed = false;
    Motor_x->TotalStepCounted=0;
    Motor_y->TotalStepCounted=0;
    Motor_z->TotalStepCounted=0;
    return ok; // this happens when all light barrier are contacted
  }
  return err;
}
    /************ increment counted steps inside class objects******/
void Alignment::incrementTotalStepCounted()
{//increment global step counted inside scoop of class 
  Motor_PrintHead->TotalStepCounted+=Motor_PrintHead->StepCounter;
  Motor_x->TotalStepCounted+=Motor_x->StepCounter;
  Motor_y->TotalStepCounted+=Motor_y->StepCounter;
  Motor_z->TotalStepCounted+=Motor_z->StepCounter;
}
    /********** safety step counter reset **********/
void Alignment::resetStepCounter()
{
  // this function will be called if any function that 
  Motor_PrintHead->StepCounter=0;
  Motor_x->StepCounter=0;
  Motor_y->StepCounter=0;
  Motor_z->StepCounter=0; 
}
retVal Alignment::calibratePrintHead() // new calibrate func using v2 methods
{
  /**
     @brief calibrate Print Head based on target distance
     @algorithm: get distance to ML on every Axis (X,Y,Z), move axis in respect to target distance to printhead ( deduced from another fucntion) until target distance is same on all axis
     @return retVal
  */
  DistanceM_x->IkeyenceRS232->getValueOutputHeadAll();
  // Flags
  bool XAligned = false, YAligned = false, ZAligned = false;
  //conditions
  double PHpositionX=getDistancePrintHeadToMlX();
  double PHpositionY=getDistancePrintHeadToMlY();
  double PHpositionZ=getDistancePrintHeadToMlZ();
  //safe conditions when unvalid mesurements: -FFFFFF 
  if (PHpositionX<0) PHpositionX=-PHpositionX;
  if (PHpositionY<0) PHpositionY=-PHpositionY;
  if (PHpositionZ<0) PHpositionZ=-PHpositionZ;

  bool XsmallerTarget = PHpositionX <= TargetDistancePHToMl + SensorThreashold; // if real distance smaller as target
  bool YsmallerTarget = PHpositionY <= TargetDistancePHToMl + SensorThreashold;
  bool ZsmallerTarget = PHpositionZ <= TargetDistancePHToMl + SensorThreashold;
  bool XbiggerTarget = PHpositionX >= TargetDistancePHToMl - SensorThreashold; // if real distance  distance bigger as target
  bool YbiggerTarget = PHpositionY >= TargetDistancePHToMl - SensorThreashold;
  bool ZbiggerTarget = PHpositionZ >= TargetDistancePHToMl - SensorThreashold;
  bool XequalTarget = PHpositionX <= TargetDistancePHToMl + SensorThreashold && PHpositionX >= TargetDistancePHToMl - SensorThreashold; // if mesured equal to target
  bool YequalTarget = PHpositionY <= TargetDistancePHToMl + SensorThreashold && PHpositionY >= TargetDistancePHToMl - SensorThreashold;
  bool ZequalTarget = PHpositionZ <= TargetDistancePHToMl + SensorThreashold && PHpositionZ >= TargetDistancePHToMl - SensorThreashold;

#ifdef DEBUG
  Serial.println("target distance in mm: "+ String(TargetDistancePHToMl));
  Serial.println("current d X in mm: "+String(PHpositionX));
  Serial.println("current d Y in mm: "+ String(PHpositionY));
  Serial.println("current d Z in mm: "+ String(PHpositionZ));
#endif
#ifdef DEBUG_
  Serial.println("target distance in mm: ");
  Serial.println(TargetDistancePHToMl);
  Serial.println("current d X in mm");
  Serial.println(DistanceM_x->getCurrentDistance());
  Serial.println("current d Y in mm");
  Serial.println(DistanceM_y->getCurrentDistance());
  Serial.println("current d Z in mm");
  Serial.println(DistanceM_z->getCurrentDistance());
#endif
  if (XsmallerTarget && XAligned == false)
  { // if d>0 go up by d_x
    if (checkLimitUpX() == false) StepOnceX(up);
  }
  // if d<0 go down by d_x
  if (XbiggerTarget && XAligned == false)
  {
    if (checkLimitDownX() == false) StepOnceX(down);
  }
  // if d=0 disable motor and set flag
  if (XequalTarget)
  {
    //Motor_x->enable(off); // disable motor
    XAligned = true;
  }
  if (YsmallerTarget && YAligned == false)
  {
    if (checkLimitUpY() == false) StepOnceY(up);
  }
  if (YbiggerTarget && YAligned == false)
  {
    if (checkLimitDownY() == false) StepOnceY(down);
  }
  // if d=0 disable motor and set flag
  if (YequalTarget)
  {
    //Motor_y->enable(off); // disable motor
    YAligned = true;
  }
  if (ZsmallerTarget && ZAligned == false)
  {
    if (checkLimitUpZ() == false) StepOnceZ(up);
  }
  if (ZbiggerTarget && ZAligned == false)
  {
    if (checkLimitDownZ() == false) StepOnceZ(down);
  }
  // if d=0 disable motor and set flag
  if (ZequalTarget)
  {
    //Motor_z->enable(off); // disable motor
    ZAligned = true;
  }
  // return ok if all motor sensors have approximate similar value with threashold
  if (XAligned && YAligned && ZAligned)
  {
    XequalTarget = false;
    YequalTarget = false;
    ZequalTarget = false;
    return ok;
  }
  return err;
}

/******************* Max Up/Down X, Y, Z ***********************/
retVal Alignment::StepDownXMax() {
  if (checkLimitDownX() == true) return ok;
  else {
    StepOnceX(down);
    return err;
  }
} // move x max down
retVal Alignment::StepDownYMax() {
  if (checkLimitDownY() == true) return ok;
  else {
    StepOnceY(down);
    return err;
  }
} // move y max down
retVal Alignment::StepDownZMax() {
  if (checkLimitDownZ() == true) return ok;
  else {
    StepOnceZ(down);
    return err;
  }
} // move z max down
retVal Alignment::StepUpXMax() {
  if (checkLimitUpX() == true) return ok;
  else {
    StepOnceX(up);
    return err;
  }
} // move x max Up
retVal Alignment::StepUpYMax() {
  if (checkLimitUpY() == true) return ok;
  else {
    StepOnceY(up);
    return err;
  }
} // move y max Up
retVal Alignment::StepUpZMax() {
  if (checkLimitUpZ() == true) return ok;
  else {
    StepOnceZ(up);
    return err;
  }
} // move z max Up
/********* Move Distance and check Limit ***************/
retVal Alignment::MoveDistanceXSafe(int direction, float distance)
{
  if (direction == up)
  {
    if (checkLimitUpX() == true) {
      Motor_x->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceX(direction, distance);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownX() == true) {
      Motor_x->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceX(direction, distance);
    }
  }
}
retVal Alignment::MoveDistanceYSafe(int direction, float distance)
{
  if (direction == up)
  {
    if (checkLimitUpY() == true) 
    {
      Motor_y->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceY(direction, distance); 
    }
  }
  if (direction == down)
  {
    if (checkLimitDownY() == true) 
    {
      Motor_y->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceY(direction, distance);
    }
  }
}
retVal Alignment::MoveDistanceZSafe(int direction, float distance)
{
  if (direction == up)
  {
    if (checkLimitUpZ() == true) 
    {
      Motor_z->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceZ(direction, distance);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownZ() == true) 
    {
      Motor_z->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceZ(direction, distance);
    }
  }
}
retVal Alignment::MoveDistanceAllSafe(int direction, float distance)
{
  if (direction == up)
  {
    if (checkLimitUpXYZ() == true) 
    {
      Motor_x->StepCounter=0;
      Motor_y->StepCounter=0;
      Motor_z->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceAll(direction, distance);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownXYZ() == true) 
    {
      Motor_x->StepCounter=0;
      Motor_y->StepCounter=0;
      Motor_z->StepCounter=0;
      return ok;
      }
    else {
      return MoveDistanceAll(direction, distance);
    }
  }
}
/******** move angle and chekc safety **************/
retVal Alignment::MoveAngleXSafe(int direction, float Angle)
{
  if (direction == up)
  {
    if (checkLimitUpX() == true) 
    {
      Motor_x->StepCounter=0;
      return ok;
      }
    else {
      return MoveAngleX(direction, Angle);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownX() == true) 
    {
      Motor_x->StepCounter=0;
      return ok;
      }
    else {
      return MoveAngleX(direction, Angle);
    }
  }
}
retVal Alignment::MoveAngleYSafe(int direction, float Angle)
{
  if (direction == up)
  {
    if (checkLimitUpY() == true) 
    {
      Motor_y->StepCounter=0;
      return ok;
      }
    else {
      return MoveAngleY(direction, Angle);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownY() == true) 
    {
      Motor_y->StepCounter=0;
      return ok;
      }
    else {
      return MoveAngleY(direction, Angle);
    }
  }
}
retVal Alignment::MoveAngleZSafe(int direction, float Angle)
{
  if (direction == up)
  {
    if (checkLimitUpZ() == true) 
    {
      Motor_z->StepCounter=0;
      return ok;
      }
    else {
      return MoveAngleZ(direction, Angle);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownZ() == true) 
    {
      Motor_z->StepCounter=0;
      return ok;
      }
    else {
      return MoveAngleZ(direction, Angle);
    }
  }
}
retVal Alignment::MoveAngleAllSafe(int direction, float Angle)
{
  if (direction == up)
  {
    if (checkLimitUpXYZ() == true) 
    {
     Motor_x->StepCounter=0;
     Motor_y->StepCounter=0;
     Motor_z->StepCounter=0;
      return ok;
    }
    else {
      return MoveAngleAll(direction, Angle);
    }
  }
  if (direction == down)
  {
    if (checkLimitDownXYZ() == true) 
    {
     Motor_x->StepCounter=0;
     Motor_y->StepCounter=0;
     Motor_z->StepCounter=0;
      return ok;
    }
    else {
      return MoveAngleAll(direction, Angle);
    }
  }
}

    /********** rotate printHead in clockweise/counter clockwise **********/
    retVal Alignment::StepOncePH(int direction)
    {
      Motor_PrintHead->setDirection(direction); // set direction
      Motor_PrintHead->stepOnce(); // loop steps
      return ok;
    } // move motor PH one step
    retVal Alignment::rotateFullRevPH(int direction)
    {
      return rotateAnglePH(direction, 360);
    } // move motor PH one rev
    retVal Alignment::rotateAnglePH(int direction, float Angle)
    {
      int steps = convertAngleToStep(Angle);
      if (Motor_PrintHead->StepCounter < steps)
      {
        Motor_PrintHead->StepCounter++;
        StepOncePH(direction);
        #ifdef DEBUG
        Serial.println("required steps:");
        Serial.println(steps);
        Serial.println("Steps counter:");
        Serial.println(Motor_PrintHead->StepCounter);
        Serial.println("total steps counted:");
        Serial.println(Motor_PrintHead->TotalStepCounted);
        #endif
        if (Motor_PrintHead->StepCounter == steps)
        {
          Motor_PrintHead->StepCounter = 0;
          return ok;
        }
      }
      return err;      
    } //rotate certain angle
/************* move printhead to referenc pos on x axis using distance sensor********/

retVal Alignment::movePhToRefX()
{
  // get sensors reading 
  DistanceM_x->IkeyenceRS232->getValueOutputHeadAll();
  // get value for x 
  double valueX=DistanceM_x->getCurrentDistance();
  // rotate printhead until value of X is FFFFF
  Serial.print("current distance sensor value of X: ");
  Serial.println(valueX);
  if (valueX != 0) 
  {
    Serial.println("moving to x axis ..");
    return rotateAnglePH(Motor_PrintHead->direction, 1.8);
  }
  else
  {
    Serial.println("X laser point reached, aligning printhead with x axis");
    return rotateAnglePH(Motor_PrintHead->direction, 25);
  }

}
/************* oscillate system ***********************/
    retVal Alignment::oscillateSys(float desired_angle, int num_revolutions, bool default_sens/*=clk*/, bool reverse_sense/*=true*/)
    {
      int steps_per_revolutions=200;
      bool sens_rotation=default_sens;
      bool counter_sens_rotation = !sens_rotation;
      float stepAngle=Angle_per_step;
      int num_rev_cw;
      int num_rev_ccw;
      double toRadian=180/PI;
      float radius=124.0;
      desired_angle*=toRadian;
      double beta_x;
      double teta_x;
      double p_x;
      double beta_y;
      double teta_y;
      double p_y;
      double beta_z;
      double teta_z;
      double p_z;
      double new_px;
      double old_px=0;
      double new_py;
      double old_py=0;
      double new_pz;
      double old_pz=0;
      if (reverse_sense)
      {
        num_rev_ccw,num_rev_cw=num_revolutions/2;
        // we assume to start from X
        for (int rev=0; rev<num_revolutions; rev++)
        {
          if(rev<num_rev_cw)// if we rotate in clk
          {
            for (int step=0; step<steps_per_revolutions; step++)
            {
              // print mototr will move one step (360)
              StepOncePH(sens_rotation);
              // formula:
              // x motor 
              beta_x=toRadian; //always be equal to radians before next
              beta_x*=(step+90);
              teta_x=desired_angle*sin(beta_x);
              p_x=radius*tan(teta_x); 
              new_px=p_x-old_px; 
              #ifdef DEBUG
              Serial.println("beta x:");
              Serial.println(beta_x);
              Serial.println("teta x:");
              Serial.println(teta_x);
              Serial.println("p x:");
              Serial.println(p_x);
              #endif
              if (new_px>0) MoveDistanceXSafe(up, new_px);
              else MoveDistanceXSafe(down, abs(new_px));
              old_px=new_px; 
              // y motor
              beta_y=toRadian;
              beta_y*=(step+120);
              teta_y=desired_angle*sin(beta_y);
              p_y=radius*tan(teta_y);
              new_py=p_y-old_py; 
              #ifdef DEBUG
              Serial.println("beta y:");
              Serial.println(beta_y);
              Serial.println("teta y:");
              Serial.println(teta_y);
              Serial.println("p y:");
              Serial.println(p_y);
              #endif
              if (new_py>0) MoveDistanceYSafe(up, new_py);
              else MoveDistanceYSafe(down, abs(new_py));
              old_py=new_py; 
              // z motor
              beta_z=toRadian;
              beta_z*=(step+240);
              teta_z=desired_angle*sin(beta_z);
              p_z=radius*tan(teta_z);
              new_pz=p_z-old_pz; 
              #ifdef DEBUG
              Serial.println("beta z:");
              Serial.println(beta_z);
              Serial.println("teta z:");
              Serial.println(teta_z);
              Serial.println("p z:");
              Serial.println(p_z);
              #endif
              if (new_pz>0) MoveDistanceZSafe(up, new_pz);
              else MoveDistanceZSafe(down, abs(new_pz));
              old_pz=new_pz; 
            }
          }
          else // roatae in ccw
          {
            for (int step=0; step<steps_per_revolutions; step++)
            {
              // print mototr will move one step (360)
              StepOncePH(counter_sens_rotation);
              // formula:
              // x motor 
              beta_x=toRadian;
              beta_x*=(step-90);//+250
              teta_x=desired_angle*sin(beta_x);
              p_x=radius*tan(teta_x); 
              new_px=p_x-old_px; 
              #ifdef DEBUG
              Serial.println("beta x:");
              Serial.println(beta_x);
              Serial.println("teta x:");
              Serial.println(teta_x);
              Serial.println("p x:");
              Serial.println(p_x);
              #endif
              if (new_px>0) MoveDistanceXSafe(up, new_px);
              else MoveDistanceXSafe(down, abs(new_px));
              old_px=new_px; 
              // y motor
              beta_y=toRadian;
              beta_y*=(step-120);
              teta_y=desired_angle*sin(beta_y);
              p_y=radius*tan(teta_y);
              new_py=p_y-old_py; 
              #ifdef DEBUG
              Serial.println("beta y:");
              Serial.println(beta_y);
              Serial.println("teta y:");
              Serial.println(teta_y);
              Serial.println("p y:");
              Serial.println(p_y);
              #endif
              if (new_py>0) MoveDistanceYSafe(up, new_py);
              else MoveDistanceYSafe(down, abs(new_py));
              old_py=new_py; 
              // z motor
              beta_z=toRadian;
              beta_z*=(step-240);
              teta_z=desired_angle*sin(beta_z);
              p_z=radius*tan(teta_z);
              new_pz=p_z-old_pz; 
              #ifdef DEBUG
              Serial.println("beta z:");
              Serial.println(beta_z);
              Serial.println("teta z:");
              Serial.println(teta_z);
              Serial.println("p z:");
              Serial.println(p_z);
              #endif
              if (new_pz>0) MoveDistanceZSafe(up, new_pz);
              else MoveDistanceZSafe(down, abs(new_pz));
              old_pz=new_pz; 
            }
          } 
        }
      }
      // if no sense of rotation should not be reversed
      else
      {
        for (int rev=0; rev<num_revolutions; rev++)
        {
            for (int step=0; step<steps_per_revolutions; step++)
            {
              // print mototr will move one step (360)
              StepOncePH(default_sens);
              // formula:
              // x motor 
              beta_x=toRadian;
              beta_x*=(step+90);
              teta_x=desired_angle*sin(beta_x);
              p_x=radius*tan(teta_x); 
              new_px=p_x-old_px; 
              if (new_px>0) MoveDistanceXSafe(up, new_px);
              else MoveDistanceXSafe(down, abs(new_px));
              old_px=new_px; 
              // y motor
              beta_y=toRadian;
              beta_y*=(step+120);
              teta_y=desired_angle*sin(beta_y);
              p_y=radius*tan(teta_y);
              new_py=p_y-old_py; 
              if (new_py>0) MoveDistanceYSafe(up, new_py);
              else MoveDistanceYSafe(down, abs(new_py));
              old_py=new_py; 
              // z motor
              beta_z=toRadian;
              beta_z*=(step+240);
              teta_z=desired_angle*sin(beta_z);
              p_z=radius*tan(teta_z);
              new_pz=p_z-old_pz; 
              if (new_pz>0) MoveDistanceZSafe(up, new_pz);
              else MoveDistanceZSafe(down, abs(new_pz));
              old_pz=new_pz; 
            }
          }        
      }

    }
/********** keyence sensors **********/
    #ifdef keyence
    retVal Alignment::initSensors()
    {
      //Keyence_base::listHeads();
      DistanceM_x->setKeyenceCom(); 
      return ok;
    }
    #endif
/*********************************************** API V1 *****************************************************/
/**
   @brief setup stuff to initialise enable, direction and so on

   @return retVal
*/
retVal Alignment::InitAlign(bool enable /*= on*/) {
  Motor_x->enable(enable); // set enable
  Motor_y->enable(enable); // set enable
  Motor_z->enable(enable); // set enable
  Motor_PrintHead->enable(enable); // set enable
  return ok;
}
retVal Alignment::EnableAll(bool enable /*= on*/) {
  Motor_x->enable(enable); // set enable
  Motor_y->enable(enable); // set enable
  Motor_z->enable(enable); // set enable
  Motor_PrintHead->enable(enable); // set enable
  return ok;
}
retVal Alignment::DisableAll(bool enable /*= of*/) {
  Motor_x->enable(enable); // set enable
  Motor_y->enable(enable); // set enable
  Motor_z->enable(enable); // set enable
  Motor_PrintHead->enable(enable); // set enable
  return ok;
}
/**
   @brief Move all motors home
   @algorithm: check if every motor endswitch is not pressed, then move Nema8 up
   @return retVal
*/
retVal Alignment::MoveHomeAll()
{
  /**
     @brief : move all motor down to ref

  */
#ifdef VIRTUAL
  return ok;
#endif
// test reverse rotation
//rotateFullRevPH(cclk);
  // check  if endstop is not pressed
  bool condition1 = (endSwitch_x->get_current_state(true) != endSwitch_x->PressedState) && (endSwitch_x->Ispressed == false);
  bool condition2 = (endSwitch_y->get_current_state(true) != endSwitch_y->PressedState) && (endSwitch_y->Ispressed == false);
  bool condition3 = (endSwitch_z->get_current_state(true) != endSwitch_z->PressedState) && (endSwitch_z->Ispressed == false);
  // check if endstop is pressed
  bool Acondition1 = endSwitch_x->get_current_state(true) == endSwitch_x->PressedState;
  bool Acondition2 = endSwitch_y->get_current_state(true) == endSwitch_y->PressedState;
  bool Acondition3 = endSwitch_z->get_current_state(true) == endSwitch_z->PressedState;
  // cehck if all pressed
  bool OKcondition = endSwitch_x->Ispressed && endSwitch_z->Ispressed && endSwitch_y->Ispressed;


  if (condition1)
  { //while endstop not pressed, move down
    Motor_x->setDirection(down); // set direction
    Motor_x->stepOnce(); // loop steps
  }
  if (Acondition1)
  {
    // if endstop pressed, reverse direction and go up by 1 mm, set pressed true
    Motor_x->setDirection(up); // set direction
    Motor_x->stepOnce(); // loop steps
    endSwitch_x->Ispressed = true;
  }
  if (condition2)
  { //if endstop not pressed, move down
    Motor_y->setDirection(down);
    Motor_y->stepOnce();
  }
  if (Acondition2)
  {
    Motor_y->setDirection(up);
    Motor_y->stepOnce(); //
    endSwitch_y->Ispressed = true;
  }
  if (condition3)
  { //if endstop not pressed, move down
    Motor_z->setDirection(down); // move down
    Motor_z->stepOnce(); // move down
  }
  if (Acondition3)
  {
    Motor_z->setDirection(up); // move down
    Motor_z->stepOnce(); // move down
    endSwitch_z->Ispressed = true;
  }
  if (OKcondition) {
    endSwitch_x->Ispressed = false;
    endSwitch_y->Ispressed = false;
    endSwitch_z->Ispressed = false;
    Motor_x->TotalStepCounted=0;
    Motor_y->TotalStepCounted=0;
    Motor_z->TotalStepCounted=0;

    return ok; // this happens when all endstop are contacted
  }
  return err;
}
/**
   @brief This is the main function to keep track of alignment during process
   @algorithm: compare value of distance sensor for each motor with target and calibrate
   @return retVal
*/
retVal Alignment::AlignLoop() {
  /**
     @brief TODO_:Better for loop for each Motor

  */
  DistanceM_x->IkeyenceRS232->getValueOutputHeadAll();

  // Flags
  //bool XAligned = false, YAligned = false, ZAligned = false;
  //conditions
  bool XsmallerTarget = DistanceM_x->getCurrentDistance() < double(TargetDistanceSensorToMl) + SensorThreashold; // if mesured distance smaller as target
  bool YsmallerTarget = DistanceM_y->getCurrentDistance() < double(TargetDistanceSensorToMl) + SensorThreashold;
  bool ZsmallerTarget = DistanceM_z->getCurrentDistance() < double(TargetDistanceSensorToMl) + SensorThreashold;
  bool XbiggerTarget = DistanceM_x->getCurrentDistance() > double(TargetDistanceSensorToMl) - SensorThreashold; // if mesured distance bigger as target
  bool YbiggerTarget = DistanceM_y->getCurrentDistance() > double(TargetDistanceSensorToMl) - SensorThreashold;
  bool ZbiggerTarget = DistanceM_z->getCurrentDistance() > double(TargetDistanceSensorToMl) - SensorThreashold;
  bool XequalTarget = DistanceM_x->getCurrentDistance() <= double(TargetDistanceSensorToMl) + SensorThreashold && DistanceM_x->getCurrentDistance() >= double(TargetDistanceSensorToMl) - SensorThreashold; // if mesured equal to target
  bool YequalTarget = DistanceM_y->getCurrentDistance() <= double(TargetDistanceSensorToMl) + SensorThreashold && DistanceM_y->getCurrentDistance() >= double(TargetDistanceSensorToMl) - SensorThreashold;
  bool ZequalTarget = DistanceM_z->getCurrentDistance() <= double(TargetDistanceSensorToMl) + SensorThreashold && DistanceM_z->getCurrentDistance() >= double(TargetDistanceSensorToMl) - SensorThreashold;

#ifdef DEBUG_ALIGN
  Serial.println("target distance in mm");
  Serial.println(TargetDistanceSensorToMl);
  Serial.println("target -+ threashold equal 1 in mm");
  Serial.println("current distance X in mm");
  Serial.println(DistanceM_x->getCurrentDistance());
  Serial.println("current distance Y in mm");
  Serial.println(DistanceM_y->getCurrentDistance());
  Serial.println("current distance Z in mm");
  Serial.println(DistanceM_z->getCurrentDistance());
#endif

  if (XsmallerTarget && XAligned == false)
  { // if d>0 go down by d_x
    Motor_x->setDirection(up); // set direction
    //Motor_x->step(ConvertDistanceToStep(d_x)); // move the distance
    Motor_x->stepOnce();
  }
  // if d<0 go up by d_x
  if (XbiggerTarget && XAligned == false)
  {
    Motor_x->setDirection(down); // set direction
    //Motor_x->step(ConvertDistanceToStep(d_x)); // move the distance
    Motor_x->stepOnce();
  }
  // if d=0 disable motor and set flag
  if (XequalTarget)
  {
    //Motor_x->enable(off); // disable motor
    XAligned = true;
  }
  if (YsmallerTarget && YAligned == false)
  {
    Motor_y->setDirection(up);
    //Motor_y->step(ConvertDistanceToStep(d_y));
    Motor_y->stepOnce();
  }
  if (YbiggerTarget && YAligned == false)
  {
    Motor_y->setDirection(down);
    //Motor_y->step(ConvertDistanceToStep(d_y));
    Motor_y->stepOnce();
  }
  // if d=0 disable motor and set flag
  if (YequalTarget)
  {

    //Motor_y->enable(off); // disable motor
    YAligned = true;
  }
  if (ZsmallerTarget && ZAligned == false)
  {
    Motor_z->setDirection(up);
    //Motor_z->step(ConvertDistanceToStep(d_z));
    Motor_z->stepOnce();
  }
  if (ZbiggerTarget && ZAligned == false)
  {
    Motor_z->setDirection(down);
    //Motor_z->step(ConvertDistanceToStep(d_z));
    Motor_z->stepOnce();
  }
  // if d=0 disable motor and set flag
  if (ZequalTarget)
  {

    //Motor_z->enable(off); // disable motor
    ZAligned = true;
  }
  // return ok if all motor sensors have approximate similar value with threashold
  if (XAligned && YAligned && ZAligned)
  {
  
    XequalTarget = false;
    YequalTarget = false;
    ZequalTarget = false;
    return ok;
  }
  return err;
}

// Move Up and Down using max value
retVal Alignment::MoveUp(bool x = true, bool y = true, bool z = true, bool checkLimit = false) {
  bool all = false;
  if (x && y && z) {
    all = true;
  }
#ifdef DEBUG_UP
  Serial.println("max allowed distance to up");
  Serial.println(RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold);
  Serial.println("current distance X in mm");
  Serial.println(getMaxX());
  Serial.println("current distance Y in mm");
  Serial.println(getMaxY());
  Serial.println("current distance Z in mm");
  Serial.println(getMaxZ());
#endif
  Motor_x->setDirection(up);
  Motor_y->setDirection(up);
  Motor_z->setDirection(up);

  if (x) {
    if (checkLimit) {
      if (getMaxX() <= RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold) {
        Motor_x->stepOnce();
      }
      else {
        xUpMax = true;
        Serial.println("finished up X MAx");
        if (!all) return ok;
      }
    }
    else {
      Motor_x->stepOnce();
    }
  }
  if (y) {
    if (checkLimit) {
      if (getMaxY() <= RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold) {
        Motor_y->stepOnce();
      }
      else {
        yUpMax = true;
        Serial.println("finished up Y MAx");
        if (!all) return ok;
      }
    }
    else {
      Motor_y->stepOnce();
    }
  }
  if (z) {
    if (checkLimit) {
      if (getMaxZ() <= RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold) {
        Motor_z->stepOnce();
      }
      else {
        zUpMax = true;
        Serial.println("finished up Z MAx");
        if (!all) return ok;
      }
    }
    else {
      Motor_z->stepOnce();
    }
  }
  if (all) {
    if (xUpMax && yUpMax && zUpMax) {
      allUpMax = true;
      xUpMax = false;
      yUpMax = false;
      zUpMax = false;
#ifdef DEBUG
      Serial.println("finish command Max up");
#endif
      return ok;
    }
  }
}
retVal Alignment::MoveDown(bool x = true, bool y = true, bool z = true, bool checkLimit = false) {
  bool all = false;
  if (x && y && z) {
    all = true;
  }
  Motor_x->setDirection(down);
  Motor_y->setDirection(down);
  Motor_z->setDirection(down);
#ifdef DEBUG_DOWN
  Serial.println("max allowed distance to down");
  Serial.println(RodLength_EndeffectorThickness);
  Serial.println("current distance X in mm");
  Serial.println(getMinX());
  Serial.println("current distance Y in mm");
  Serial.println(getMinY());
  Serial.println("current distance Z in mm");
  Serial.println(getMinZ());
#endif
  if (x) {
    if (checkLimit) {
      if (getMinX() >= RodLength_EndeffectorThickness + SensorThreashold) {
        Motor_x->stepOnce();
      }
      else {
        xDownMax = true;
        Serial.println("finished down X MAx");
        if (!all) return ok;
      }
    }
    else {
      Motor_x->stepOnce();
    }
  }
  if (y) {
    if (checkLimit) {
      if (getMinY() >= RodLength_EndeffectorThickness + SensorThreashold) {
        Motor_y->stepOnce();
      }
      else {
        yDownMax = true;
        Serial.println("finished down Y MAx");
        if (!all) return ok;


      }
    }
    else {
      Motor_y->stepOnce();
    }
  }
  if (z) {
    if (checkLimit) {
      if (getMinZ() >= RodLength_EndeffectorThickness + SensorThreashold) {
        Motor_z->stepOnce();
      }
      else {
        zDownMax = true;
        Serial.println("finished down Z MAx");
        if (!all) return ok;


      }
    }
    else {
      Motor_z->stepOnce();
    }
  }
  if (all) {
    if (xDownMax && yDownMax && zDownMax) {
      allDownMax = true;
      xDownMax = false;
      yDownMax = false;
      zDownMax = false;
#ifdef DEBUG
      Serial.println("finish command Max down");
#endif
      return ok;
    }
  }
}
// Move up and down to distance
retVal Alignment::MoveUpTo(bool x = true, bool y = true, bool z = true, bool checkLimit = false, float distance = 0) {
  xUpDistanceArrived = false;
  yUpDistanceArrived = false;
  zUpDistanceArrived = false;
  allUpDistanceArrived = false;
  bool all = false;
  if (x && y && z) {
    all = true;
  }
  Motor_x->setDirection(up);
  Motor_y->setDirection(up);
  Motor_z->setDirection(up);

#ifdef DEBUG_UP_DISTANCE
  Serial.println("max allowed distance to up");
  Serial.println(RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold);
  Serial.println("current distance X in mm");
  Serial.println(getMaxX());
  Serial.println("current distance Y in mm");
  Serial.println(getMaxY());
  Serial.println("current distance Z in mm");
  Serial.println(getMaxZ());
#endif
  if (x) {
    if (checkLimit) {
      if (getMaxX() < RodLength_EndeffectorThickness + LeadScrewLEngth) {
        Motor_x->stepOnce();
        //Motor_x->step(ConvertDistanceToStep(distance));
      } if (getMaxX() >= RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold) {
        xUpDistanceArrived = true;
        if (!all) return ok;
      }
    }
    else {
      Motor_x->step(ConvertDistanceToStep(distance));
    }
  }
  if (y) {
    if (checkLimit) {
      if (getMaxY() < RodLength_EndeffectorThickness + LeadScrewLEngth) {
        //Motor_y->step(ConvertDistanceToStep(distance));
        Motor_y->stepOnce();

      } if (getMaxY() >= RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold) {
        yUpDistanceArrived = true;
        if (!all) return ok;
      }
    }
    else {
      Motor_y->step(ConvertDistanceToStep(distance));
    }
  }
  if (z) {
    if (checkLimit) {
      if (getMaxZ() < RodLength_EndeffectorThickness + LeadScrewLEngth) {
        Motor_z->stepOnce();

        //Motor_z->step(ConvertDistanceToStep(distance));
      } if (getMaxZ() >= RodLength_EndeffectorThickness + LeadScrewLEngth + SensorThreashold) {
        zUpDistanceArrived = true;
        if (!all) return ok;
      }
    }
    else {
      Motor_z->step(ConvertDistanceToStep(distance));
    }
  }
  if (all) {
    if (xUpDistanceArrived && yUpDistanceArrived && zUpDistanceArrived) {
      xUpDistanceArrived = false;
      yUpDistanceArrived = false;
      zUpDistanceArrived = false;
      allUpDistanceArrived = true;
      return ok;
    }
  }
}
retVal Alignment::MoveDownTo(bool x = true, bool y = true, bool z = true, bool checkLimit = false, float distance = 0) {
  xDownDistanceArrived = false;
  yDownDistanceArrived = false;
  zDownDistanceArrived = false;
  allDownDistanceArrived = true;

  bool all = false;
  if (x && y && z) {
    all = true;
  }
  Motor_x->setDirection(down);
  Motor_y->setDirection(down);
  Motor_z->setDirection(down);
#ifdef DEBUG_DOWN_DISTANCE
  Serial.println("max allowed distance to down");
  Serial.println(RodLength_EndeffectorThickness);
  Serial.println("current distance X in mm");
  Serial.println(getMinX());
  Serial.println("current distance Y in mm");
  Serial.println(getMinY());
  Serial.println("current distance Z in mm");
  Serial.println(getMinZ());
#endif
  if (x) {
    if (checkLimit) {
      if (getMinX() > RodLength_EndeffectorThickness) {
        //Motor_x->step(ConvertDistanceToStep(distance));
        Motor_x->stepOnce();

      } if (getMinX() <= RodLength_EndeffectorThickness + SensorThreashold) {
        xDownDistanceArrived = true;
        if (!all) return ok;
      }
    }
    else {
      Motor_x->step(ConvertDistanceToStep(distance));
    }
  }
  if (y) {
    if (checkLimit) {
      if (getMinY() > RodLength_EndeffectorThickness) {
        //Motor_y->step(ConvertDistanceToStep(distance));
        Motor_y->stepOnce();

      } if (getMinY() <= RodLength_EndeffectorThickness + SensorThreashold) {
        yDownDistanceArrived = true;
        if (!all) return ok;
      }
    }
    else {
      Motor_y->step(ConvertDistanceToStep(distance));
    }
  }
  if (z) {
    if (checkLimit) {
      if (getMinZ() > RodLength_EndeffectorThickness) {
        //Motor_z->step(ConvertDistanceToStep(distance));
        Motor_z->stepOnce();

      } if (getMinZ() <= RodLength_EndeffectorThickness + SensorThreashold) {
        zDownDistanceArrived = true;
        if (!all) return ok;
      }
    }
    else {
      Motor_z->step(ConvertDistanceToStep(distance));
    }
  }
  if (all) {
    if (xDownDistanceArrived && yDownDistanceArrived && zDownDistanceArrived) {
      xDownDistanceArrived = false;
      yDownDistanceArrived = false;
      zDownDistanceArrived = false;
      allDownDistanceArrived = true;
      return ok;
    }
  }
}
/**
   @brief get the real distance based on mechanical construction in this setup

   @return float
*/
float Alignment::getRemainingDistanceZ() {
  // make the conversion to the actual value based on the parameters in the config file:
  // subsitute the length of rod, endeffector and sensor holder
  float mesured = DistanceM_z->getCurrentDistance();
  float remainingDistance = mesured - (RodLength + EndeffectorThickness + SensorThickness);
  return remainingDistance;
}

float Alignment::getRemainingDistanceY() {
  // make the conversion to the actual value based on the parameters in the config file:
  // subsitute the length of rod, endeffector and sensor holder
  float mesured = DistanceM_y->getCurrentDistance();
  float remainingDistance = mesured - (RodLength + EndeffectorThickness + SensorThickness);
  return remainingDistance;
}
float Alignment::getRemainingDistanceX() {
  // make the conversion to the actual value based on the parameters in the config file:
  // subsitute the length of rod, endeffector and sensor holder
  float mesured = DistanceM_x->getCurrentDistance();
  float remainingDistance = mesured - (RodLength + EndeffectorThickness + SensorThickness);
  return remainingDistance;
}
/**
   @brief get mesured values minus thickness of sensor: equal to 0 position

   @return float
*/
float Alignment::getMinX() // calculate the height over values
{
  float mesured = DistanceM_x->getCurrentDistance();
  float MinX = mesured + SensorThickness;
  return MinX;
}

float Alignment::getMinY() // calculate the height over values
{
  float mesured = DistanceM_y->getCurrentDistance();
  float MinY = mesured + SensorThickness;
  return MinY;
}

float Alignment::getMinZ() // calculate the height over values
{
  float mesured = DistanceM_z->getCurrentDistance();
  float MinZ = mesured + SensorThickness;
  return MinZ;
}

float Alignment::getMaxX() // calculate the height over values
{
  float MaxX = getMinX() + LeadScrewLEngth - (MotorLength + MotorSensorHolderThickness);
  return MaxX;
}

float Alignment::getMaxY() // calculate the height over values
{
  float MaxY = getMinY() + LeadScrewLEngth - (MotorLength + MotorSensorHolderThickness);
  return MaxY;
}

float Alignment::getMaxZ() // calculate the height over values
{
  float MaxZ = getMinZ() + LeadScrewLEngth - (MotorLength + MotorSensorHolderThickness);
  return MaxZ;
}
/*
********** new Functions features V2 *************
*/
float Alignment::getCurrentPosX()
{
  float ZeroPos = EndeffectorThickness + RodLength + MotorSensorHolderThickness; //zeor position
  float CurrentPos = DistanceM_x->getCurrentDistance() - ZeroPos; // pos relativ to zero pos
}
float Alignment::getCurrentPosY()
{
  float ZeroPos = EndeffectorThickness + RodLength + MotorSensorHolderThickness; //zeor position
  float CurrentPos = DistanceM_y->getCurrentDistance() - ZeroPos;
}
float Alignment::getCurrentPosZ()
{
  float ZeroPos = EndeffectorThickness + RodLength + MotorSensorHolderThickness; //zeor position
  float CurrentPos = DistanceM_z->getCurrentDistance() - ZeroPos;
}

float Alignment::CheckBoundaryX(float targetDistance, int direction)
{
  if (direction == up) {
    if (getCurrentPosX() + targetDistance > AllowedPath) {
      Serial.print("out of limit, adjusting new target");
      targetDistance = AllowedPath - getCurrentPosX();
      Serial.print(targetDistance);

      Motor_x->step(ConvertDistanceToStep(targetDistance));
    }
    Motor_x->step(ConvertDistanceToStep(targetDistance));
  }
  if (direction == down) {
    if (getCurrentPosX() - targetDistance > AllowedPath) {
      Serial.print("out of limit, adjusting new target");
      targetDistance = getCurrentPosX() - AllowedPath;
      Serial.print(targetDistance);

      Motor_x->step(ConvertDistanceToStep(targetDistance));
    }
    Motor_x->step(ConvertDistanceToStep(targetDistance));
  }
}

// TODO: write all functions left

/**
   @brief convert distance in mm or µm to step or microstep
   @param distance
   @return int
*/
int Alignment::ConvertDistanceToStep(float distance) {
  return round(distance / Linear_travel_per_step); //distance in mm / mm
}
/**
   @brief set new target distance to ML
   @param distance
   @return retVal
*/
retVal Alignment::setTargetDistancePHToML(float distance) { //set target distance between PH and ML
  TargetDistancePHToMl = distance;
  #ifdef DEBUG
  Serial.println("new target distance set:");
  Serial.println(TargetDistancePHToMl);
  #endif 
  return ok;
}
retVal Alignment::setTargetDistanceSensorToML(float distance) { //set target distance between PH and ML
  TargetDistanceSensorToMl = distance;
  #ifdef DEBUG
  Serial.println("new target distance set:");
  Serial.println(TargetDistanceSensorToMl);
  #endif 
  return ok;
}