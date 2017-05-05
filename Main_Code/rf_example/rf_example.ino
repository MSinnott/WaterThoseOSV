#include "enes100.h"


SoftwareSerial mySerial(8, 9);
Marker marker(3);
RF_Comm rf(&mySerial, &marker); 

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (rf.updateLocation()) {
    Serial.println("Huzzah!");
    Serial.print("Marker 3’s X coordinate is: ");
    Serial.println(marker.x);
  }else{
    Serial.println("Jeepers! Something’s gone wrong...");
  }
  rf.println("Can you hear me now?");
  delay(500);
  if(rf.transmitData(NAV, CHEMICAL)){
    rf.println("Navigation completed!");
  }else{
    rf.println("Awww");
    rf.transmitData(END_MISSION, NO_DATA);
  }
}
