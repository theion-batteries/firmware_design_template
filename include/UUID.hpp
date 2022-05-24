/**
 * @file serial_ids_base.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief include a base class that defines all ids
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
//#define using_iostream
#define using_serial_stream
#ifdef using_iostream
   #include <iostream> // use to test on pc
#endif
#ifdef using_serial_stream
   #include <Arduino.h> // test direct with serial.print
   #include <EEPROM.h>
#endif
/**
 * @brief Class for managing UUID, construct a new uuid manager object
 * by passing the name to constructor to automaticly point to the specific id.
 * 
 * IDS = ["align", "sf6", "print", "cnt", "temp", "default]
 * @param WhichId 
 */
class UUID_MANAGER 
{
private:
// a pointer to which id 
String* ObjUUID;
private:
// id format: firmware_version
   String default_id="def_v0.1";
   String temp_id="temp_v0.1";
   String sf6_id = "sf6_v0.1";
   String align_id = "align_v0.1";
   String print_id= "print_v0.1";
   String cnt_id= "cnt_v0.1";
   String delta_id = "delta_v0.1";
public:
/**
 * @brief Construct a new uuid manager object
 * example: pass "align" to constructor to automaticly to align id
 * @param WhichId 
 */
UUID_MANAGER(String WhichId)
{
   if (WhichId=="align")
   {
      ObjUUID=&align_id;
   }
   if (WhichId=="sf6")
   {
      ObjUUID=&sf6_id;
   }
   if (WhichId=="print")
   {
      ObjUUID=&print_id;
   }
   if (WhichId=="cnt")
   {
      ObjUUID=&cnt_id;
   }
   if (WhichId=="temp")
   {
      ObjUUID=&temp_id;
   }
   if (WhichId=="default")
   {
      ObjUUID=&default_id;
   }
   this->_checkIfUUIDisWritten();
}
/**
 * @brief wrapper function to get internal stored id
 * 
 * @return String 
 */
String get_UUID_EEPROM(){
      *ObjUUID=_readStringFromEEPROM(0);
      return *ObjUUID;
}
/**
 * @brief wrapper function to set new internal id
 * 
 */
void set_UUID_EEPROM(const String new_uuid){
   *ObjUUID=new_uuid;
   _writeStringToEEPROM(0, new_uuid);
}
/**
 * @brief write id at boot, don't overwrite if exists
 * @see private method write to eeprom to get the idea
 * @return true 
 * @return false 
 */
void _checkIfUUIDisWritten(){
   if(*ObjUUID==_readStringFromEEPROM(0)) return;
   else _writeStringToEEPROM(0,*ObjUUID);
}
////// Private methods read/write eeprom ////////////
private:
/**
 * @brief write string to eeprom
 * 
 * @param addrOffset 
 * @param strToWrite 
 * @return int 
 */
void _writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

/**
 * @brief read string from eeprom
 * 
 * @param addrOffset 
 * @param strToRead 
 * @return int 
 */
String _readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)
  return String(data);
}

////////////////
// getter methods to return private attributes
//////////////////
/**
 * @brief Get the default id object
 * 
 * @return String 
 */
String _get_default_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(default_id);
   #endif
return default_id;
}
/**
 * @brief Get the temp id object
 * 
 * @return String 
 */
String _get_temp_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(temp_id);
   #endif   
return temp_id;
}
/**
 * @brief Get the wafer alignement id object
 * 
 * @return String 
 */
String _get_align_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(align_id);
   #endif

return align_id;
}
/**
 * @brief Get the sf6 id object
 * 
 * @return String 
 */
String _get_sf6_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(sf6_id);
   #endif   
return sf6_id;
}
String _get_delta_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(delta_id);
   #endif   
return delta_id;
}
String _get_cnt_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(cnt_id);
   #endif   
return cnt_id;
}
String _get_print_id(){ // use auto if confused : auto get_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("getting UUID");
      Serial.println(print_id);
   #endif   
return print_id;
}
////////////////
// setter methods to set private attributes
//////////////////

/**
 * @brief Get the default id object
 * 
 * @return String 
 */
void _set_default_id(String new_id){ // use auto if confused : auto set_temp_id(){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(default_id);
   #endif
 default_id=new_id;
}
/**
 * @brief set the temp id object
 * 
*/
void _set_temp_id(String new_id){ // use auto if confused : auto set_temp_id(String new_id){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(temp_id);
   #endif   
 temp_id=new_id;
}
/**
 * @brief set the wafer alignement id object
 * 
*/
void _set_align_id(String new_id){ // use auto if confused : auto set_temp_id(String new_id){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(align_id);
   #endif

 align_id=new_id;
}
/**
 * @brief set the sf6 id object
 * 
*/
void _set_sf6_id(String new_id){ // use auto if confused : auto set_temp_id(String new_id){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(sf6_id);
   #endif   
 sf6_id=new_id;
}
void _set_delta_id(String new_id){ // use auto if confused : auto set_temp_id(String new_id){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(delta_id);
   #endif   
 delta_id=new_id;
}
void _set_cnt_id(String new_id){ // use auto if confused : auto set_temp_id(String new_id){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(cnt_id);
   #endif   
 cnt_id=new_id;
}
void _set_print_id(String new_id){ // use auto if confused : auto set_temp_id(String new_id){}
   #ifdef using_serial_stream
      Serial.println("setting UUID");
      Serial.println(print_id);
   #endif   
 print_id=new_id;
}
};