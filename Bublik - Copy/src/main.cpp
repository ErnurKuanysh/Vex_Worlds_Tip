#include "vex.h"
#include "OpControl.h"

using namespace vex;

competition Competition;

void pre_auton(void){
  vexcodeInit();
  Gyro.calibrate();         // For Stabilizing Gyroscope
  while(Gyro.isCalibrating()){
    delay(50);
  }
  Front(20);                // Calibration of the Lift 
}

void autonomous(void){
  Right1.setPosition(0,degrees); // Reset of the positions of the motors
  Right2.setPosition(0,degrees);
  Right3.setPosition(0,degrees);
  Left1.setPosition(0,degrees);
  Left2.setPosition(0,degrees);
  Left3.setPosition(0,degrees);
  task StartUp(Setup);      // From OpControl directory 
  task autoPID(AutoPID);    // From Funtions directory 
  DrivPIDEnabled = true;
  WPLine();                 // Auton selection 
  // NonWPLine();
  // WP();
  // Skills();
  // Beta();
  FrontLeft.set(false);     // For Piston activation 
}

void usercontrol(void){
  task StartUp(Setup);      // From OpControl directory
  while(true){
    DrivPIDEnabled = false; // To ensure that autonomous will not interfere with drive functions
    task Driving(Control);  // From OpControl directory 
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while(true){
    delay(20);
  }
}
