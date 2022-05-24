/**
 * @file Globals.h
 * @author your name (you@domain.com)
 * @brief include declarations for commands classes
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#pragma once
#include "CmdParser.hpp"
#include "CmdPatternClasses.h"
#include "CmdBuffer.hpp"
#include "CmdCallback.hpp"
#include "stack"
#include <memory>


/// define global variables: need to be encapsulated later
extern CmdCallback<64> cmdCallback;
extern CmdBuffer<64> myBuffer;
extern CmdParser    myParser;
//Create Objects 
// Setup Motors Objects: Note: PIN must be defined in config file
extern Nema8 M_X;
extern Nema8 M_Y;
extern Nema8 M_Z;
extern Nema8 M_PH;
// Setup EndStops Objects
extern endSwitch ES_x;
extern endSwitch ES_y;
extern endSwitch ES_z;
extern endSwitch ES_Stop;
// Setup Distance Sensors Objects
extern DistanceSensor DS_x;
extern DistanceSensor DS_y;
extern DistanceSensor DS_z;
// Setup Light barrier Objects
extern lightBarrier LB_x;
extern lightBarrier LB_y;
extern lightBarrier LB_z;
// Setup Alignment Object
extern Alignment AlignObj;
extern UUID_MANAGER AlignId;
extern ResetHardware resetObj;
extern SleepHardware sleepObj;
extern char Start[];
extern char Quit[] ;
extern char Set[];
extern char Get[];
extern char Undo[] ;
extern char Move[] ; 
extern char Reset[] ;
extern char Stop[] ;
extern char Sleep[] ;
extern char Help[] ;
extern char Calibrate[] ;
extern char Rotate[] ;
extern char Test1[] ;
extern char Test2[] ;
// define command Stack
extern std::stack<ICommand*> CmdStack;
extern std::vector<ICommand*> CmdDeleter;
extern std::stack<Invoker> InvokerStack;
void ParserThreadCallback();

void BackgroundThreadCallback();











// wrapper class for clarity 
class MotorGetCmdHandler
{
    private:

};

#endif