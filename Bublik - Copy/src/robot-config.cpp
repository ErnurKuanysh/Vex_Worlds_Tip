#include "vex.h"

using namespace vex;


brain Brain;

controller Controller1 = controller(primary);

motor Left1 = motor(PORT17, ratio18_1, true);
motor Left2 = motor(PORT19, ratio18_1, false);
motor Left3 = motor(PORT20, ratio18_1, true);
motor Right1 = motor(PORT7, ratio18_1, true);
motor Right2 = motor(PORT8, ratio18_1, false);
motor Right3 = motor(PORT9, ratio18_1, false);

// motor BackLift = motor(PORT10, ratio18_1, true);

motor FrontLift = motor(PORT16, ratio18_1, false);

motor BublikIntake = motor(PORT6, ratio18_1, false);

// gps GPS = gps(PORT10, 0, 0.00, mm, -0);

inertial Gyro = inertial(PORT10);

pot Am = pot(Brain.ThreeWirePort.H);

digital_out Back = digital_out(Brain.ThreeWirePort.B);
digital_out FrontRight = digital_out(Brain.ThreeWirePort.A);
digital_out FrontLeft = digital_out(Brain.ThreeWirePort.H);



bool RemoteControlCodeEnabled = true;



void vexcodeInit(void) {

}