#pragma once 

#ifndef OPCONTROL_H
#define OPCONTROL_H 

#include "vex.h"
#include "Functions.h"
#include "Autos.h"

bool pres[] = {0,0,0,0,0,0,0};  // To store data about all buttons 
bool state[] = {0};             // To store data about Speed of the Base
int BackState = 1;              // Old! To Store needed position of the back lift 
int FrontLiftState = 0;         // Old! Helpful! To Store needed position of the front lift
int SpeedLimit = 10000;         // To give speed limit for the base 
double TurnLimit = 1;           // to give turning limit for the base
double axisright;               // for the Arcade control
double axisleft;
int Start = 35;                 // to count some seconds to make sure that Intake will fold out
bool StartPressed = false;      // to state the start
// double axisFront;            // for the Arcade Control
// double axisturn;
bool FrontLiftForce = false;    // To Put Max Force by using two pistons instead of one

void Base(){
                                // Arcade Control
  // axisFront = (Controller1.Axis3.position() * Controller1.Axis3.position() * Controller1.Axis3.position()) / SpeedLimit;
  // axisturn = ((Controller1.Axis1.position() * Controller1.Axis1.position() * Controller1.Axis1.position()) / 15000);
  // axisright = (axisFront - axisturn);
  // axisleft = (axisFront + axisturn);
                                // Tank Control
  axisright = (Controller1.Axis2.position() * Controller1.Axis2.position() * Controller1.Axis2.position()) / (SpeedLimit * TurnLimit);
  axisleft = (Controller1.Axis3.position() * Controller1.Axis3.position() * Controller1.Axis3.position()) / (SpeedLimit * TurnLimit);
                                // Button Control
  // Double state button for Speed Control 
  if(Controller1.ButtonDown.pressing() or Controller1.ButtonRight.pressing() 
  or Controller1.ButtonUp.pressing() or Controller1.ButtonLeft.pressing()){
    if(pres[6] == false){ 
      pres[6] = true;
      state[0] = !state[0];
    }
  }else{
    pres[6] = false;
  }
  // To Limit The Speed of turning
  if(Controller1.Axis2.position() * Controller1.Axis3.position() < 0){
    if(SpeedLimit == 25000){
      TurnLimit = 1.35;
    }else{
      TurnLimit = 2.3;
    }
  }else{
    TurnLimit = 1;
  }
  // Speed Limiting 
  if(!state[0]){
    SpeedLimit = 10000;
  }else{
    SpeedLimit = 25000;
  }
  // Driving the Motors
  Right1.spin(forward, axisright, percent);
  Right2.spin(forward, axisright, percent);
  Right3.spin(forward, axisright, percent);
  Left1.spin(forward, axisleft, percent);
  Left2.spin(forward, axisleft, percent);
  Left3.spin(forward, axisleft, percent);
}

int Setup(){ // Setting down the lift automatically for making autonomous functions to work properly
  FrontLift.spin(forward, -70, percent);
  delay(100);
  while(start == 0){
    delay(10);
    if(FrontLift.velocity(percent) == 0){
      start = true;
      FrontLift.setPosition(-40, degrees);
      FrontLift.spin(forward, 0, percent);
    }
  }
  return 0;
}

void Arms(){ // Control of the Arms and Intake
  if(start){
    if(Controller1.ButtonR1.pressing() and FrontLift.position(degrees) < 1300 ){
      FrontLift.spin(forward,100,percent);
    }else if(Controller1.ButtonR2.pressing() and FrontLift.position(degrees) > 0){
      FrontLift.spin(forward,-100,percent);
    }else{
      FrontLift.spin(forward,0,percent);
      FrontLift.setStopping(hold);
    }

    // Old! Automatic positioning system for the lift by power level 

    // if(Controller1.ButtonR1.pressing()){
    //   if(FrontLiftState < 2 and pres[2] == false){
    //     FrontLiftState ++;
    //   }
    //   pres[2] = true;
    // }else{
    //   pres[2] = false;
    // }
    // if(Controller1.ButtonR2.pressing()){
    //   if(FrontLiftState > 0 and pres[3] == false){
    //     FrontLiftState --;
    //   }
    //   pres[3] = true;
    // }else{
    //   pres[3] = false;
    // }
    // if(FrontLiftState == 0){
    //   if(Controller1.ButtonY.pressing() or Controller1.ButtonB.pressing()){
    //     FrontLift.spin(forward, LiftPID(FrontLiftleft, 150), percent);
    //   }else{
    //     FrontLift.spin(forward, LiftPID(FrontLiftleft, 40), percent);
    //   }
    // }else if(FrontLiftState == 1){
    //   FrontLift.spin(forward, LiftPID(FrontLiftleft, 300), percent);
    // }else if(FrontLiftState == 2){
    //   FrontLift.spin(forward, LiftPID(FrontLiftleft, 1100), percent);
    // }
  }
  // Double state button
  if(Controller1.ButtonY.pressing()){
    if(pres[0] == false){
      IntakeState = !IntakeState;
      pres[0] = true;
    }
  }else{
    pres[0]= false;
  }
  
  if(StartPressed){
    BublikIntake.spin(forward, -80, percent);
  }else if(Controller1.ButtonA.pressing()){
    BublikIntake.spin(forward, -80, percent);
  }else{
    BublikIntake.spin(forward, IntakeSpeed() * IntakeState, percent);
  }
}

void Claws(){ // Claw Control
  if(Controller1.ButtonL2.pressing()){
    if(Start == 35){
      StartPressed = true;
    }
    if(pres[5] == false){
      Back.set(!Back.value());
      pres[5] = true;
    }
  }else{
    pres[5]= false;
  }
  if(Controller1.ButtonL1.pressing() or StartPressed){
    if(pres[4] == false){
      FrontRight.set(!FrontRight.value());
      if(FrontLiftForce){
        FrontLeft.set(FrontRight.value());
      }
      pres[4] = true;
    }
  }else{
    pres[4] = false;
  }
  if(Controller1.ButtonLeft.pressing()){
    if(pres[2] == false){
      FrontLiftForce = true;
      FrontLeft.set(FrontRight.value());
      pres[2] = true;
    }
  }else{
    pres[2] = false;
  }
  // FrontLiftClaw.spin(forward, ClawPID((ClawState[0] * 15) + 32 + (FrontLiftState == 0  and ClawState[0]? -5 : 0)), percent);
}


int Control(){ // Overal Control 
  // task Gps(GPSPos);
  // task tan(Angle);
  while(true){
    if(StartPressed){
      Start --;
    }
    if(Start < 0){
      StartPressed = false;
    }
    Base();
    Arms();
    Claws();
    Controller1.Screen.print(Gyro.roll()); 
    Controller1.Screen.clearLine();

    delay(10);
  }
  return 1;
}





/*void BackArm(){
  if(Controller1.ButtonR1.pressing()){
    if(BackState < 3 and pres[0] == false){
      BackState ++;
    }
    pres[0] = true;
  }else{
    pres[0] = false;
  }
  if(Controller1.ButtonR2.pressing()){
    if(BackState > 0 and pres[1] == false){
      BackState --;
    }
    pres[1] = true;
  }else{
    pres[1] = false;
  }
  if(BackState == 0){
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