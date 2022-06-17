#include "vex.h"
#include "Odometry.h"
#include "OpControl.h"

using namespace vex;

competition Competition;

void pre_auton(void){
  vexcodeInit();
}

void autonomous(void){
  Right.setPosition(0,degrees);
  Left.setPosition(0,degrees);
  task autoPID(AutoPID);
  DrivPIDEnabled = true;
  // WPLine();
  // NonWPLine();
  // Skills();
  Beta();
}

void usercontrol(void){
  while(true){
    DrivPIDEnabled = false;
    task Driving(Control);
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
