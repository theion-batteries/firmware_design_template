/**
 * @file StateManager.hpp
 * @author sami@theion.de
 * @brief Manager for internal cpu actions and states 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
class CommandStateManager{
        public:
        /** we have 2 categorie and subcategorie  to manage:
         * A- serial or external
         *          * commands: coming from serial monitor ending with LF or new line ending
         *          * states: every command running has it own state
         * B - CPU or internal 
         *          * actions: high priority than commands
         *          * states: when action is run, change immediately to its state
         **/
        /**** cmd/state atr****/
        String FirstArgs[5] = {"printhead", "x", "y", "z", "all"};
        String SecondArgs[4] = {"up", "down", "clk", "cclk"};
        // third arg depending on command is tricky: could be digit value or max,min string
        String ThirdArgs[3] = {"value", "max", "min"};
        // Meta/template commands: move, rotate, get, set 
        // mechanical objects: x,y,z
        // electronic drive objects: motor, sensor
        // electronic specific attribute/paramtere value: distance, delay
        // general format: meta mechObj eleObj eleAttr
        // get x sensor distance
        // get y motor speed/delay  
        // set printhead motor direction clk
        // example command with args: move x up 20 
        // arg1: x, arg2: up, arg3: 20 float        
        String command;
        String state;
        /**** cpu action state******/
        String CPUstate;
        String CPUaction;
        /******* cmd /state list*********/
        const int StatesListLength= 11;
        const int CommandsListLength= 21;
        String* States = new String[StatesListLength]{"ready","homing Up", "homing Down", "oscillating", "rotating Clockwise", 
        "rotating Counter Clockwise", "calibrating", "aligning", "moving Down", "moving Up","setting Target Distance Printhead to Mother liquid"         };
        String* Commands= new String[CommandsListLength]{"get_id","homeUp", "homeDown","oscillate","rotateCW",
         "rotateCCW","calibrate","align", "down", "up", "downAllMax", "downXMax","downYMax", 
         "downZMax", "upAllMax", "setTargetDistancePhMl", "upXMax","upYMax","upZMax"                         };
        // converting old commands to new format:
        // example1: homeUp -> move all up value or move all up max where value is poisitiv integer: move all up 1000
        // here the callbackfunction must have safety limit to indicate that 1000 is out of range and thus moving to max
        /****** cpu actions state list ********/
        // First cpu actions running or starting communication procedure following by ackowledgment id or UUID 
        // example set of actions on global scoop : boot, start, run ...
        // cpu process in computer have several states: new, ready, running, termination, wait/block, suspend waiting
        // thus lot actions are performed: states new to ready: after receiving command, ready->runing: schedule the cmd task, run->termination: complete succefully 
        // running-> waiting: i/o/pause request, running->canceled: cancel/exit, suspended->ready: resume.
        const int CPUStatesListLength= 11;
        const int CPUActionsLength= 20;

/*********** CPU Methods ******************/
        void setCPUready(){
          CPUstate="ready";
        }
 /*********** Commands Methods ***************/
 /*********** states methods ***************/
        String getCommandState()
        {
          String CommandState;
          if (command=="wait") {CommandState="ready";}
          if (command=="get_id") {CommandState="ready";}
          if (command=="setTargetDistancePhMl") {CommandState="TargetDistancePhMl_set";}
          if (command=="homeUp") {CommandState="homingUp";}
          if (command=="homeDown") {CommandState="homingDown";}
          if (command=="rotateCW") {CommandState="rotating_Clockwise";} 
          if (command=="rotateCCW") {CommandState="rotating_CounterClockwise";} 
          if (command=="calibrate") {CommandState="calibrating";}
          if (command=="align") {CommandState="aligning";}
          if (command=="oscillate") {CommandState="oscillating";}
          if (command=="downAllMax") {CommandState="movingDownALLMax";}
          if (command=="downXMax") {CommandState="movingDownXMAx";}
          if (command=="downYMax") {CommandState="movingDownYMAx";}
          if (command=="downZMax") {CommandState="movingDownZMAx";}
          if (command=="upAllMax") {CommandState="movingUpAllMAx";}
          if (command=="upXMax") {CommandState="movingUpXMAx";}
          if (command=="upYMax") {CommandState="movingUpYMAx";}
          if (command=="upZMax") {CommandState="movingUpZMAx";}
          if (command=="downAll") {CommandState="movingDownALL";}
          if (command=="downX") {CommandState="movingDownX";}
          if (command=="downY") {CommandState="movingDownY";}
          if (command=="downZ") {CommandState="movingDownZ";}
          if (command=="upAll") {CommandState="movingUpAll";}
          if (command=="upX") {CommandState="movingUpX";}
          if (command=="upY") {CommandState="movingUpY";}
          if (command=="upZ") {CommandState="movingUpZ";}
          return CommandState;
        }
        bool commandWithArgs(){
          if (command == "down")
          {
          return true;
          }
          if ( command == "up")
          {
            return true;
          }
          else{
            return false;
          }
        }
        void setCommand(String com){
          command = com;
        }
        void setState(String st){
          state = st;
        }   
        void updateState(){
          if (command=="wait") {state="ready";}
          if (command=="get_id") {state="ready";}
          if (command=="setTargetDistancePhMl") {state="TargetDistancePhMl_set";}
          if (command=="homeUp") {state="homingUp";}
          if (command=="homeDown") {state="homingDown";}
          if (command=="rotateCW") {state="rotating_Clockwise";} 
          if (command=="rotateCCW") {state="rotating_CounterClockwise";} 
          if (command=="calibrate") {state="calibrating";}
          if (command=="align") {state="aligning";}
          if (command=="down") {state="movingDown";}
          if (command=="up") {state="movingUp";}
          if (command=="oscillate") {state="oscillating";}
        }


};