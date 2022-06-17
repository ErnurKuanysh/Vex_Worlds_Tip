#pragma once 

#ifndef AUTOS_H
#define AUTOS_H 

#include "vex.h"
#include "Functions.h"

void First(){
  Green();
  Claw(true);
  delay(100);
  Drive(33);
  DrivePos(33);
  Drive(-6);
  DrivePos(-6);
  Claw(false);
}

void Second(){
  Drive(43);
  DrivePos(43);
  Green();
  Claw(true);
  Drive(20);
  DrivePos(20);
  Claw(false);
  delay(700);
  Drive(-75);
  DrivePos(-63);
  Claw(true);
  DrivePos(-75);
  // Turn(-135);
  // TurnPos(-135);
  // Claw(true);
  // Drive(-10);
  // DrivePos(-10);
  // Claw(false);
  // Drive(10);
  // DrivePos(8);
  // Drive(-5);
  // DrivePos(-5);
}

void Third(){
  Drive(20);
  DrivePos(20);
  Green();
  Claw(true);
  Drive(10);
  DrivePos(10);
  Claw(false);
  delay(700);
  Drive(-40);
  DrivePos(-30);
  Claw(true);
  DrivePos(-40);
  delay(1000);
  Claw(false);
  Drive(42);
  DrivePos(42);
  Orange();
  Claw(true);
  Drive(10);
  DrivePos(10);
  Claw(false);
  delay(700);
  Drive(-52);
  DrivePos(-42);
  Claw(true);
  DrivePos(-52);
  Claw(false);
  // Turn(-135);
  // TurnPos(-135);
  // Claw(true);
  // Drive(-10);
  // DrivePos(-10);
  // Claw(false);
  // Drive(10);
  // DrivePos(8);
  // Drive(-5);
  // DrivePos(-5);
}

void Fourth(){
  Drive(45);
  DrivePos(45);
  Turn(90);
  TurnPos(90);
  Drive(20);
  DrivePos(20);
  Turn(90);
  TurnPos(90);
  Purple();
  Claw(true);
  Drive(20);
  DrivePos(20);
  Claw(false);
  delay(700);
  Drive(-45);
  DrivePos(-45);
  Turn(90);
  TurnPos(90);
  Drive(36);
  DrivePos(30);
  Claw(true);
  DrivePos(36);
  Drive(-10);
  DrivePos(-10);
}

void ful(){
  while(true){
    First();
    while(!Controller1.ButtonA.pressing() or !Controller1.ButtonLeft.pressing()){
      delay(50);
    }
    if(Controller1.ButtonA.pressing()){
      break;
    }
  }
  while(true){
    Second();
    while(!Controller1.ButtonA.pressing() or !Controller1.ButtonLeft.pressing()){
      delay(50);
    }
    if(Controller1.ButtonA.pressing()){
      break;
    }
  }
  while(true){
    Third();
    while(!Controller1.ButtonA.pressing() or !Controller1.ButtonLeft.pressing()){
      delay(50);
    }
    if(Controller1.ButtonA.pressing()){
      break;
    }
  }
  while(true){
    Fourth();
    while(!Controller1.ButtonA.pressing() or !Controller1.ButtonLeft.pressing()){
      delay(50);
    }
    if(Controller1.ButtonA.pressing()){
      break;
    }
  }
  
}


#endif 