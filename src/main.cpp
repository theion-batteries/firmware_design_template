/**
 * @file main.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief launch main coroutine 
 * @version 0.1
 * @date 2022-02-11
 * @copyright Copyright (c) 2022
 * 
 */
#include "ComHandler.hpp"
#include <AceRoutine.h>
using namespace ace_routine;
ComManager ComObj;

COROUTINE(parser) {
    COROUTINE_LOOP()
    {
    COROUTINE_YIELD();
    cmdCallback.loopCmdProcessing(&myParser, &myBuffer, &Serial);
    }
}

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
  AlignObj.initFirmwareUnit();
  CoroutineScheduler::setup();
}
void loop() { 
  CoroutineScheduler::loop();
}

void yield()
{
  parser.runCoroutine();
}

