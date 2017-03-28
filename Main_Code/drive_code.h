#include "SoftwareSerial.h"
#include "enes100.h"
#include <dfr_tank.h>

#define SUCCEEDED  1
#define FAILED 	   0
#define PI         3.1415926

#ifndef DRIVE_LOCK
#define DRIVE_LOCK

DFRTank tank;

SoftwareSerial mySerial(8, 9);
Marker mrk(99);
RF_Comm rf(&mySerial, &mrk);

typedef struct Waypoint{
  float x, y;
  Waypoint *next; 
} Waypoint;

#endif

void init_drive();

int turn_to_angle(float ang);

int drive_to_waypt(Waypoint pt);

float rescale_angle(float ang);

float ang_to_turn(Marker loc, Waypoint wpt);

float dist_to_waypt(Marker loc, Waypoint wpt);

int drive(float port, float star);
