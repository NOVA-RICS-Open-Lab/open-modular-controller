extern "C" {
    #include <stdlib.h>
}
#include "testLibrary.h"
#include "Arduino.h"
#include <string>


Node::Node(){
    return;
}


int Node::returnDigitalInputPort(const String pinIdentifier){
            
    if(pinIdentifier[1]=='1'){
        return 35;
    }
    if(pinIdentifier[1]=='2'){
        return 25;
    }
    if(pinIdentifier[1]=='3'){
        return 26;
    }
    if(pinIdentifier[1]=='4'){
        return 27;
    }
    if(pinIdentifier[1]=='5'){
        return 2;
    }
    if(pinIdentifier[1]=='6'){
        return 4;
    }
    if(pinIdentifier[1]=='7'){
        return 16;
    }
    else{
        return 41;
    }
}


int Node::returnDigitalOutputPort(const String pinIdentifier){
            
    if(pinIdentifier[1]=='1'){
        return 23;
    }
    if(pinIdentifier[1]=='2'){
        return 22;
    }
    if(pinIdentifier[1]=='3'){
        return 21;
    }
    if(pinIdentifier[1]=='4'){
        return 19;
    }
    if(pinIdentifier[1]=='5'){
        return 18;
    }
    if(pinIdentifier[1]=='6'){
        return 5;
    }
    if(pinIdentifier[1]=='7'){
        return 17;
    }
    else{
        return 41;
    }
}


int Node::returnAnalogInputPort(const String pinIdentifier){
    if(pinIdentifier[3]=='0'){
        return 36;
    }
    if(pinIdentifier[3]=='1'){
        return 39;
    }
    if(pinIdentifier[3]=='2'){
        return 34;
    }
    return 41;    
}


int Node::initDigitalInput(const String pinIdentifier){
    if(pinIdentifier.length()<4 && pinIdentifier.length()!=0 && pinIdentifier[0]=='I'){
        int port = returnDigitalInputPort(pinIdentifier);
        if(port != 41){
            pinMode(port, INPUT);
            return 1;
        }
        else{
            //log_e("Invalid pin identifier");
            return 2;
        }
    }
    else{
        //log_e("Invalid pin identifier");
        return 3;
    }
}


int Node::initDigitalOutput(const String pinIdentifier){
    if(pinIdentifier.length() < 4 && pinIdentifier.length() != 0 && pinIdentifier[0] == 'O'){
        int port = returnDigitalOutputPort(pinIdentifier);
        if(port != 41){
            pinMode(port, OUTPUT);
            return 1;
        }
        else{
            //log_e("Invalid pin identifier");
            return 2;
        }
    }
    else{
        //log_e("Invalid pin identifier");
        return 3;
    }
}


int Node::readDigitalPort(const String pinIdentifier){ //Verificar se esta inicializado
    if(pinIdentifier.length()<4 && pinIdentifier.length()!=0 && pinIdentifier[0]=='I'){
        int port = returnDigitalInputPort(pinIdentifier);
        if(port != 41){
            return digitalRead(port);
        }
        else{
            //log_e("Invalid pin identifier");
            return -1;
        }
    }
    else{
        //log_e("Invalid pin identifier");
        return -1;
    }
}


bool Node::writeDigitalPort(const String pinIdentifier, int value){ //Verificar se esta inicializado
    if(pinIdentifier.length()<4 && pinIdentifier.length()!=0 && pinIdentifier[0]=='O'){
        int port = returnDigitalOutputPort(pinIdentifier);
        if(port != 41){
            digitalWrite(port, value);
            return true;
        }
        else{
            //log_e("Invalid pin identifier");
            return false;
        }
    }
    else{
        //log_e("Invalid pin identifier");
        return false;
    }
}


int Node::readAnalogPort(const String pinIdentifier){
    if(pinIdentifier.length()<4 && pinIdentifier.length()!=0 && pinIdentifier[0]=='A'){
        int port = returnAnalogInputPort(pinIdentifier);
        if(port != 41){
            return analogRead(port);
        }
        else{
            //log_e("Invalid pin identifier");
            return false;
        }
    }
    else{
        //log_e("Invalid pin identifier");
        return false;
    }
}


int returnSSnPort(){
    return 15;
}


int returnMOSIPort(){
    return 13;
}


int returnMISOPort(){
    return 12;
}


int returnSCKLPort(){
    return 14;
}
