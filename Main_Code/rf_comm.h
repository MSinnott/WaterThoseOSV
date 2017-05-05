/* Copyright © 2017 Elan Hamburger, Karam Singh, Bryan Zeug
 *
 * This software created for the exclusive use of the University of Maryland
 * at College Park. Any other use of this software requires the explicit
 * permission of the creators.
 */

#ifndef RF_COMM_H
#define RF_COMM_H

#include "marker.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

//objectives
#define START_MISSION "Start Mission"
#define NAV "Navigation: "
#define BASE "Base: "
#define BONUS "Bonus: "
#define END_MISSION "End of Mission"
//missions
#define CHEMICAL "Chemical Team"
#define FIRE "Fire Team"
#define WATER "Water Team"
#define TERRAIN "Terrain Team"
#define MATERIAL "Material Team"

//Mission-specific defines
#define FIRE_SITE_A "Fire Site A is lit"
#define FIRE_SITE_B "Fire Site B is lit"
#define FIRE_SITE_C "Fire Site C is lit"
#define FIRE_SITE_D "Fire Site D is lit"

#define COPPER "Debris is COPPER"
#define STEEL "Debris is STEEL"

#define GREEN "Terrain is GREEN"
#define BLACK "Terrain is BLACK"

#define FRESH "Pool is FRESH WATER"
#define SALT "Pool is SALT WATER"

#define NO_DATA ""
class RF_Comm {
  private:
    SoftwareSerial *sSerial;
    Marker *marker;

    void splitMission() {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit command
      this->sSerial->print("#lapTimer*");
      // Flush the buffer
      this->sSerial->flush();
    }

    void stopMission() {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit command
      this->sSerial->print("#stopTimer*");
      // Flush the buffer
      this->sSerial->flush();
      while(1);
    }

    void startMission() {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit command
      this->sSerial->print("#startTimer*");
      // Flush the buffer
      this->sSerial->flush();
    }

    void checkMission(String obj, String data){
      /*
      SPRING 17 REQUIREMENTS:
        -Stop mission will be called when END_MISSION is received
      */
      if(obj == END_MISSION){
        stopMission();
      }else if(obj == NAV && data == CHEMICAL){
        splitMission();
      }
    }

    int calls[5] = {1, 1, 2, 2, 1};

    bool checkCalls(String obj){
      int i;
      if(obj == START_MISSION){
        i = 0;
      }else if(obj == NAV){
        i = 1;
      }else if(obj == BASE){
        i = 2;
      }else if(obj == BONUS){
        i = 3;
      }else if(obj == END_MISSION){
        i = 4;
      }else{
        return false;
      }
      if(calls[i]){
        calls[i]--;
        return true;
      }else{
        return false;
      }
    }

  public:
    RF_Comm(SoftwareSerial *s, Marker *m) {
      this->sSerial = s;
      this->sSerial->begin(9600);
      this->sSerial->flush();
      startMission();
      transmitData(START_MISSION, NO_DATA);
      this->marker = m;
    }

    void print(const char *msg) {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit message
      this->sSerial->print(msg);
      // Flush the buffer
      this->sSerial->flush();
    }

    void print(int num) {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit message
      this->sSerial->print(num);
      // Flush the buffer
      this->sSerial->flush();
    }

    void print(double num) {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit message
      this->sSerial->print(num);
      // Flush the buffer
      this->sSerial->flush();
    }

    void println(const char *msg) {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit message
      this->sSerial->print(msg);
      this->sSerial->print('\n');
      // Flush the buffer
      this->sSerial->flush();
    }

    void println(int num) {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit message
      this->sSerial->print(num);
      this->sSerial->print('\n');
      // Flush the buffer
      this->sSerial->flush();
    }

    void println(double num) {
      // Flush the buffer
      this->sSerial->flush();
      // Transmit message
      this->sSerial->print(num);
      this->sSerial->print('\n');
      // Flush the buffer
      this->sSerial->flush();
    }

    bool transmitData(String obj, int data){
      if(checkCalls(obj)){
        this->sSerial->flush();
        // Transmit message
        this->sSerial->print("#tdStart*");
        this->sSerial->print(obj);
        this->sSerial->print(data);
        this->sSerial->print("#tdEnd*");
        checkMission(obj, "");
        // Flush the buffer
        this->sSerial->flush();
        return true;
      }else{
        return false;
      }
    }

    bool transmitData(String obj, String data){
      if(checkCalls(obj)){
        this->sSerial->flush();
        // Transmit message
        this->sSerial->print("#tdStart*");
        this->sSerial->print(obj);
        this->sSerial->print(data);
        this->sSerial->print("#tdEnd*");
        checkMission(obj, data);
        // Flush the buffer
        this->sSerial->flush();
        return true;
      }else{
        return false;
      }
    }

    bool transmitData(String obj, float data){
      if(checkCalls(obj)){
        this->sSerial->flush();
        // Transmit message
        this->sSerial->print("#tdStart*");
        this->sSerial->print(obj);
        this->sSerial->print(data);
        this->sSerial->print("#tdEnd*");
        checkMission(obj, "");
        // Flush the buffer
        this->sSerial->flush();
        return true;
      }else{
        return false;
      }
    }

    int updateLocation() {
      // Send request to Vision System
      this->sSerial->print('#');
      this->sSerial->print(this->marker->num);
      this->sSerial->print('*');
      // Flush the buffer
      this->sSerial->flush();
      // Begin tracking time
      unsigned long start = millis();
      int state = 0;
      while((millis() - start) < 600) {
        if(this->sSerial->available()) {
          switch(state) {
            // Marker ID
            case 0:
              if(this->sSerial->parseInt() == this->marker->num)
                state++;
              break;
            // X Coordinate
            case 1:
              this->marker->x = this->sSerial->parseFloat();
              state++;
              break;
            // Y Coordinate
            case 2:
              this->marker->y = this->sSerial->parseFloat();
              state++;
              break;
            // Theta
            case 3:
              this->marker->theta = this->sSerial->parseFloat();
              return 1;
              break;
            default:
              return 0;
              break;
          }
        }

      }

      return 0;
    }
};

#endif
