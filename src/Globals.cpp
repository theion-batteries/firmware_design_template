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
#include "Globals.h"

CmdCallback<64> cmdCallback;
CmdBuffer<64> myBuffer;
CmdParser    myParser;
//Create Objects 
// Setup Motors Objects: Note: PIN must be defined in config file
Nema8 M_X(0, XMs1_pin, XMs2_pin, XMs3_pin, XDir_pin, XEnable_pin, XStep_pin, down);
Nema8 M_Y(0, YMs1_pin, YMs2_pin, YMs3_pin, YDir_pin, YEnable_pin, YStep_pin, down);
Nema8 M_Z(0, ZMs1_pin, ZMs2_pin, ZMs3_pin, ZDir_pin, ZEnable_pin, ZStep_pin, down);
Nema8 M_PH(0, PHMs1_pin, PHMs2_pin, PHMs3_pin, PHDir_pin, PHEnable_pin, PHStep_pin, cclk);
// Setup EndStops Objects
endSwitch ES_x(E_X, LOW);
endSwitch ES_y(E_Y, LOW);
endSwitch ES_z(E_Z, LOW);
endSwitch ES_Stop(E_Emergency, LOW);
// Setup Distance Sensors Objects
DistanceSensor DS_x(XSensorHead);
DistanceSensor DS_y(YSensorHead);
DistanceSensor DS_z(ZSensorHead);
// Setup Light barrier Objects
lightBarrier LB_x(LB_X, HIGH);
lightBarrier LB_y(LB_Y, HIGH);
lightBarrier LB_z(LB_Z, HIGH);
// Setup Alignment Object
Alignment AlignObj(&M_X, &M_Y, &M_Z, &M_PH, &DS_x, &DS_y, &DS_z, &ES_x, &ES_y, &ES_z,&ES_Stop, &LB_x, &LB_y, &LB_z);
UUID_MANAGER AlignId("align");
ResetHardware resetObj(PIN_OUTPUT_RESET);
SleepHardware sleepObj(InterruptSleepPin);
char Start[] = "start";
char Quit[] = "quit";
char Set[] = "set";
char Get[] = "get";
char Undo[] = "undo";
char Move[] = "move"; 
char Reset[] = "reset";
char Stop[] = "stop";
char Sleep[] = "sleep";
char Help[] = "help";
char Calibrate[] = "calibrate";
char Rotate[] = "rotate";
char Test1[] = "test1";
char Test2[] = "test2";
// define command Stack
std::stack<ICommand*> CmdStack;
std::vector<ICommand*> CmdDeleter;
std::stack<Invoker> InvokerStack;

void ParserThreadCallback()
{
cmdCallback.loopCmdProcessing(&myParser, &myBuffer, &Serial);
}
void BackgroundThreadCallback()
{
Serial.println("running in background..");
}