#include "DistanceSensor.hpp"
#include "Arduino.h"

#define MAX_PULSE_WIDTH 23200


//Initialize the distance sensor object
DistanceSensor::DistanceSensor(int triggerPin, int echoPin)
{
    //Store the pin numbers for the trigger and echo pins for future use
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    //Set the pins to the correct I/O mode
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(triggerPin, LOW);
}

//Returns the distance read from the sensor in cm
int DistanceSensor::getDist()
{
    //Makes use of the internal functions to handle each stage of the read
    //process
    sendTriggerPulse();
    unsigned long pulseWidth;
    int statusCode = measureEchoPulse(&pulseWidth);
    if(statusCode == -1)
    {
      return -1; 
    }
    return pulse2cm(pulseWidth);
}

//Send the 10 us pulse out on the trigger
void DistanceSensor::sendTriggerPulse()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
}

/*
Fills the variable pointed to by pulseWidth with the measure pulse 
width. Returns 0 when success full and reuturns -1 when an error 
occured such as when the measure distance is out of range.
*/
int DistanceSensor::measureEchoPulse(unsigned long *pulseWidth)
{
     *pulseWidth = pulseIn(echoPin, HIGH);

    //Return the correct code depending on if the meausred pulse
    //is with in the allowed range.
    if(*pulseWidth > MAX_PULSE_WIDTH)
    {
        return -1;
    }
    else
    {
        return 0;
    }
    
}

//Convert the pulse width to cm
int DistanceSensor::pulse2cm(int pulseWidth)
{
    return pulseWidth / 58.0;
}
