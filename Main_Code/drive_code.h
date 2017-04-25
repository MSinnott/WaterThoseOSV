#ifndef DRIVE_H
#define DRIVE_H



#define SUCCEEDED  1
#define FAILED 	   0
#define PI         3.1415926

#include "enes100.h"

#endif

void init_drive();

int turn_to_ang(float ang);

float rescale_angle(float ang);

int drive(int port, int star);

int drive(int pwr);

int maintain_heading(float heading);
