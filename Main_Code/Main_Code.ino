#include "Arduino.h"
#include "drive_code.h"
#include "hardware.h"

#include <SoftwareSerial.h>
#include "enes100.h"
#include <dfr_tank.h>

void setup(){
    rf.startMission();
    mySerial.begin(9600);
    init_drive();
}

void loop(){
  turn_to_ang(PI/2);
}
