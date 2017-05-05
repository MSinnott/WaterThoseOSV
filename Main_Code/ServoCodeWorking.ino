#include <Servo.h>

int pingPin = 2;
int servoPin = 5;
int water_servo_pin = 4;
int servoAngle = 0;
int limitSwitch = A1;
int salinityPin = A0;
boolean saltFlag = false;
int pump[] = {36, 37};

Servo servo;
Servo water_servo;
void init_sensors() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pump[0], OUTPUT);
  pinMode(pump[1], OUTPUT);
  resetServo();
  servo.detach();
}

void loop_sensors() {
  Serial.println("Calculated Depth : " +  (String)measureDepth() + " cm");
  //Serial.println(analogRead(salinityPin));
  delay(5000);
//  for(servoAngle = 0; servoAngle < 180; servoAngle++){  //move the micro servo from 0 degrees to 180 degrees                              
//    servo.write(servoAngle);              
//    delay(50);                  
//  }
}
void resetServo(){
  servo.attach(servoPin);
  servo.write(180);
}

double measureDepth(){
  int topOfWater = 180;
  int flag = 0;
  
  int servoAngle = 180;
  servo.attach(servoPin);
  servo.write(servoAngle);
  boolean limit = false;
  while(!limit){
    //Serial.println(analogRead(limitSwitch));
    if(analogRead(limitSwitch) > 512){
      Serial.println((String) ("Bottom hit at theta = " + (String)servoAngle));
      limit = true;
    }
    servoAngle--;
    if(servoAngle == 0) servoAngle = 180;
    servo.write(servoAngle);
    Serial.println((String) ("Conductivity = " + (String) analogRead(salinityPin)));
    if(flag == 0 && analogRead(salinityPin)>25){
      Serial.println((String) ("Water hit at theta = " + (String) servoAngle));
        
      topOfWater = servoAngle;
      flag = 1;
      
    }
    if(analogRead(salinityPin)>=50){
      saltFlag = true;
    }
     delay(50);
  }
  
  servo.write(180);
  return((servoAngle-topOfWater)*(6.0*3.14159/360.0));          
}

void retrieve_water(){
  water_servo.attach(water_servo_pin);
  water_servo.write(0);
  delay(1000);
  water_servo.write(180);
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


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
