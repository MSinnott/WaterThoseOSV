#include <stdio.h>
#include <math.h>

#include <dfr_tank.h>
#include "SoftwareSerial.h"
#include "enes100.h"

#include "drive_code.h"

void init_drive(){
  tank.init();
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
	while(abs(mrk.theta - ang) > ang_thresh){
		rf.updateLocation();
		float pwr = rescale_angle(mrk.theta - ang);
		drive(pwr, -pwr);
	}
	drive(0, 0);
}

float rescale_angle(float ang){
        ang *= 500;
	return ang;
}

/* Sets left motor to port and right motor to star */
int drive(float port, float star){
    tank.setLeftMotorPWM(port);
    tank.setRightMotorPWM(star);
}
