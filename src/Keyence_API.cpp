/**
   @file Keyence_API.h
   @author sami dhiab (sami@theion.de)
   @brief keyence sensors APIs
   @version 0.1
   @date 2022-04-06

   @copyright Copyright (c) 2022

*/
#include "Keyence_API.h"

//keyence base class 
////define keyence static variables
int Keyence_base::HeadsCount = 0;
std::vector<int> Keyence_base::NumUsedHeads;
int Keyence_base::HeadsArray[12];
double* Keyence_base::LookUpValues = new double[Keyence_base::HeadsCount]{ 0 };

// list heads availble
void Keyence_base::listHeads()
{

  transformArrayToVector(HeadsArray, NumUsedHeads);
  NumUsedHeads.resize(HeadsCount);
  //Serial.println("listing heads in vector container");
    // For loop using iterators
  if (!NumUsedHeads.empty())
  {
    for (std::vector<int>::iterator it = NumUsedHeads.begin(); it != NumUsedHeads.end(); it++)
    {
#ifdef DEBUG_
      Serial.println("next head number:");
      Serial.println(*it);
#endif
    }
  }
  else Serial.println("empty heads container");
}
//commands section
// helper method to retrieve commands from map
String Keyence_base::findCommand(String& command, std::map<String, String>& CommandMap)
{
  for (auto it = CommandMap.begin(); it != CommandMap.end(); ++it)
  {
    if ((*it).first == command)
    {
      return (*it).second;
    }
  }
}

// keyence rs232 

//constructor: take a serial handler and baudrate by default defined in config file
Keyence_rs232_interface::Keyence_rs232_interface(HardwareSerial& serHandler = KEYENCE_SERIAL_HANDLER, unsigned long baud = KEYENCE_SERIAL_BAUDRATE)
{
  this->serialHandler = &serHandler;
  this->baudrate = baud;

}
// if the serial handler is changed dynamicly
void Keyence_rs232_interface::setSerialHandler(HardwareSerial& serHandler)
{
  this->serialHandler = &serHandler;
}
// if baudrate is changed dynamicly
void Keyence_rs232_interface::setSerialBaudrate(unsigned long baud)
{
  this->baudrate = baud;
}

//init the com with keyence
void Keyence_rs232_interface::initKeyenceCom()
{
  serialHandler->begin(baudrate);
}

//get a output value of single head: head number format is 01,02,03... but param is given as int 1,2,3...
double Keyence_rs232_interface::getValueSingleOutputHead(int output_head_Nr)
{
  static double last_time = 0;
  String Zero = "0";
  String Response;
  double val;
  // head specific parameters
  String Soutput_head_Nr = String(output_head_Nr);
  //write the get value command
  //
  String command = "mesure_value_outputN";
  String cmd = findCommand(command, commands);
  if (output_head_Nr < 9) {
    Soutput_head_Nr = Zero + Soutput_head_Nr;
  }
  cmd += Soutput_head_Nr;
  // from hear comes magic  
  // if the buffer is not empty
  if (serialHandler->available() > 0)
  {
    // get it
    Response = serialHandler->readStringUntil('\r');
    //Serial.println("buffer already full with: "+Response);
    if (Response.substring(0, 5) == cmd)
    {
      Serial.println("full response: " + Response);
      Response.remove(0, 6); //remove default response
      val = Response.toDouble();
      Serial.println("filtered response for head: " + Soutput_head_Nr + " equal to: " + Response + " double value: " + val);
      if (val > 0) return val;
    }
    serialHandler->flush();
  }
  serialHandler->print(cmd + CR);
  //Serial.println("sending command: "+cmd);
  // because the need of time between cmd and response
  if (millis() - last_time >= 200) //time to send/receive response from 1 head
  {
    if (serialHandler->available() > 0)
    {
      // Read data from rs232 port
      Response = serialHandler->readStringUntil('\r');
      // write the data to the other port
      //MS,OUT01,value CR: remove M->,: 9
      //Serial.println("cmd: "+cmd+" Response: "+ Response.substring(0,5));
      if (Response.substring(0, 5) == cmd)
      {
        Serial.println("full response: " + Response);
        Response.remove(0, 6); //remove default response
        val = Response.toDouble();
        Serial.println("filtered response for head: " + Soutput_head_Nr + " equal to: " + Response + " double value: " + val);
        serialHandler->flush();
        last_time = millis();
        if (val > 0) return val;
      }
    }
  }
}
//get output multiple heads in this format: "0-12" example: head 1,2 and 3 will be 111000000000
double* Keyence_rs232_interface::getValueMultipleOutputHead(String HeadsArray)
{
  int NumOfOutputs = 0;
  //write the get value command
  if (NumOfOutputs < 1)
  {
    for (auto& element : HeadsArray)
    {
      if (element == '1')
      {
        NumOfOutputs++;
      }
    }
  }
  double* Values = new double[NumOfOutputs];
  //double Values[NumOfOutputs];
  String valuesHolder = "";
  int ValuesCounter = 0;
  Serial.println("number of heads");
  Serial.println(NumOfOutputs);
  String command = "mesure_value_multipleN";
  String cmd = findCommand(command, commands);
  //cmd:MM,010010000000
  cmd += String(HeadsArray);
  Serial.println("command sent:");
  Serial.println(cmd);
  serialHandler->println(cmd);
  if (serialHandler->available() > 0)
  {
    // Read data from rs232 port
    String Response = serialHandler->readStringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
#endif
    // Response: MM,010010000000,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    Serial.println(Response);
    // iterate response and extract values

    for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        Serial.println("value holder got");
        Serial.println(valuesHolder);
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        valuesHolder = "";
      }
      if (ValuesCounter == NumOfOutputs) break;
    }
    for (int i = 0; i < NumOfOutputs; i++)
    {
      Serial.println("extracted values");
      Serial.println(*(Values + i));
    }
    return Values;
  }
}
// get output all
double* Keyence_rs232_interface::getValueOutputHeadAll()
{
  String Response;
  String valuesHolder = "";
  int ValuesCounter = 0;
  //write the get value command
  String cmd;
  //Serial.print("number of heads: ");
  //Serial.println(HeadsCount);
  ////Serial.println("timer: "+String(timer_send_cmd));
  //Serial.print("timer: ");
  //Serial.println(timer_send_cmd);
  String command = "mesure_value_All";
  //cmd = findCommand(command, commands);
  // speed purpose we skip any loop
  cmd = "MA";
  serialHandler->print(cmd + CR);
  //Serial.print("command sent: ");
  //Serial.println(cmd+CR);
  if (serialHandler->available() > 0)
  {
    // Read data from rs232 port
    Response = serialHandler->readStringUntil('\r');
    // MA,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    Serial.println(Response);
    double* Values = new double[HeadsCount] {0}; //heap
    // iterate response and extract values
    /*for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        //Serial.print("value holder got: ");
        //Serial.println(valuesHolder.toDouble());
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        //Serial.print("extracted values: ");
        //Serial.println(*(Values + i));
      }
      if (ValuesCounter == HeadsCount) break;
    }*/
    // try to gte rid of any loop that slow down the main loop
    // as we know that we use three heads, we can just add the index
    int first_occurance=Response.indexOf(',', 0);
    int second_occurance=Response.indexOf(',', first_occurance+1);
    int third_occurance=Response.indexOf(',',second_occurance+1);
    Values[0] = Response.substring(first_occurance+1,second_occurance+1).toDouble();
    Values[1] = Response.substring(second_occurance+1,third_occurance+1).toDouble();
    Values[2] = Response.substring(third_occurance+1,Response.length()).toDouble();
    //Serial.println(Values[0]);
    //Serial.println(Values[1]);
    //Serial.println(Values[2]);
    Keyence_base::LookUpValues = Values;
    delete[] Values;
    return Keyence_base::LookUpValues;
  }
}

// set general mode
void Keyence_rs232_interface::setGeneralMode()
{
  //write the get value command
  String command = "set_general_mode";
  String cmd = findCommand(command, commands);
  serialHandler->print(cmd + CR);
  if (serialHandler->available() > 0)
  {
    // Read data from rs232 port
    String Response = serialHandler->readStringUntil('\r');
#ifdef DEBUG_
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
#endif
  }
}
// set communication mode
void Keyence_rs232_interface::setCommunicationMode()
{

  //write the get value command
  String command = "set_communication_mode";
  String cmd = findCommand(command, commands);
  serialHandler->print(cmd + CR);
  delay(100); //this delay is obligatory to clear buffer

  if (serialHandler->available() > 0)
  {
    // Read data from rs232 port
    String Response = serialHandler->readStringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    Serial.println("response:");
    Serial.println(Response);
#endif
  }
  serialHandler->write("");
  serialHandler->flush();
}

