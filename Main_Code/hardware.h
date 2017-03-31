#ifndef HARDWARE_H
#define HARDWARE_H

#include <SoftwareSerial.h>
#include "enes100.h"
#include <dfr_tank.h>

SoftwareSerial mySerial(8, 9);
Marker mrk(11);
RF_Comm rf(&mySerial, &mrk);

#endif
