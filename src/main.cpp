/**
 * @file main.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief launch main scheduler 
 * @version 0.1
 * @date 2022-02-11
 * @copyright Copyright (c) 2022
 * 
 */
#include "ComHandler.hpp"
ComManager ComObj;
ThreadController MainScheduler = ThreadController();
Thread ParserThread = Thread();

void setup() {
  ComObj.initCom(BAUDRATE);
  cmdCallback.addCmd(Get, &get_cmd);
  cmdCallback.addCmd(Set, &set_cmd);
  cmdCallback.addCmd(Undo, &undo_cmd);
  cmdCallback.addCmd(Move, &move_cmd);
  cmdCallback.addCmd(Reset, &reset_cmd);
  cmdCallback.addCmd(Sleep, &sleep_cmd);
  cmdCallback.addCmd(Help, &get_help);
  cmdCallback.addCmd(Calibrate, &calibrate_cmd);
  cmdCallback.addCmd(Rotate, &rotate_cmd);
  display_help();
	// Configure parser thread
	ParserThread.onRun(ParserThreadCallback);
	// Adds thread to the MainScheduler
	MainScheduler.add(&ParserThread);
}
void loop() { 
MainScheduler.run();
}

void yield(void) {
  Serial.println("yield called, switch context");
  ParserThread.run();
}