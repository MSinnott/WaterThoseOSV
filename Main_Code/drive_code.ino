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

int drive(){
	Waypoint *pt;
	while(pt->next != NULL){
		//Code below used for sharp turns?? 
		//float ang = ang_to_turn(mrk, wpt);
		//turn_to_angle(ang);
		
		drive_to_waypt(*pt);
		pt = pt->next;
	}
}

float d_thresh = 0.05;
float base_pwr = 0.75;
int drive_to_waypt(Waypoint pt){
	while(dist_to_waypt(mrk, pt) < d_thresh){
		float ang = ang_to_turn(mrk, pt);
		float turn_pwr = rescale_angle(mrk.theta - ang);
		drive(base_pwr + turn_pwr, base_pwr - turn_pwr);
		rf.updateLocation();
	}
}



float ang_to_turn(Marker loc, Waypoint wpt){
	float ang = atan((loc.y - wpt.y) / (loc.x - wpt.x));
	return ang;
}

float dist_to_waypt(Marker loc, Waypoint wpt){
	return sqrt(((loc.y - wpt.y) * (loc.y - wpt.y))/ ((wpt.x - loc.x) * (wpt.x - loc.x)));
}

/******** Basic drive code below ********/

float ang_thresh = 0.05;
int turn_to_angle(float ang){
        float err = 0;
        rf.updateLocation();
	while(1){
		rf.updateLocation();
		err += mrk.theta - ang;
                float pwr = rescale_angle(mrk.theta - ang + err);
                mySerial.print("Pwr:");
                mySerial.println(pwr);
		if(pwr > 0) {
			drive((int) abs(pwr), 0);
		} else {
			drive(0, (int) abs(pwr));
		}
	}
}

float rescale_angle(float ang){
        ang *= 500;
        if(abs(ang) > 230){
           ang = abs(ang)/ang * 230; 
        }
	return ang;
}

/* Sets left motor to port and right motor to star 
   brakes if either = 0 */
int drive(int port, int star){
  if(port != 0) {
    digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
    digitalWrite(DIR_A, (port > 0) ? HIGH : LOW);   // setting direction - HIGH the motor will spin forward
  } else {
    digitalWrite(BRAKE_A, HIGH);  // setting brake HIGH enables motor brake
  }
  if(star != 0){
    digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
    digitalWrite(DIR_B, (star > 0) ? HIGH : LOW);   // setting direction - HIGH the motor will spin forward
  } else {
    digitalWrite(BRAKE_B, HIGH);  // setting brake HIGH enables motor brake 
  }
  analogWrite(PWM_A, abs(port));
  analogWrite(PWM_B, abs(star));
}
