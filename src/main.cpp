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
COROUTINE(parse) {
  COROUTINE_LOOP() {
    COROUTINE_YIELD();
    cmdCallback.loopCmdProcessing(&myParser, &myBuffer, &Serial);
  }
}
// 
COROUTINE(switchA) {
    COROUTINE_BEGIN();
    COROUTINE_YIELD();
    switchCmdA();
    COROUTINE_END();
}
COROUTINE(switchA) {
    COROUTINE_BEGIN();
    COROUTINE_YIELD();
    switchCmdB();
    COROUTINE_END();
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
  CoroutineScheduler::setup();
  display_help();

}
void loop() { 
  CoroutineScheduler::loop();
}

void switchCmdA()
{
  for (int i = 0; i<100; i++)
  {
  Serial.println("switching contextA");
  }
}
void switchCmdB()
{
  for (int i = 0; i<100; i++)
  {
  Serial.println("switching contextB");
  }}