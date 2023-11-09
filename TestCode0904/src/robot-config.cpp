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
motor CataMotorA = motor(PORT1, ratio36_1, false);
motor CataMotorB = motor(PORT21, ratio36_1, true);
motor_group Cata = motor_group(CataMotorA, CataMotorB);
digital_out leftFlap = digital_out(Brain.ThreeWirePort.C);
inertial Inertial5 = inertial(PORT5);
digital_out intake_piston = digital_out(Brain.ThreeWirePort.D);
digital_out hang = digital_out(Brain.ThreeWirePort.H);
digital_out rightFlap = digital_out(Brain.ThreeWirePort.F);
motor Blocker = motor(PORT11, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonX/ButtonB status to control Cata
      if (Controller1.ButtonX.pressing()) {
        Cata.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        Cata.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        Cata.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}