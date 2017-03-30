#include <Servo.h>

int pingPin = 2;
int servoPin = 5;
int servoAngle = 0;
int limitSwitch = 6;
int salinityPin = A0;

int pump[] = {36, 37};
const int
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,

PWM_B = 11,
DIR_B = 13,
BRAKE_B = 8;


Servo servo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_B, OUTPUT);
  
  servo.attach(servoPin);
  int i;
  
  pinMode(pump[0], OUTPUT);
  pinMode(pump[1], OUTPUT);
  
}

void loop() {
  forward();
  pump_in();
  delay(1000);
  pump_stop();
  delay(1000);
  pump_out();
  delay(1000);
//  for(servoAngle = 0; servoAngle < 180; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
//  {                                  
//    servo.write(servoAngle);              
//    delay(50);                  
//  }

  
}
int topOfWater = 0;
int measureDepth(){
  int flag = 0;
  int servoAngle = 0;
  servo.write(servoAngle);
  
  while(digitalRead(limitSwitch)!=HIGH){
    servoAngle = (servoAngle+1 % 180);
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

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  
  return cm;
}
void forward(){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);\
void forward(){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void backward(){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW;   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void brake(){
  digitalWrite(BRAKE_A, HIGH);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW;   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, HIGH);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void turn_clockwise(){
   digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW;   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void turn_counterclockwise(){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, HIGH;   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}  // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void backward(){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void brake(){
  digitalWrite(BRAKE_A, HIGH);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, HIGH);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void turn_clockwise(){
   digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, LOW);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}
void turn_counterclockwise(){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_A, 255);     // Set the speed of the motor, 255 is the maximum value
  digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward
  analogWrite(PWM_B, 255);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

