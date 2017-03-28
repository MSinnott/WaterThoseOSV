#include "Arduino.h"
#include "drive_code.h"

void setup(){
    rf.startMission();
    Serial.begin(9600);
    init_drive();
}

void loop(){
  delay(10);
  turn_to_angle(PI/2);
}
