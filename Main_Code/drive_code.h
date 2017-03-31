#ifndef DRIVE_H
#define DRIVE_H

#define SUCCEEDED  1
#define FAILED 	   0
#define PI         3.1415926

#include "enes100.h"

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

int drive(int port, int star);
