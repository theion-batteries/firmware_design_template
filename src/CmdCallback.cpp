/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

#include "CmdCallback.hpp"

void CmdCallbackObject::loopCmdParsing(CmdParser *      cmdParser,
                                          CmdBufferObject *cmdBuffer,
                                          Stream *         serial)
{
    ThisCmdBuffer=cmdBuffer;
        // read data
        if (ThisCmdBuffer->readFromSerial(serial)) {

            // parse command line
            if (cmdParser->parseCmd(ThisCmdBuffer) != CMDPARSER_ERROR) {
                // search command in store and call function
                // ignore return value "false" if command was not found
                // change original concept
                IsParsed=true;
                //this->processCmd(cmdParser);
                //ThisCmdBuffer->clear();
            }
        }
}
void CmdCallbackObject::loopCmdProcessing(CmdParser *cmdParser,CmdBufferObject *cmdBuffer,
                           Stream *serial)
{
    ThisCmdBuffer=cmdBuffer;
            // read data
        if (cmdBuffer->readFromSerial(serial)) {

            // parse command line
            if (cmdParser->parseCmd(cmdBuffer) != CMDPARSER_ERROR) {
                // search command in store and call function
                // ignore return value "false" if command was not found
                // change original concept
                IsParsed=true;
                this->processCmd(cmdParser);
                cmdBuffer->clear();
            }
        }
}
bool CmdCallbackObject::processCmd(CmdParser *cmdParser)
{
    char *cmdStr = cmdParser->getCommand();

    // check is commando okay
    if (cmdStr == NULL) {
        return false;
    }

    // search cmd in store
    for (size_t i = 0; this->checkStorePos(i); i++) {

        // compare command with string
        if (this->equalStoreCmd(i, cmdStr)) {
            // call function
            return this->callStoreFunct(i, cmdParser);
        }
    }
    
    return false;
}
bool CmdCallbackObject::processReadyCmd(CmdParser *cmdParser)
{
    char *cmdStr = cmdParser->getCommand();

    // check is commando okay
    if (cmdStr == NULL) {
        return false;
    }

    // search cmd in store
    for (size_t i = 0; this->checkStorePos(i); i++) {

        // compare command with string
        if (this->equalStoreCmd(i, cmdStr)) {
            // call function
            return this->callStoreFunct(i, cmdParser);
        }
    }
    
    return false;
}
void CmdCallbackObject::updateCmdProcessing(CmdParser *      cmdParser,
                                            CmdBufferObject *cmdBuffer,
                                            Stream *         serial)
{
    // read data and check if command was entered
    if (cmdBuffer->readSerialChar(serial)) {
        // parse command line
        if (cmdParser->parseCmd(cmdBuffer) != CMDPARSER_ERROR) {
            // search command in store and call function
            // ignore return value "false" if command was not foun
            
            this->processCmd(cmdParser);
            cmdBuffer->clear();
        }
    }
}

bool CmdCallbackObject::hasCmd(char *cmdStr)
{
    // search cmd in store
    for (size_t i = 0; this->checkStorePos(i); i++) {

        // compare command with string
        if (this->equalStoreCmd(i, cmdStr)) {
            return true;
        }
    }

    return false;
}


