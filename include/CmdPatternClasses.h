/**
 * @file CmdPatternClasses.h
 * @author sami dhiab (sami@theion.de)
 * @brief interface Command &Invoker and Classes Definition here
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _CMDPATTERNCLASSES_
#define _CMDPATTERNCLASSES_
#include "Alignment.hpp"
#include "Reset.h"
#include "Sleep.h"
#include "UUID.hpp"
#include "StateManager.hpp"

// command pattern Base
class ICommand {
 // private: implement a receiver reference
 public:
    virtual ~ICommand(){}
    virtual void execute() = 0;
    virtual void undo() = 0;
};
/********* Internal Commnands ***********/
// template command get uuid
 class getUUID : public ICommand {
 private:
  UUID_MANAGER& idObj;
  String UUID_;
 public:
  getUUID(UUID_MANAGER& idObj):idObj(idObj){}
  virtual void execute() {
  Serial.println( "execute get uuid"); 
    UUID_=idObj.get_UUID_EEPROM();
    Serial.println(UUID_); }
  virtual void undo() {
    Serial.println(UUID_);
  }
};
// template command set uuid
 class setUUID : public ICommand {
 private:
  UUID_MANAGER& idObj;
  String old_UUID_;
  String new_UUID_;
 public:
  setUUID(UUID_MANAGER& idObj, String uuid):idObj(idObj), new_UUID_(uuid){}
  virtual void execute() {
  Serial.println( "execute set uuid"); 
    old_UUID_=idObj.get_UUID_EEPROM();
    idObj.set_UUID_EEPROM(new_UUID_);
    Serial.println(new_UUID_); }
  virtual void undo() {
    idObj.set_UUID_EEPROM(new_UUID_);
    Serial.println(old_UUID_);
  }
};
// reset hardware
 class ResetDevice : public ICommand {
 private:
  ResetHardware& reset;
 public:
  ResetDevice(ResetHardware& reset):reset(reset){}
  virtual void execute() {
  //Serial.println( "execute reset"); 
  reset.soft_reset(); }
  virtual void undo() {}
};
// sleep hardware
 class SleepDevice : public ICommand {
 private:
  SleepHardware& sleep;
 public:
  SleepDevice(SleepHardware& sleep):sleep(sleep){}
  virtual void execute() {
  //Serial.println( "execute sleep"); 
  sleep.Sleep(); }
  virtual void undo() {}
};
/********** Motor enable/disable*********/
 class EnableMotorCmd : public ICommand {
 private:
 Nema8& M;
 public:
  EnableMotorCmd(Nema8& motor) :M(motor){}
  virtual void execute() {
  Serial.println( "execute enable motor"); 
  M.enable(on);
  }
  virtual void undo() {
    Serial.println( "execute disable motor"); 
    M.enable(off);
  }
};

/**************** GET ******************/
// template command get motor
 class getMotorCmd : public ICommand {
 private:
 Nema8& M;
 int oldVal;
 public:
  getMotorCmd(Nema8& motor) :M(motor){}
  virtual void execute() {
  Serial.println( "execute get"); 
  // here oldVal=M.get();
  }
  virtual void undo() {
    Serial.println(oldVal);
  }
};
// concrete command class get speed
class getMotorSpeedCmd : public ICommand {
 private:
 Nema8& M;
 int oldVal;
 public:
  getMotorSpeedCmd(Nema8& motor):M(motor){}
   virtual void execute() {
    Serial.println( "execute get speed");
    oldVal=M.getSpeed();
    Serial.println(oldVal); }
  virtual void undo() {
    Serial.println(oldVal);
  }
};
class getMotorDirectionCmd : public ICommand {
 private:
 Nema8& M;
 int oldVal;
 public:
  getMotorDirectionCmd(Nema8& motor):M(motor){}
  virtual void execute() {
    Serial.println( "execute get direction");
    oldVal=M.getDirection(); }
  virtual void undo() {
    Serial.println(oldVal);
  }
};
class getMotorDelayCmd : public ICommand {
 private:
 Nema8& M;
 int oldVal;
 public:
  getMotorDelayCmd(Nema8& motor):M(motor){}
  virtual void execute() {
    Serial.println( "execute get delay");
    oldVal=M.getDelay(); }
  virtual void undo() {
    Serial.println(oldVal);
  }
};


/*********************** SET *************************/
// template command motor set
class setMotorCmd : public ICommand {
 private:
 Nema8& M;
 int val;
 int old=0;
 public:
  setMotorCmd(Nema8& motor, int val) :M(motor), val(val){}
  virtual void execute() {
    Serial.println( "execute set"); 
    // old=get();
    }
  virtual void undo() {
    //  set(old);
  }
};
// concrete command class set speed
class setMotorSpeedCmd : public ICommand {
 private:
 Nema8& M;
 int val;
 int old=0;
 public:
  setMotorSpeedCmd(Nema8& motor, int val):M(motor), val(val){}
  virtual void execute() {
    Serial.println( "execute set speed");
    old=M.getSpeed();
    M.setSpeed(val); }
  virtual void undo() {
    M.setSpeed(old);
  }
};
class setMotorDirectionCmd : public ICommand {
 private:
 Nema8& M;
 int val;
 int old=0;
 public:
  setMotorDirectionCmd(Nema8& motor, int val):M(motor), val(val){}
  virtual void execute() {
    Serial.println( "execute set direction");
    old=M.getDirection();
    M.setDirection(val); }
  virtual void undo() {
    M.setDirection(old);
  }
};
class setMotorDelayCmd : public ICommand {
 private:
 Nema8& M;
 int val;
 int old=0;
 public:
  setMotorDelayCmd(Nema8& motor, int val):M(motor),val(val){}
  virtual void execute() {
    Serial.println( "execute set delay");
    old=M.getDelay();
    M.setDelay(val); }
  virtual void undo() {
    M.setDelay(old);
  }
};



/**************************** MOVE ******************************/
// Template move
class MoveMotorCmd : public ICommand {
 private:
 Nema8& M;
 int val;
 int old=0;
 public:
  MoveMotorCmd(Nema8& motor, int val) :M(motor), val(val){}
  virtual void execute() {
    Serial.println( "execute set"); 
    // old=get();
    }
  virtual void undo() {
    //  set(old);
  }
};
// concrete implementation move up
class MoveMotorUpCmd : public ICommand {
 private:
 Nema8& M;
 Alignment& Al;
 float val;
 public:
  MoveMotorUpCmd(Nema8& motor, Alignment& AL, float val) :M(motor), Al(AL), val(val){}
  virtual void execute() {
    Serial.println( "execute move up"); 
    Al.MoveDistanceMSafe(&M, up, val);    
    // move down by same distance is the undo cmd
    }
  virtual void undo() {
    Serial.println( "execute move down"); 
    Al.MoveDistanceMSafe(&M, down, val);
  }
};
class MoveMotorDownCmd : public ICommand {
 private:
 Nema8& M;
 Alignment& Al;
 float val;
 public:
  MoveMotorDownCmd(Nema8& motor, Alignment& AL, float val) :M(motor), Al(AL), val(val){}
  virtual void execute() {
    Serial.println( "execute move down"); 
    Al.MoveDistanceMSafe(&M, down, val);
    // move down by same distance is the undo cmd
    }
  virtual void undo() {
    Serial.println( "execute up down"); 
    Al.MoveDistanceMSafe(&M, up, val);
  }
};
/**************************** ROTATE ******************************/
// Template rotate
class RotateMotorCmd : public ICommand {
 private:
 Nema8& M;
 int val;
 int old=0;
 public:
  RotateMotorCmd(Nema8& motor, int val) :M(motor), val(val){}
  virtual void execute() {
    Serial.println( "execute set"); 
    // old=get();
    }
  virtual void undo() {
    //  set(old);
  }
};
class RotateMotorClkCmd : public ICommand {
 private:
 Nema8& M;
 Alignment& Al;
 float val;
 public:
  RotateMotorClkCmd(Nema8& motor, Alignment& AL, float val) :M(motor), Al(AL), val(val){}
  virtual void execute() {
    Serial.println( "execute rotate clk"); 
    Al.RotateAnglePHloop(&M, clk, val);
    // move down by same distance is the undo cmd
    }
  virtual void undo() {
    Serial.println( "execute rotate cclk"); 
    Al.RotateAnglePHloop(&M, cclk, val);
  }
};
class RotateMotorCclkCmd : public ICommand {
 private:
 Nema8& M;
 Alignment& Al;
 float val;
 public:
  RotateMotorCclkCmd(Nema8& motor, Alignment& AL, float val) :M(motor), Al(AL), val(val){}
  virtual void execute() {
    Serial.println( "execute rotate cclk"); 
    Al.RotateAnglePHloop(&M, cclk, val);
    // move down by same distance is the undo cmd
    }
  virtual void undo() {
    Serial.println( "execute rotate clk"); 
    Al.RotateAnglePHloop(&M, clk, val);
  }
};
/***************** Sensor Commands **********/

/**************** GET ******************/
// template command get sensor
 class getSensorCmd : public ICommand {
 private:
 DistanceSensor& S;
 int oldVal;
 public:
  getSensorCmd(DistanceSensor& Sensor) :S(Sensor){}
  virtual void execute() {
  Serial.println( "execute get"); 
  // here oldVal=M.get();
  }
  virtual void undo() {
    Serial.println(oldVal);
  }
};
// concrete command class get speed
class getSensorValueCmd : public ICommand {
 private:
 DistanceSensor& S;
 double oldVal;
 public:
  getSensorValueCmd(DistanceSensor& Sensor):S(Sensor){}
   virtual void execute() {
    Serial.println( "execute get Value");
    oldVal=S.getCurrentDistance();
    Serial.println(oldVal); }
  virtual void undo() {
    Serial.println(oldVal);
  }
};

/********** Unit aka Firmware Commands ************/
// as a convention, to control the firmware with given commands,
// these commands must be defined via classes, then Unit aka 
// firmware invoker is responsible for requesting cmds.
// Why do we need unit class? simply because it is easier to control
// a complete unit of receivers with simple cmd. Motors, Sensors, endstops, 
// lightbarriers {x,y,z} make the unit aka firmware alignment. 
// the invoker FirmwareUnit can indirectly make requests to all of these receivers.

class FirmwareUnit: public Alignment{};
/**************** GET ******************/
// template command get sensor
 class CalibrateCmd : public ICommand {
 private:
 Alignment& FU;
 float target;
 int oldVal;
 public:
  CalibrateCmd(Alignment& Funit, float target): FU(Funit), target(target){}
  virtual void execute() {
  Serial.println( "execute calibrate"); 
  FU.setTargetDistancePHToML(target);
  FU.calibratePrintHead();
  }
  virtual void undo() {
    Serial.println("no undo cmd here");
  }
};
/******* Base class invoker template *********/
class Invoker{
  private:
    // template commands to add
    ICommand *on_start_cmd;
    ICommand *on_finish_cmd;
 public:
 //clean up
  ~Invoker() {
  delete  on_finish_cmd;
  delete on_start_cmd;
  }
  void SetOnStart(ICommand *command){
    this->on_start_cmd=command;
  }
  void start() {
    Serial.println("starting..");
    if (this->on_start_cmd) {
      this->on_start_cmd->execute();
    }
  }
  void SetOnfinish(ICommand *command){
    this->on_finish_cmd=command;
  }
  void finish() {
    Serial.println("finishing..");
    if (this->on_finish_cmd) {
      this->on_finish_cmd->execute();
    }
  }
};
/********** Unit/Firmware invoker *************/
// see motor invoker for template
class FirmInvoker{
private:
  ICommand *on_calibrate;
 public:
  ~FirmInvoker() {
  delete on_calibrate;
  }
// On set function assign command
  void SetOnCalibrate(ICommand *command){
    this->on_calibrate=command;
  }
  void calibrate() {
    Serial.println("calibrating..");
    if (this->on_calibrate) {
      this->on_calibrate->execute();
    }
  }
};








/**************** Invoker****************/
/**
 * The Invoker is associated with one or several commands. It sends a request to
 * the command.
 */
class MotorInvoker {
 private:
  ICommand *on_start_;
  ICommand *on_finish_;
  ICommand *on_move_up;
  ICommand *on_move_down;
  ICommand *on_rotate_clk;
  ICommand *on_rotate_Cclk;
  ICommand *on_get_speed;
  ICommand *on_get_delay;
  ICommand *on_get_direction;
  ICommand *on_set_speed;
  ICommand *on_set_delay;
  ICommand *on_set_direction;
 public:
  ~MotorInvoker() {
  delete on_start_;
  delete on_finish_;
  delete on_move_up;
  delete on_move_down;
  delete on_rotate_clk;
  delete on_rotate_Cclk;
  delete on_get_speed;
  delete on_get_delay;
  delete on_get_direction;
  delete on_set_speed;
  delete on_set_delay;
  delete on_set_direction;
  }
// On set function assign command
  void SetOnStart(ICommand *command){
    this->on_start_=command;
  }
  void SetOnFinish(ICommand *command){
    this->on_finish_ = command;
  }
  void SetOnMoveUp(ICommand *command) {
    this->on_move_up = command;
  }
  void SetOnRotateClk(ICommand *command) {
    this->on_rotate_clk = command;
  }
  void SetOnMoveDown(ICommand *command) {
    this->on_move_down = command;
  }
  void SetOnRotateCclk(ICommand *command) {
    this->on_rotate_clk = command;
  }
  void SetOnGetSpeed(ICommand *command) {
    this->on_get_speed = command;
  }
  void SetOnSetSpeed(ICommand *command) {
    this->on_set_speed= command;
  }
  void SetOnGetDelay(ICommand *command) {
    this->on_get_delay = command;
  }
  void SetOnSetDelay(ICommand *command) {
    this->on_set_delay= command;
  }  
  void SetOnGetDirection(ICommand *command) {
    this->on_get_direction = command;
  }
  void SetOnSetDirection(ICommand *command) {
    this->on_set_direction= command;
  }
  /**
   * The Invoker does not depend on concrete command or receiver classes. The
   * Invoker passes a request to a receiver indirectly, by executing a command.
   */
  void moveUp() {
    Serial.println("turn on motor on move");
    if (this->on_move_up) {
      this->on_start_->execute();
      this->on_move_up->execute();
    }
    Serial.println( "turn off motor when finish");
    if (this->on_finish_) {
      this->on_finish_->undo();
    }
  }
  void moveDown() {
    Serial.println("turn on motor on move");
    if (this->on_move_down) {
      this->on_start_->execute();
      this->on_move_down->execute();
    }
    Serial.println( "turn off motor when finish");
    if (this->on_finish_) {
      this->on_finish_->undo();
    }
  }
  void rotateClk() {
    Serial.println("turn on motor on move");
    if (this->on_rotate_clk) {
      this->on_start_->execute();
      this->on_rotate_clk->execute();
    }
    Serial.println( "turn off motor when finish");
    if (this->on_finish_) {
      this->on_finish_->undo();
    }
  }
  void rotateCclk() {
    Serial.println("turn on motor on move");
    if (this->on_rotate_Cclk) {
      this->on_start_->execute();
      this->on_rotate_Cclk->execute();
    }
    Serial.println( "turn off motor when finish");
    if (this->on_finish_) {
      this->on_finish_->undo();
    }
  }
  void getSpeed() {
    if (this->on_get_speed) {
      this->on_get_speed->execute();
    }
  }
  void getDelay() {
    if (this->on_get_delay) {
      this->on_get_delay->execute();
    }
  }
  void getDirection() {
    if (this->on_get_direction) {
      this->on_get_direction->execute();
    }
  }
  void setSpeed() {
    if (this->on_set_speed) {
      this->on_set_speed->execute();
    }
  }
  void setDelay() {
    if (this->on_set_delay) {
      this->on_set_delay->execute();
    }
  }
  void setDirection() {
    if (this->on_set_direction) {
      this->on_set_direction->execute();
    }
  }
};
#endif