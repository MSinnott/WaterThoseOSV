#include "enes100.h"
#include "marker.h"
#include "rf_comm.h"

#include "Arduino.h"
#include "drive_code.h"
#include "hardware.h"

#include <SoftwareSerial.h>
//#include <dfr_tank.h>

SoftwareSerial mySerial(6, 7);
Marker mrk(11);
RF_Comm rf(&mySerial, &mrk);

//DFRTank tank;

void setup(){
    //mySerial.begin(9600);
    init_drive(); 
    rf.println("Initialized!!");
}

int stage = 1, pwr = 230, dist_mark = 18;
void loop(){
  int upd = rf.updateLocation();
  if (upd == 1){
      delay(300);
      rf.println(upd);
      delay(300);

      switch(stage){
	    case 1:
                stage += turn_to_ang(PI/2);
                rf.println("Turning to PI/2");
		break;
	    case 2:
                drive(pwr);
                stage += (mrk.y >= 1.5);
                rf.println("Driving to y >= 1.5");
		break;
	    case 3:
                stage += turn_to_ang(0);
                rf.println("Turning to 0");                
		break;
	    case 4:
                if(getDist() < dist_mark) {
                  stage = 5;
                  rf.println("Seeing wall... skipping");                  
                  break; 
                }
                drive(pwr);
		stage += (mrk.x >= 1.5);
                rf.println("Driving to x >= 1.5");                 
                break;
            // Go to bottom!!!
            case 5:
                stage += turn_to_ang(-PI/2);
                rf.println("Turning to -PI/2");                
                break;
            case 6:
                drive(pwr);
                stage += (mrk.y <= 0.5);
                rf.println("Driving to y <= 0.5");
		break;
	    case 7:
		stage += turn_to_ang(0);
                rf.println("Turning to 0");
		break;
	    case 8:
                drive(pwr);
		stage += (mrk.x >= 2.6);
                rf.println("Driving to x >= 2.6");
                break;
	    case 9:
		drive(0);
                rf.println("Done!");
                break;
	    default:
		break;
           }
    }
}
