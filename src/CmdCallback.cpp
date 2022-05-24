/* Copyright 2016 Pascal Vizeli <pvizeli@syshack.ch>
 * BSD License
 *
 * https://github.com/pvizeli/CmdParser
 */

#include "CmdCallback.hpp"
Thread* CmdCallbackObject::getInternalThread() const{
    return InternThread;
}
ThreadController* CmdCallbackObject::getInternalScheduler() const{
      return InternalScheduler;
  }
// after parsing cmd, create a thread to execute that cmd later
void CmdCallbackObject::createThreadForCmd(CmdParser* cmdParser)
{
    InternThread=new Thread();
    //InternThread->onRunT(threadCallback(current_idx, cmdParser));
    InternalScheduler->add(InternThread);
}
void* CmdCallbackObject::threadCallback(size_t idx, CmdParser *cmdParser)
{
    Serial.println("created new internal cmd thread");
    m_functList[idx](cmdParser);
    
}
void CmdCallbackObject::loopCmdProcessing(CmdParser *      cmdParser,
                                          CmdBufferObject *cmdBuffer,
                                          Stream *         serial)
{
        // read data
        if (cmdBuffer->readFromSerial(serial)) {

            // parse command line
            if (cmdParser->parseCmd(cmdBuffer) != CMDPARSER_ERROR) {
                // search command in store and call function
                // ignore return value "false" if command was not found
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
void CmdCallbackObject::processCmdVoid(CmdParser *cmdParser)
{
    char *cmdStr = cmdParser->getCommand();

    // check is commando okay
    if (cmdStr == NULL) {
        return;
    }

    // search cmd in store
    for (size_t i = 0; this->checkStorePos(i); i++) {

        // compare command with string
        if (this->equalStoreCmd(i, cmdStr)) {
            // call function
         this->callStoreFunct(i, cmdParser);
        }
    }

    return;
}
bool CmdCallbackObject::runCmd(char* cmdStr, CmdParser *cmdParser)
{
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


