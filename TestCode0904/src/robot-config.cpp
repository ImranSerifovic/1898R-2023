#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Intake = motor(PORT11, ratio6_1, true);
motor Right1 = motor(PORT1, ratio6_1, false);
motor Right2 = motor(PORT2, ratio6_1, false);
motor Left1 = motor(PORT12, ratio6_1, false);
motor Left2 = motor(PORT13, ratio6_1, false);
inertial Inertial21 = inertial(PORT21);
controller Controller1 = controller(primary);
motor Cata = motor(PORT3, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}