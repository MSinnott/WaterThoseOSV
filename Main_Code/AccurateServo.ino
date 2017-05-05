#include <Servo.h>
int servoPin = 5;
Servo servo;

boolean saltFlag = false;
void setup(){
  servo.attach(5);
  servo.write(180);
  Serial.begin(9600);
}

void loop(){
Serial.println("MEASURED DEPTH" + (String)measureDepthAccurately());
delay(5000);
}
double measureDepthAccurately(){
  double depth = measureDepth();
  delay(3000);
  if((depth <= 4.4 && depth >= 2.2)){
    return depth;
  }else{
    while(!(depth <= 4.4 && depth >= 2.2)){
      depth = measureDepth();
      delay(5000);
    }
    return depth;
  }
}
  int salinityPin = A0;
  int limitSwitch = A1;
  
 double measureDepth(){
   int flag = 0;
   int limitflag = 0;
   int servoAngle = 180;
   int topOfWater = 180;
   servo.write(servoAngle);
   
   while(limitflag==0){
    
    Serial.println("salt : " + (String)analogRead(A0) + "topOfWater: " + (String)topOfWater +" ServoAngle: " + (String)servoAngle  + " " + (topOfWater-servoAngle)*(6.0*3.14159/360.0));
    
     if(analogRead(limitSwitch) >= 500){
       Serial.println("Bottom hit at theta = " + (String)servoAngle);
       limitflag = 1;
       servo.write(180);
       return((topOfWater-servoAngle)*(6.0*3.14159/360.0)); 
     }
    
     servo.write(servoAngle);
     if(flag == 0 && analogRead(salinityPin)>25 && servoAngle<110){
       Serial.println("Water hit at theta = " + (String) servoAngle);
         
       topOfWater = servoAngle;
       flag = 1;
       
     }
     if(analogRead(salinityPin)>=50){
       saltFlag = true;
     }
     servoAngle = ((servoAngle -1));
     if(servoAngle<=0){
      servoAngle = 180;
     }
      
      delay(50);
     
   }
   
         
 }
