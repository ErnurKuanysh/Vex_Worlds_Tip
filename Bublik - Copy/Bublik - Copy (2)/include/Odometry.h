#pragma once
#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "vex.h"


using namespace vex;

#define right 0
#define left 1
#define side 2
#define Pi 3.1415926535


#define Right_Side 5.125
#define Left_Side 5.125
#define Back_Side 5

// lcd::initialize();
int Printable = 0;
double Right_value;
double Left_value;
double Back_value;
double delta_Right_value;
double delta_Left_value;
double delta_Back_value;
double pre_Right_value = 0;
double pre_Left_value = 0;
double pre_Back_value = 0;
double Reset_Right_value = 0;
double Reset_Left_value = 0;
double Tetta;
double delta_Tetta;
double pre_Tetta = 0;
double Y_Local;
double X_Local;
double R_Polar;
double Tetta_Polar;
double delta_X = 0;
double delta_Y = 0;
double X0 = 0;
double Y0 = 0;
double X;
double Y;


double Pos(int Type){
  return Type == right? Right.position(degrees) * (12.56 / 360) : Type == left ? 
  Left.position(degrees) * (12.56 / 360) : /*EncoderSide.position(degrees) * (8.66 / 360)*/ 0 ;
}

int Odom(){
  while(true){

    // Collecting Data
    Right_value = Pos(right);
    Left_value = Pos(left);
    Back_value = Pos(side);
    delta_Right_value = Right_value - pre_Right_value;
    delta_Left_value = Left_value - pre_Left_value;
    delta_Back_value = Back_value - pre_Back_value;
    pre_Right_value = Right_value;
    pre_Left_value = Left_value;
    pre_Back_value = Back_value;

    // Countings
    Tetta = (Right_value - Left_value) / (Left_Side + Right_Side);
    delta_Tetta = Tetta - pre_Tetta;
    pre_Tetta = Tetta;

    // Local Cordinate System
    if(delta_Tetta == 0){
      X_Local = delta_Back_value;
      Y_Local = delta_Right_value;
    }else{
      Y_Local = 2 * sin(delta_Tetta / 2) * (delta_Right_value / delta_Tetta + Right_Side);
      X_Local = 2 * sin(delta_Tetta / 2) * (delta_Back_value / delta_Tetta + Back_Side);
    }
    //Polar Cordinate System
    R_Polar = sqrt(X_Local * X_Local + Y_Local * Y_Local); 
    Tetta_Polar = atan(Y_Local / X_Local) + X_Local < 0 ? 180 : Y_Local < 0 ? 360 : 0;
    Tetta_Polar -= pre_Tetta + delta_Tetta / 2;

    //Cartesian Cordinate System
    delta_X = R_Polar * cos(Tetta_Polar);
    delta_Y = R_Polar * sin(Tetta_Polar);

    //Final update 
    X = X0 + delta_X;
    Y = Y0 + delta_Y;
    X0 = X;
    Y0 = Y;

    // Printing Data
    if(!(Printable % 10)){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(3, 3);
      Brain.Screen.print(X);
      Brain.Screen.setCursor(4, 3);
      Brain.Screen.print(Y);
    }
    Printable++;
    delay(10);
  }
}


#endif 