#pragma once 
// Try to understand 
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vex.h"

#define frontright 2
#define right 0
#define left 1
#define side 3
#define turn 2
#define front 0
#define back 2

#define BackClaw 2

#define defaultSpeed 100

#define Pi 3.1415926535

double Diameter = 13.3;

double MaxSpeed = defaultSpeed;

#define AngleError 1

double liftP = 0.63;
double liftD = 1;

double ClawP = 18;
double ClawD = 60;
bool ClawState[] = {false, true, true}; 

double MaxTurnSpeed = 100;
#define BP 6
#define BD -3
#define TP 0.72
#define TD 10
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

bool start = 0;

double Abs(double Value){
  return Value < 0 ? -Value : Value;
}

// double Pos(int Type){
//   return Type == 2 ? GPS.yPosition() : Type == 1 ? GPS.xPosition() : GPS.rotation();
// }

// double GpsTurnGoal, DriveGoal, Y, X, deltaX, deltaY;

// int GPSPos(){
//   while(true){
//     deltaX = Pos(1) - X;
//     deltaY = Pos(2) - Y;
//     if(deltaY == 0){
//       GpsTurnGoal = deltaX > 0 ? 270 : 90;
//     }else if(deltaY<0){
//       if(deltaX<0){
//         GpsTurnGoal = (atan(deltaX/deltaY) / 3.1415926535) * 180;
//       }else{
//         GpsTurnGoal = (atan(deltaX/deltaY) / 3.1415926535) * 180 + 360;
//       }
//     }else{
//       GpsTurnGoal = (atan(deltaX/deltaY) / 3.1415926535) * 180 + 180;
//     }
//     // DriveGoal = sqrt(Abs(deltaX) * Abs(deltaX) + Abs(deltaY) * Abs(deltaY));
//   }
// }
// int Angle(){
//   while(true){
//     if(GpsTurnGoal / AngleError < 90){
//       turningRight = true;
//     }else if(GpsTurnGoal / AngleError > 270){
//       turningRight = false;
//     }
//     if(fabs(gyroLastAngle - GpsTurnGoal / AngleError) > 300){
//       if(turningRight){
//         rotations ++;
//       }else{
//         rotations --;
//       }
//     }
    
//     gyroLastAngle = GpsTurnGoal / AngleError;
//     gyroAngle = GpsTurnGoal / AngleError + (rotations * 360) - 180;
//     delay(10);
//   }
//   return 0;
// }

double TurnCheck(double Speed){
  return Speed > MaxTurnSpeed ? MaxTurnSpeed : Speed < - MaxTurnSpeed ? - MaxTurnSpeed : Speed;
}

double Check(double Speed){
  return Speed > MaxSpeed ? MaxSpeed : Speed < -MaxSpeed ? - MaxSpeed : Speed;
}

double LiftPos(){
  return FrontLift.position(degrees);
}

void Front(int Goal){
  FrontLiftGoal = Goal;
}

// void Back(int Goal){
//   BackLiftGoal = Goal;
// }

double LiftPID(double Goal){

  Error = Goal - LiftPos();

  Derivative = Error - LastError[2];
  LastError[2] = Error;

  return (Goal < 50 and LiftPos() < 50) ? 0 : ((Error * liftP) + (Derivative * liftD));
}


double BasePos(int Type){
  return Type == right? ((Right1.position(degrees) + Left1.position(degrees) + Right2.position(degrees) +
  Left2.position(degrees) + Right3.position(degrees) + Left3.position(degrees)) / 6) * (Diameter / 360)
  : Type == turn ? Gyro.rotation() :
  /*EncoderSide.position(degrees) * (8.66 / 360)*/ 0;
  
}

double BasePID(int Type, double Goal){  

  Error = Goal - BasePos(Type);

  Derivative = Error - LastError[Type + 3];
  LastError[Type + 3] = Error;
  
  return (Error * baseP[Type] + Derivative * baseD[Type]);
}

// double ClawPID(double Goal){  

//   Error = Goal - Am.angle();

//   Derivative = Error - LastError[6];
//   LastError[6] = Error;

//   return Am.angle() != 0 ? (Error * ClawP + Derivative * ClawD) : 0;
// }

// bool BaseSpeed(){
//   return fabs(Right1.velocity(percent) + Right2.velocity(percent) + 
//   Left1.velocity(percent) + Left2.velocity(percent)) < 1 ? true : false;
// }

void Turn(int Goal){
  LastTurnGoal = TurningGoal;
  TurningGoal += Goal;
}

void TurnPos(int Goal){
  while((Gyro.rotation() - LastTurnGoal) > (Goal + 1.5) 
  or (Gyro.rotation() - LastTurnGoal) < (Goal - 1.5)){
    delay(20);
  }
  delay(200);
}

void TurnPos(int Goal, int Error){
  while((Gyro.rotation() - LastTurnGoal) > (Goal + 1 + Error) 
  or (Gyro.rotation() - LastTurnGoal) < (Goal - 1 - Error)){
    delay(20);
  }
  delay(200);
}

void Drive(int Goal){
  LastGoal = DrivingGoal;
  DrivingGoal += Goal;
}

void DrivePos(int Goal){
  while(((BasePos(right))  - LastGoal ) > (Goal + 1.5) 
  or ((BasePos(right)) - LastGoal ) < (Goal - 1.5)){
    delay(20);
  }
}

void DrivePos(int Goal, int Error){
  while(((BasePos(right)) - LastGoal ) > (Goal + 1.5 + Error) 
  or ((BasePos(right)) - LastGoal ) < (Goal - 1.5 - Error)){
    delay(20);
  }
}

void Claw(bool Type, bool State){
  ClawState[Type] = State;
}

bool Parking = false;
int ParkingSpeed = 0;

void DriveUp(){
  Parking = true;
  while(Gyro.roll() > -16){
    ParkingSpeed = 50;
  }
}

void Park(){
  delay(1300);
  ParkingSpeed = 20;
  while(Gyro.roll() < -16){
    ParkingSpeed = 50;
  }
  ParkingSpeed = -50;
  delay(1000);
  ParkingSpeed = 0;
}

bool presMogo = false;
int counter = 0;
int Staying = 0;

int IntakeSpeed(){
  if(BublikIntake.velocity(percent) < 5 and BublikIntake.velocity(percent) > -5) Staying ++;
  else Staying = 0;
  if(Staying == 20) counter = 150;
  counter --;
  return counter>0 ? -50 : 100; 
}

int IntakeState=0;

void Intake(int Speed){
  IntakeState = Speed;
}

int IntakeAuton(){
  while(true){
    // BublikIntake.spin(forward, IntakeState, percent);
  }
}

double Forward = 0;
double Right = 0;
int AutoPID(){
  while(true){
    if(DrivPIDEnabled){
      if(start){
        FrontLift.spin(forward, LiftPID(FrontLiftGoal), percent);
      }

      Forward = Check(BasePID(right, DrivingGoal));
      Right = TurnCheck(BasePID(turn, TurningGoal));
      
      Right1.spin(forward, Parking ? ParkingSpeed : Forward - Right, percent);

      Right2.spin(forward, Parking ? ParkingSpeed : Forward - Right, percent);

      Right3.spin(forward, Parking ? ParkingSpeed : Forward - Right, percent);
  
      Left1.spin(forward, Parking ? ParkingSpeed : Forward + Right, percent);

      Left2.spin(forward, Parking ? ParkingSpeed : Forward + Right, percent);
      
      Left3.spin(forward, Parking ? ParkingSpeed : Forward + Right, percent);  
    }else{
      delay(300);
    }
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