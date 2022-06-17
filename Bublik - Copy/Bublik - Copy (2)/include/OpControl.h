#pragma once 

#ifndef OPCONTROL_H
#define OPCONTROL_H 

#include "vex.h"
#include "Functions.h"
#include "Autos.h"

bool start[] = {0,0,0};
bool pres[7] = {0,0,0,0,0,0,0};
bool state[] = {0};
int BackState = 1;
int FrontState = 0;
bool FrontPlatform = false;
bool BackPlatform = false;
bool Platform = false;
int SpeedLimit = 10000;
double axisright;
double axisleft;
double axisfront;
double axisturn;

void Base(){
  axisfront = (Controller1.Axis3.position() * Controller1.Axis3.position() * Controller1.Axis3.position()) / SpeedLimit;
  axisturn = ((Controller1.Axis1.position() * Controller1.Axis1.position() * Controller1.Axis1.position()) / 15000);
  axisright = (axisfront - axisturn);
  axisleft = (axisfront + axisturn);
  if(Controller1.ButtonDown.pressing() or Controller1.ButtonRight.pressing() 
  or Controller1.ButtonUp.pressing() or Controller1.ButtonLeft.pressing()){
    if(pres[6] == false){
      pres[6] = true;
      state[0] = !state[0];
    }
  }else{
    pres[6] = false;
  }
  if(Controller1.ButtonY.pressing()){
    SpeedLimit = 20000;
  }else if(state[0]){
    SpeedLimit = 10000;
  }else{
    SpeedLimit = 30000;
  }
  Right.spin(forward, axisright, percent);
  Left.spin(forward, axisleft, percent);
}

int Control(){
  while(true){
    Base();
    // Controller1.Screen.print(EncoderLeft.position(degrees));
    // Controller1.Screen.clearLine();
    delay(10);
  }
  return 1;
}





/*void BackArm(){
  if(Controller1.ButtonB.pressing()){
    BackPlatform = true;
  }
  if(Controller1.ButtonA.pressing()){
    Platform = true;
  }
  if(Controller1.ButtonR1.pressing()){
    if(BackState < 3 and pres[0] == false){
      BackState ++;
    }
    Platform = false;
    BackPlatform = false;
    pres[0] = true;
  }else{
    pres[0] = false;
  }
  if(Controller1.ButtonR2.pressing()){
    if(BackState > 0 and pres[1] == false){
      BackState --;
    }
    Platform = false;
    BackPlatform = false;
    pres[1] = true;
  }else{
    pres[1] = false;
  }
  if(Platform == true){
    BackLift.spin(forward, LiftPID(backlift, 680),percent);
  }else if(BackPlatform == true){
    BackLift.spin(forward, LiftPID(backlift, 1700), percent);
  }else if(BackState == 0){
    BackLift.spin(forward, LiftPID(backlift, 0), percent);
  }else if(BackState == 1){
    BackLift.spin(forward, LiftPID(backlift, 70), percent);
  }else if(BackState == 2){
    BackLift.spin(forward, LiftPID(backlift, 230), percent);
  }else if(BackState == 3){
    BackLift.spin(forward, LiftPID(backlift, 1950), percent);
  }

  // if(Controller1.ButtonL1.pressing()){
  //   BackLift.spin(forward, 100, percent);
  // }else if(Controller1.ButtonL2.pressing()){
  //   BackLift.spin(forward, -100, percent);
  // }else{
  //   BackLift.spin(forward, 0, percent);
  //   BackLift.setStopping(hold);
  // }
}//*/
#endif 