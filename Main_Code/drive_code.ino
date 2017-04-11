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

int drive_to_site(){

}


/******** Basic drive code below ********/

float ang_thresh = 0.05;
int turn_to_ang(float ang){
        float err = mrk.theta - ang;      
        float turn_pwr = signum(err) * 220 + rescale_angle(err);
        
        cap(&turn_pwr, 250);
	drive(turn_pwr, -turn_pwr);

        char prnt[100];
        sprintf(prnt, "Err: %f\n", err);
        rf.println(prnt);

	return abs(err) < ang_thresh;
}

static int signum(int f){
  if(f > 0) return  1;
  if(f < 0) return -1;
  return 0;
}

float rescale_angle(float ang){
        ang *= 200;

	return ang;
}

void cap(float *val, float cap){
  if(*val > cap){
    *val = cap; 
  } else if(*val < -cap){
    *val = -cap; 
  }
}

int drive(int port, int star){
   drive_OSV(port, star); 
}

int drive(int pwr){
   drive(pwr, pwr); 
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

static int drive_tank(int port, int star){
  tank.setLeftMotorPWM(port);
  tank.setRightMotorPWM(star);
}
