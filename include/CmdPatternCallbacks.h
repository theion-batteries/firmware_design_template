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

#ifndef _CMDPATTERNCALLBACKS_H_
#define _CMDPATTERNCALLBACKS_H_
#pragma once
#include "Globals.h"

/************** Help commands section ***********/
// help command
/**
 * @brief display help
 *
 * @param
 */
void display_help();

/**
 * @brief display help
 *
 * @param
 */
void display_help_get();

/**
 * @brief display help
 *
 * @param
 */
void display_help_set();

/**
 * @brief display help
 *
 * @param
 */
void display_help_move();

/**
 * @brief display help
 *
 * @param
 */
void display_help_undo();

/**
 * @brief display help
 *
 * @param
 */
void display_help_reset();

/**
 * @brief display help
 *
 * @param
 */
void display_help_sleep();

// command callback templates
/**
 * @brief display help
 *
 * @param
 */
void get_help(CmdParser* myParser); 

/**
 * @brief callback cmd
 *
 * @param my cmdParser
 */
void get_cmd(CmdParser* myParser);
// command callback templates
/**
 * @brief callback cmd
 *
 * @param my cmdParser
 */
void set_cmd(CmdParser* myParser); 
// format: move x up 1
/**
 * @brief callback cmd
 *
 * @param my cmdParser
 */
void move_cmd(CmdParser* myParser); 
// format: move x up 1
/**
 * @brief callback cmd
 *
 * @param my cmdParser
 */
void rotate_cmd(CmdParser* myParser); 
/**
 * @brief calibrate cmd using invoker
 *
 * @param myParser
 */
void calibrate_cmd(CmdParser* myParser);
/**
 * @brief reset device
 *
 * @param myParser
 */
void reset_cmd(CmdParser* myParser); 
/**
 * @brief reset device
 *
 * @param myParser
 */
void sleep_cmd(CmdParser* myParser); 
/**
 * @brief undo last command by calling undo();, then remove it from stack
 *
 * @param myParser
 */
void undo_cmd(CmdParser* myParser); 
#endif