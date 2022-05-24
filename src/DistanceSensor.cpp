/**
 * @file DistanceSensor.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief 
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "DistanceSensor.hpp"

#ifdef hc_sr04
DistanceSensor::DistanceSensor(int EchoPin, int TrigPin){
    this->EchoPin=EchoPin;
    this->TrigPin=TrigPin;
    pinMode(EchoPin, INPUT);
    pinMode(TrigPin,OUTPUT);
    digitalWrite(TrigPin, LOW);
}
#endif
#ifdef keyence

// conctructor distance sensor generic keyence
DistanceSensor::DistanceSensor(int OutputHeadNumber)
{
this->HeadNum=OutputHeadNumber;
//Keyence_base::NumUsedHeads.insert(Keyence_base::NumUsedHeads.begin()+Keyence_base::HeadsCount,OutputHeadNumber);   //insert
Keyence_base::HeadsArray[Keyence_base::HeadsCount]=OutputHeadNumber;
Keyence_base::HeadsCount++;
}

void DistanceSensor::setKeyenceCom()
{
    IkeyenceRS232->initKeyenceCom();
    IkeyenceRS232->setGeneralMode();
    //Serial.println("Keyence general mode set succefully");
    //Serial.flush();
}

#endif

// generic methods
double DistanceSensor::getCurrentDistance()
{
    #ifdef hc_sr04 //how to read with hc_sr04
        unsigned long t1;
        unsigned long t2;
        unsigned long pulse_width;
        float cm;
        digitalWrite(TrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW);
        while ( digitalRead(EchoPin) == 0 );
        t1 = micros();
        while ( digitalRead(EchoPin) == 1);
        t2 = micros();
        pulse_width = t2 - t1;
        cm = pulse_width / 58.0;
        long mm = cm*10;
        currentDistance=mm;
        return currentDistance;
    #endif
    /******* get values from keyence *********/
    #ifdef keyence //how to read with keyence
    IkeyenceRS232->getValueOutputHeadAll();
    return Keyence_base::LookUpValues[this->HeadNum-1];
    #endif
}
void DistanceSensor::printDistance(float val)
{
    static unsigned long timer_print_serial=0;
    unsigned int period = 500;
 //if(millis()-timer_print_serial>period) //timer 
  //{
    timer_print_serial=millis();
    Serial.print("current distance head ");
    Serial.print(this->HeadNum);
    Serial.print(" equal to ");
    Serial.println(val);
 // }
}
