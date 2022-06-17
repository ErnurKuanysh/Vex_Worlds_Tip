#pragma once 

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vex.h"

#define backlift 0
#define frontleft 1
#define frontright 2
#define right 0
#define left 1
#define side 3
#define turn 2
#define front 0
#define back 1

#define mid 188
#define lyft 10

#define defaultSpeed 50

#define Pi 3.1415926535

double Diameter = 13.3;

double MaxSpeed = defaultSpeed;
double MaxTurnSpeed = 50;

#define AngleError 1

#define BP 8
#define BD 32
#define TP 0.6
#define TD 7
double baseP[] = {BP, BP, TP};
double baseD[] = {BD, BD, TD};

double DrivingGoal = 0;
double LastGoal = 0;
double LastTurnGoal = 0;
double TurningGoal = 0;
bool DrivPIDEnabled = true;

double FrontLiftGoal = 0;
double BackLiftGoal = 0;

double Error;
double Derivative;
double LastError[] = {0,0,0,0,0,0,0};

double differenceRightLeft = 0;
double TurningK = 0.2;

double gyroAngle = 0;
int rotations = 0;
double gyroLastAngle = 0;
bool turningRight;
double visionSpeed;
double visionAngle;

bool VisionEnabled = false;

void Turn(int Goal){
  LastTurnGoal = TurningGoal;
  TurningGoal += Goal;
}

void Claw(bool grab){
  if(grab){
    Lift.setMaxTorque(100, percent);
    Lift.spin(forward, -20, percent);
  }else{  
    Lift.setMaxTorque(80, percent);
    Lift.spin(forward, 20, percent);
  }
}

void Purple() {
  VisionEnabled = true;
  int Time=0;
  while (true) {
    Vision.takeSnapshot(Vision__PURPLE_CUBE);
    if (Vision.objects[0].exists &&
        !(-(lyft) < Vision.objects[0].centerX - mid &&
          (lyft) > Vision.objects[0].centerX - mid)) {

      Time = 0;
    } else {
      Time++;
    }
    if (Time > 10) {
      VisionEnabled = false;
      Turn(TurningGoal - gyroAngle);
      break;
    }
    visionSpeed = ((Vision.objects[0].centerX - mid)) / -8;
    delay(5);
  }
  delay(50);
}

void Orange() {
  VisionEnabled = true;
  int Time=0;
  while (true) {
    Vision.takeSnapshot(Vision__ORANGE_CUBE);
    if (Vision.objects[0].exists &&
        !(-(lyft) < Vision.objects[0].centerX - mid &&
          (lyft) > Vision.objects[0].centerX - mid)) {

      Time = 0;
    } else {
      Time++;
    }
    if (Time > 10) {
      VisionEnabled = false;
      Turn(TurningGoal - gyroAngle);
      break;
    }
    visionSpeed = ((Vision.objects[0].centerX - mid)) / -8;
    delay(5);
  }
  delay(50);
}

void Green() {
  VisionEnabled = true;
  int Time=0;
  while (true) {
    Vision.takeSnapshot(Vision__GREEN_CUBE);
    if (Vision.objects[0].exists &&
        !(-(lyft) < Vision.objects[0].centerX - mid &&
          (lyft) > Vision.objects[0].centerX - mid)) {

      Time = 0;
    } else {
      Time++;
    }
    if (Time > 10) {
      VisionEnabled = false;
      Turn(TurningGoal - gyroAngle);
      break;
    }
    visionSpeed = ((Vision.objects[0].centerX - mid)) / -8;
    delay(5);
  }
  delay(50);
}


int Angle(){
  while(true){
    gyroAngle = (Left.position(degrees) - Right.position(degrees))/5.7;
    delay(10);
  }
}

double TurnCheck(double Speed){
  return Speed > MaxTurnSpeed ? MaxTurnSpeed : Speed < - MaxTurnSpeed ? - MaxTurnSpeed : Speed;
}

double Check(double Speed){
  return Speed > MaxSpeed ? MaxSpeed : Speed < -MaxSpeed ? - MaxSpeed : Speed;
}


double BasePos(int Type){
  return Type == right? ((Right.position(degrees) + Left.position(degrees)) / 2) * (Diameter / 360) : Type == left ? 
  ((Right.position(degrees) + Left.position(degrees)) / 2) * (Diameter / 360) : Type == turn ? gyroAngle :
  /*EncoderSide.position(degrees) * (8.66 / 360)*/ 0;
  
}

double BasePID(int Type, double Goal){  

  Error = Goal - BasePos(Type);

  Derivative = Error - LastError[Type + 3];
  LastError[Type + 3] = Error;

  return (Error * baseP[Type] + Derivative * baseD[Type]);
}


void TurnPos(int Goal){
  while((gyroAngle - LastTurnGoal) > (Goal + 3) 
  or (gyroAngle - LastTurnGoal) < (Goal - 3)){
    delay(20);
  }
  delay(100);
}

void Drive(double Goal){
  LastGoal = DrivingGoal;
  DrivingGoal += Goal;
}

void DrivePos(double Goal){
  while(((BasePos(right) + BasePos(left)) / 2 - LastGoal ) > (Goal + 1.5) 
  or ((BasePos(right) + BasePos(left)) / 2 - LastGoal ) < (Goal - 1.5)){
    delay(20);
  }
}

int AutoPID(){
  task FindDegrees(Angle);
  while(DrivPIDEnabled){
    Right.spin(forward, Check(BasePID(right, DrivingGoal)) - 
    TurnCheck(!VisionEnabled ? BasePID(turn, TurningGoal + visionAngle) : visionSpeed), percent);
 
    Left.spin(forward, Check(BasePID(left, DrivingGoal)) + 
    TurnCheck(!VisionEnabled ? BasePID(turn, TurningGoal + visionAngle): visionSpeed), percent);
  }
  return 0;
}

/*void Turn(int Goal){
  TurningK = 0.2;
  Turning = 1.9;
  LastTurnGoal = TurningGoal;
  TurningGoal += Goal * (Pi * Diameter) / 360 ;
}

void TurnPos(int Goal){
  Goal = Goal * (Pi * Diameter) / 360;
  while(((BasePos(left) - BasePos(right)) / 2 - LastTurnGoal) > (Goal + 1) 
  or ((BasePos(left) - BasePos(right)) / 2 - LastTurnGoal) < (Goal - 1)){
    delay(20);
  }
}

int AutoPID(){
  while(DrivPIDEnabled){
    differenceRightLeft = 0 (BasePos(right) + LastTurnGoal) < (DrivingGoal + 0.7) and
    (BasePos(right) + LastTurnGoal) > (DrivingGoal - 0.7) ? 0 :
    (TurningGoal - ((BasePos(left) - BasePos(right)) / 2)) / TurningK;
    FrontLeft.spin(forward, LiftPID(frontleft, FrontLiftGoal) / 1.5, percent);
    FrontRight.spin(forward, LiftPID(frontright, FrontLiftGoal) / 1.5, percent);
    BackLift.spin(forward, LiftPID(backlift, BackLiftGoal), percent);
    Right1.spin(forward, Check(BasePID(right, DrivingGoal - TurningGoal), right), percent);
    Right2.spin(forward, Check(BasePID(right, DrivingGoal - TurningGoal), right), percent);
    Left1.spin(forward, Check(BasePID(left, DrivingGoal + TurningGoal), left), percent);
    Left2.spin(forward, Check(BasePID(left, DrivingGoal + TurningGoal), left), percent);
  }
  return 0;
}//*/

#endif