#ifndef protoboardLib_h
#define protoboardLib_h

#include "Arduino.h"
#include <string>

class Node{

    private:
        int returnDigitalInputPort(const String pinIdentifier);
        int returnDigitalOutputPort(const String pinIdentifier);
        int returnAnalogInputPort(const String pinIdentifier);

    public:
        Node();
        
        // DIGITAL I/O
        int initDigitalInput(const String pinIdentifier);
        int initDigitalOutput(const String pinIdentifier);
        int readDigitalPort(const String pinIdentifier);
        bool writeDigitalPort(const String pinIdentifier, int value);
         
        // ANALOG I/O
        int readAnalogPort(const String pinIdentifier);      

        // SPI COM
        int returnSSnPort();
        int returnMOSIPort();
        int returnMISOPort();
        int returnSCKLPort();
    };

#endif
