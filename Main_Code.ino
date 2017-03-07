#include "Arduino.h"
#include "SoftwareSerial.h"
#include "enes100.h"
#include <dfr_tank.h>

#define PI 3.1415926

DFRTank tank;

SoftwareSerial mySerial(8, 9);
Marker marker(99);
RF_Comm rf(&mySerial, &marker);

void setup(){
    rf.startMission();
    Serial.begin(9600);
    tank.init();
}

void loop(){
    
    delay(10);
        
    if (rf.updateLocation()){

    }
}
