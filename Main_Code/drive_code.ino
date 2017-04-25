#include <stdio.h>
#include <math.h>

#include "drive_code.h"
#include "hardware.h"

const int
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,

PWM_B = 11,
DIR_B = 13,
BRAKE_B = 8;

void init_drive(){
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_B, OUTPUT);
}

/******** Basic drive code below ********/

float ang_thresh = 0.05, min_pwr = 255;
int turn_to_ang(float ang){
        float err = mrk.theta - ang;      
        float turn_pwr = signum_flt(err)  * min_pwr;/* + rescale_angle(err);*/
        
       /* cap(&turn_pwr, 250.0);*/
	drive((int) turn_pwr, -(int) turn_pwr);

        rf.print("Error: ");
        rf.println(err);

	if(abs_flt(err) < ang_thresh) return 1;
        return 0;
}

/* float abs */
static float abs_flt(float f){
  if(f > 0) return  f;
  if(f < 0) return -f;
  return 0;
}

/* float signum */
static float signum_flt(float f){
  if(f > 0) return  1;
  if(f < 0) return -1;
  return 0;
}

static float max_flt(float a, float b){
  if(a > b) return a;
  return b; 
}

/* rescales the error */
float rescale_angle(float ang){
        ang *= 200;
	return ang;
}

/* caps a value to a level */
void cap(float *val, float cap){
  if(*val > cap){
    *val = cap; 
  } else if(*val < -cap){
    *val = -cap; 
  }
}

int drive(int port, int star){
   drive_OSV(port, star); // Because apparently we can't build an OSV with two of the same motor 
}

int drive(int pwr){
   drive(pwr, pwr); 
}

flaot scale = 25;
int maintain_heading(float heading){
  float p_pwr = 255 + scale * (mrk.theta - heading),
        s_pwr = 255 - scale * (mrk.theta - heading), 
        max_pwr = max_flt(p_pwr, s_pwr);
        
  p_pwr *= 255.0 / max_pwr;
  s_pwr *= 255.0 / max_pwr;
  
  drive(p_pwr, s_pwr);
}

/* Sets left motor to port and right motor to star 
   brakes if either = 0 */
static int drive_OSV(int port, int star){
  if(port != 0) {
    digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
    digitalWrite(DIR_A, (port > 0) ? HIGH : LOW);   // setting direction - HIGH the motor will spin forward
  } else {
    digitalWrite(BRAKE_A, HIGH);  // setting brake HIGH enables motor brake
  }
  if(star != 0){
    digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
    digitalWrite(DIR_B, (star > 0) ? HIGH : LOW);   // setting direction - LOW the motor will spin forward
  } else {
    digitalWrite(BRAKE_B, HIGH);  // setting brake HIGH enables motor brake 
  }
  analogWrite(PWM_A, abs(port));
  analogWrite(PWM_B, abs(star));
}

/* testing __ONLY__ */
static int drive_tank(int port, int star){
 // tank.setLeftMotorPWM(port);
 //s tank.setRightMotorPWM(star);
}
