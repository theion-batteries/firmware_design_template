/**
 * @file CmdPatternCallbacks.h
 * @author your name (you@domain.com)
 * @brief binding command inokation with parser callbacks
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CmdPatternCallbacks.h"


/************** Help commands section ***********/
// help command
void display_help()
{
    Serial.println("Welcome !");
    Serial.println("Syntax: help COMMAND");
    Serial.println("List information about the internal commands and options");
    Serial.println("COMMANDS[get, set, move, rotate, reset, sleep, undo]");
    Serial.println("Usage: help get      dispaly get command usage information");
}
void display_help_get()
{
    Serial.println("Syntax: get OPTIONS");
    Serial.println("COMMAND:     get [options]    get object specific value");
    Serial.println("OPTIONS:                               ");
    Serial.println("opt1:  [uuid, motor, sensor]");
    Serial.println("opt2:  [x,y,z,ph,value] ");
    Serial.println("opt3:  [speed,delay,direction] ");
    Serial.println("Usage: get uuid          return uuid");
    Serial.println("Usage: get motor x speed         return motor x speed");
    Serial.println("Usage: get sensor x value       return sensor x value");
}
void display_help_set()
{
    Serial.println("Syntax: set OPTIONS");
    Serial.println("COMMAND:     set [options]    set object specific value");
    Serial.println("OPTIONS:                               ");
    Serial.println("opt1:  [uuid, motor]");
    Serial.println("opt2:  [x,y,z,ph] ");
    Serial.println("opt3:  [speed,delay,direction] ");
    Serial.println("Usage: set uuid value        set uuid");
    Serial.println("Usage: set motor x speed value        set motor x speed");
}
void display_help_move()
{
    Serial.println("Syntax: move OPTIONS");
    Serial.println("COMMAND:     move or rotate [options]    move object specific value");
    Serial.println("OPTIONS:                               ");
    Serial.println("opt1:  [x,y,z][ph] ");
    Serial.println("opt2:  [up,down][clk,cclk] ");
    Serial.println("Usage: move x up value          move motor x up value  [in mm]");
    Serial.println("Usage: rotate ph clk angle          rotate motor ph clk angle  [in degree]");
}
void display_help_undo()
{
    Serial.println("Syntax: undo ");
    Serial.println("COMMAND:     undo   undo last command: execute last in command in stack");

}
void display_help_reset()
{
    Serial.println("Syntax: reset ");
    Serial.println("COMMAND:     reset   reset device");

}
void display_help_sleep()
{
    Serial.println("Syntax: sleep ");
    Serial.println("COMMAND:     sleep   enter sleep mode device");

}
// command callback templates
void get_help(CmdParser* myParser) {
    if (myParser->equalCmdParam(1, "get")) {
        display_help_get();
    }
    else if (myParser->equalCmdParam(1, "set")) {
        display_help_set();
    }
    else if (myParser->equalCmdParam(1, "move")) {
        display_help_move();
    }
    else if (myParser->equalCmdParam(1, "reset")) {
        display_help_reset();
    }
    else if (myParser->equalCmdParam(1, "sleep")) {
        display_help_sleep();
    }
    else if (myParser->equalCmdParam(1, "undo")) {
        display_help_undo();
    }
    else display_help();

}
void get_cmd(CmdParser* myParser) {
    if (myParser->equalCmdParam(1, "uuid")) {
        ICommand* get_uuid = new getUUID(AlignId);
        get_uuid->execute();
        CmdStack.push(get_uuid);
    }
    else if (myParser->equalCmdParam(1, "sensor")) {
        if (myParser->equalCmdParam(2, "x")) {
            if (myParser->equalCmdParam(3, "value")) {
                ICommand* get_sensor_val = new getSensorValueCmd(DS_x);
                get_sensor_val->execute();
                CmdStack.push(get_sensor_val);
            }
        }
    }
    else if (myParser->equalCmdParam(1, "motor")) {
        if (myParser->equalCmdParam(2, "x")) {
            if (myParser->equalCmdParam(3, "speed")) {
                ICommand* getMotorXspeed = new getMotorSpeedCmd(M_X);
                getMotorXspeed->execute();
                CmdStack.push(getMotorXspeed);
            }
            if (myParser->equalCmdParam(3, "direction")) {
                ICommand* getMotorXDirection = new getMotorDirectionCmd(M_X);
                getMotorXDirection->execute();
                CmdStack.push(getMotorXDirection);
            }
            if (myParser->equalCmdParam(3, "delay")) {
                ICommand* getMotorXDelay = new getMotorDelayCmd(M_X);
                getMotorXDelay->execute();
                CmdStack.push(getMotorXDelay);
            }
        }
        if (myParser->equalCmdParam(2, "y")) {
            if (myParser->equalCmdParam(3, "speed")) {
                ICommand* getMotorYspeed = new getMotorSpeedCmd(M_Y);
                getMotorYspeed->execute();
                CmdStack.push(getMotorYspeed);
            }
            if (myParser->equalCmdParam(3, "direction")) {
                ICommand* getMotorYDirection = new getMotorDirectionCmd(M_Y);
                getMotorYDirection->execute();
                CmdStack.push(getMotorYDirection);
            }
            if (myParser->equalCmdParam(3, "delay")) {
                ICommand* getMotorYDelay = new getMotorDelayCmd(M_Y);
                getMotorYDelay->execute();
                CmdStack.push(getMotorYDelay);
            }
        }
        if (myParser->equalCmdParam(2, "z")) {
            if (myParser->equalCmdParam(3, "speed")) {
                ICommand* getMotorZspeed = new getMotorSpeedCmd(M_Z);
                getMotorZspeed->execute();
                CmdStack.push(getMotorZspeed);
            }
            if (myParser->equalCmdParam(3, "direction")) {
                ICommand* getMotorZDirection = new getMotorDirectionCmd(M_Z);
                getMotorZDirection->execute();
                CmdStack.push(getMotorZDirection);
            }
            if (myParser->equalCmdParam(3, "delay")) {
                ICommand* getMotorZDelay = new getMotorDelayCmd(M_Z);
                getMotorZDelay->execute();
                CmdStack.push(getMotorZDelay);
            }
        }
    }
    // Command Unknwon
    else {
        Serial.println("command unkown");
    }
}

// command callback templates
void set_cmd(CmdParser* myParser) {
    // we create a new command pointer to hold reference to motor 
    int setVal = String(myParser->getCmdParam(4)).toInt();
    String new_uuid = myParser->getCmdParam(2);
    if (myParser->equalCmdParam(1, "uuid")) {
        ICommand* set_uuid = new setUUID(AlignId, new_uuid);
        set_uuid->execute();
        CmdStack.push(set_uuid);
    }
    else if (myParser->equalCmdParam(1, "motor"))
    {
        if (myParser->equalCmdParam(2, "x")) {
            if (myParser->equalCmdParam(3, "speed")) {
                ICommand* setMotorXspeed = new setMotorSpeedCmd(M_X, setVal);
                setMotorXspeed->execute();
                CmdStack.push(setMotorXspeed);
            }
            if (myParser->equalCmdParam(3, "direction")) {
                ICommand* setMotorXDirection = new setMotorDirectionCmd(M_X, setVal);
                setMotorXDirection->execute();
                CmdStack.push(setMotorXDirection);
            }
            if (myParser->equalCmdParam(3, "delay")) {
                ICommand* setMotorXDelay = new setMotorDelayCmd(M_X, setVal);
                setMotorXDelay->execute();
                CmdStack.push(setMotorXDelay);
            }
        }
        if (myParser->equalCmdParam(2, "y")) {
            if (myParser->equalCmdParam(3, "speed")) {
                ICommand* setMotorYspeed = new setMotorSpeedCmd(M_Y, setVal);
                setMotorYspeed->execute();
                CmdStack.push(setMotorYspeed);
            }
            if (myParser->equalCmdParam(3, "direction")) {
                ICommand* setMotorYDirection = new setMotorDirectionCmd(M_Y, setVal);
                setMotorYDirection->execute();
                CmdStack.push(setMotorYDirection);
            }
            if (myParser->equalCmdParam(3, "delay")) {
                ICommand* setMotorYDelay = new setMotorDelayCmd(M_Y, setVal);
                setMotorYDelay->execute();
                CmdStack.push(setMotorYDelay);
            }
        }
        if (myParser->equalCmdParam(2, "z")) {
            if (myParser->equalCmdParam(3, "speed")) {
                ICommand* setMotorZspeed = new setMotorSpeedCmd(M_Z, setVal);
                setMotorZspeed->execute();
                CmdStack.push(setMotorZspeed);
            }
            if (myParser->equalCmdParam(3, "direction")) {
                ICommand* setMotorZDirection = new setMotorDirectionCmd(M_Z, setVal);
                setMotorZDirection->execute();
                CmdStack.push(setMotorZDirection);
            }
            if (myParser->equalCmdParam(3, "delay")) {
                ICommand* setMotorZDelay = new setMotorDelayCmd(M_Z, setVal);
                setMotorZDelay->execute();
                CmdStack.push(setMotorZDelay);
            }
        }
    }
    // Command Unknwon
    else {
        Serial.println("command unkown");
    }
}
// format: move x up 1
void move_cmd(CmdParser* myParser) {
    // we create a new command pointer to hold reference to motor 
    AlignObj.DisableAll(on);
    int moveVal = String(myParser->getCmdParam(3)).toInt();
    if (myParser->equalCmdParam(1, "x")) {
        if (myParser->equalCmdParam(2, "up")) {
            ICommand *moveMotorXUp = new MoveMotorUpCmd(M_X, AlignObj, moveVal);
            moveMotorXUp->execute();
            CmdStack.push(moveMotorXUp);
            /* example using invoker object*/
            //MotorInvoker* Mhandler = new MotorInvoker();
            //Mhandler->SetOnStart(new EnableMotorCmd(M_X));
            //Mhandler->SetOnMoveUp(new MoveMotorUpCmd(M_X, AlignObj, moveVal));
            //Mhandler->SetOnFinish(new EnableMotorCmd(M_X));
            //delete Mhandler;
        }
        if (myParser->equalCmdParam(2, "down")) {
            ICommand* moveMotorXDown = new MoveMotorDownCmd(M_X, AlignObj, moveVal);
            moveMotorXDown->execute();
            CmdStack.push(moveMotorXDown);
        }
    }
    else if (myParser->equalCmdParam(1, "y")) {
        if (myParser->equalCmdParam(2, "up")) {
            ICommand* moveMotorYUp = new MoveMotorUpCmd(M_Y, AlignObj, moveVal);
            moveMotorYUp->execute();
            CmdStack.push(moveMotorYUp);
        }
        if (myParser->equalCmdParam(2, "down")) {
            ICommand* moveMotorYDown = new MoveMotorDownCmd(M_Y, AlignObj, moveVal);
            moveMotorYDown->execute();
            CmdStack.push(moveMotorYDown);
        }
    }
    else if (myParser->equalCmdParam(1, "z")) {
        if (myParser->equalCmdParam(2, "up")) {
            ICommand* moveMotorZUp = new MoveMotorUpCmd(M_Z, AlignObj, moveVal);
            moveMotorZUp->execute();
            CmdStack.push(moveMotorZUp);
        }
        if (myParser->equalCmdParam(2, "down")) {
            ICommand* moveMotorZDown = new MoveMotorDownCmd(M_Z, AlignObj, moveVal);
            moveMotorZDown->execute();
            CmdStack.push(moveMotorZDown);
        }
    }
    // Command Unknwon
    else {
        Serial.println("command unkown");
        AlignObj.DisableAll(off);
    }
    AlignObj.DisableAll(off);
}
// format: move x up 1
void rotate_cmd(CmdParser* myParser) {
    // we create a new command pointer to hold reference to motor 
        AlignObj.DisableAll(on);

    int moveVal = String(myParser->getCmdParam(3)).toInt();
    if (myParser->equalCmdParam(1, "ph")) {
        if (myParser->equalCmdParam(2, "clk")) {
            ICommand *rotateClk = new RotateMotorClkCmd(M_X, AlignObj, moveVal);
            rotateClk->execute();
            CmdStack.push(rotateClk);
        }
        if (myParser->equalCmdParam(2, "cclk")) {
            ICommand* rotateCclk = new RotateMotorCclkCmd(M_X, AlignObj, moveVal);
            rotateCclk->execute();
            CmdStack.push(rotateCclk);
        }
    }
    else {
        Serial.println("command unkown, use following syntax");
        display_help_move();
            AlignObj.DisableAll(off);

    }
        AlignObj.DisableAll(off);

}
/**
 * @brief calibrate cmd using invoker
 *
 * @param myParser
 */
void calibrate_cmd(CmdParser* myParser) {
    float target = String(myParser->getCmdParam(2)).toFloat();
    if (myParser->equalCmdParam(1, "target")) {
        FirmInvoker* FirmU = new FirmInvoker();
        FirmU->SetOnCalibrate(new CalibrateCmd(AlignObj, target));
        delete FirmU;
    }
}
/**
 * @brief reset device
 *
 * @param myParser
 */
void reset_cmd(CmdParser* myParser) {
    ICommand* reset = new ResetDevice(resetObj);
    reset->execute();
    delete reset;
}
/**
 * @brief sleep device
 *
 * @param myParser
 */

void sleep_cmd(CmdParser* myParser) {
    ICommand* sleep = new SleepDevice(sleepObj);
    sleep->execute();
    delete sleep;
}

/**
 * @brief undo last command by calling undo(), then remove it from stack
 *
 * @param myParser
 */
void undo_cmd(CmdParser* myParser) {
    if (!CmdStack.empty())
    {
        //debug stack
        Serial.println("undo last command");
        CmdStack.top()->undo();
        delete CmdStack.top();
        CmdStack.pop();
    }

    else Serial.println("No command in Stack");

}
