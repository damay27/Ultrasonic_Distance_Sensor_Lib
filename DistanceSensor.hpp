
class DistanceSensor
{
    private:
        int triggerPin, echoPin;

        //This functions are private so that they will only be used internally
        void sendTriggerPulse();

        /*
        Fills the variable pointed to by pulseWidth with the measure pulse 
        width. Returns 0 when success full and reuturns -1 when an error 
        occured such as when the measure distance is out of range.
        */
        int measureEchoPulse(unsigned long *pulseWidth);
        int pulse2cm(int pulseWidth);

    public:
        DistanceSensor(int triggerPin, int echoPin);
        int getDist();
};
