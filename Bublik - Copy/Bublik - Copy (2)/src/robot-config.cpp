#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller1 = controller(primary);

motor Left = motor(PORT14, ratio18_1, false);
motor Right = motor(PORT13, ratio18_1, true);

motor Lift = motor(PORT11, ratio18_1, false);

signature Vision__ORANGE_CUBE = signature (1, 8047, 8475, 8260, -3107, -2817, -2962, 4.5, 0);
signature Vision__PURPLE_CUBE = signature (1, 201, 655, 428, 7847, 8247, 8046, 11, 0);
signature Vision__GREEN_CUBE = signature (2, -7545, -6807, -7176, -4509, -3639, -4074, 5.7, 0);
vision Vision = vision (PORT1, 55, Vision__PURPLE_CUBE, Vision__ORANGE_CUBE, Vision__GREEN_CUBE);

bool RemoteControlCodeEnabled = true;



void vexcodeInit(void) {

}