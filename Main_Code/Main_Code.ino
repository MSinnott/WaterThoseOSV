#include "enes100.h"
#include "marker.h"
#include "rf_comm.h"

#include "Arduino.h"
#include "drive_code.h"
#include "hardware.h"
#include "ServoCodeWorking.h"

#include <SoftwareSerial.h>
//#include <dfr_tank.h>

SoftwareSerial mySerial(6, 7);
Marker mrk(5);
RF_Comm rf(&mySerial, &mrk);

//DFRTank tank;

void setup(){
    Serial.begin(9600);
    init_drive(); 
    init_sensors();
    rf.println("Initialized!!");
}

int stage = 1, pwr = 255, dist_mark = 42;
void loop(){
  int upd = rf.updateLocation();
  if (upd == 1){
      switch(stage){
	    case 1:
                stage += turn_to_ang(PI/2);
                rf.println("Turning to PI/2");
		break;
	    case 2:
                maintain_heading(PI/2);
                stage += (mrk.y >= 1.65);
                rf.println("Driving to y >= 1.6");
		break;
	    case 3:
                stage += turn_to_ang(0);
                rf.println("Turning to 0");                
		break;
	    case 4:
                if(getDist() < dist_mark) {
                  stage = 5;
                  rf.print((double) getDist());
                  rf.println(" -- Seeing wall... skipping");                  
                  break; 
                }
                maintain_heading(0);
		stage += (mrk.x >= 1.4);
                rf.println("Driving to x >= 1.35");                 
                break;
            // Go to bottom!!!
            case 5:
                stage += turn_to_ang(-PI/2);
                rf.println("Turning to -PI/2");                
                break;
            case 6:
                maintain_heading(-PI/2);
                stage += (mrk.y <= 0.4);
                rf.println("Driving to y <= 0.37");
		break;
	    case 7:
		stage += turn_to_ang(0);
                rf.println("Turning to 0");
		break;
	    case 8:
                maintain_heading(0);
		stage += (mrk.x >= 2.28);
                rf.println("Driving to x >= 2.28");
                break;
	    case 9:
		drive(0);
                rf.println(measureDepth());
                retrieve_water();
                break;
	    default:
		break;
           }
    }
}
