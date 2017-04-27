#include <Servo.h>

int pingPin = 2;
int servoPin = 5;
int servoAngle = 0;
int limitSwitch = 10;
int salinityPin = A0;

int pump[] = {36, 37};

Servo servo;
void init_sensors() {
  // put your setup code here, to run once:

  servo.attach(servoPin);
  
  pinMode(pump[0], OUTPUT);
  pinMode(pump[1], OUTPUT);
}

void loop_prime() {
  pump_in();
  delay(1000);
  pump_stop();
  delay(1000);
  pump_out();
  delay(1000);
//  for(servoAngle = 0; servoAngle < 180; servoAngle++){  //move the micro servo from 0 degrees to 180 degrees                              
//    servo.write(servoAngle);              
//    delay(50);                  
//  }
}

int topOfWater = 0;
int measureDepth(){
  int flag = 0;
  int servoAngle = 180;
  servo.write(servoAngle);
  
  while(digitalRead(limitSwitch)!=HIGH){
    delay(50);
    servoAngle = (servoAngle-1 % 180);
    servo.write(servoAngle);
    if(flag == 0 && analogRead(salinityPin)<1000){
      topOfWater = servoAngle;
      flag = 1;
    }
  }
  return(topOfWater-servoAngle);          
}

void pump_stop(){
  digitalWrite(pump[0], LOW); 
  digitalWrite(pump[1], LOW); 
}

void pump_in(){
  digitalWrite(pump[0], HIGH); 
  digitalWrite(pump[1], LOW); 
}

void pump_out(){
  digitalWrite(pump[0], LOW); 
  digitalWrite(pump[1], HIGH); 
}

int getDist(){
  long duration, cm;

  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  
  return cm;
}

float getDist_Tank(){
   float val = analogRead(A4);
   return 0.0016*(val*val)-1.8163*(val)+608.76;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

