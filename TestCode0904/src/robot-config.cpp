#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Right1 = motor(PORT9, ratio6_1, false);
motor Right2 = motor(PORT10, ratio6_1, false);
motor Left1 = motor(PORT2, ratio6_1, true);
motor Left2 = motor(PORT3, ratio6_1, true);
controller Controller1 = controller(primary);
motor Intake = motor(PORT4, ratio6_1, true);
motor CataMotorA = motor(PORT1, ratio36_1, true);
motor CataMotorB = motor(PORT21, ratio36_1, false);
motor_group Cata = motor_group(CataMotorA, CataMotorB);

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