#include "vex.h"
//Devan was here
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Right1               motor         9               
// Right2               motor         10              
// Left1                motor         2               
// Left2                motor         3               
// Controller1          controller                    
// Intake               motor         4               
// Cata                 motor_group   1, 21           
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;




Drive chassis(

ZERO_TRACKER_NO_ODOM,

//Left Motors:
motor_group(Left1, Left2),

//Right Motors:
motor_group(Right1, Right2),

//Port number of inertial sensor. Make sure to put PORT in front of the number
PORT21,

//Wheel diameter
3.25,

//External ratio,input teeth/output teeth.
1.6,

//Useless stuff for tracking past here

360,

//ignore
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

3,

2.75,
/*---------------------------------------------------------------------------*/
/*                    Remeasure this!!!!   - IMMY                            */
/*---------------------------------------------------------------------------*/
//put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
6.5,
///this the value ^
1,

-2.75,

5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  vexcodeInit();
  default_constants();

  //set default speeds
  Cata.setVelocity(100.0, percent);
  Cata.setStopping(brake);
  
  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(50, 50, "Drive Test");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Drive Test");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Turn Test");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Swing Test");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "Full Test");
        break;
      case 5:
        Brain.Screen.printAt(50, 50, "Odom Test");
        break;
      case 6:
        Brain.Screen.printAt(50, 50, "Tank Odom Test");
        break;
      case 7:
        Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
      drive_test(); 
      break;        
    case 1:         
      drive_test();
      break;
    case 2:
      turn_test();
      break;
    case 3:
      swing_test();
      break;
    case 4:
      full_test();
      break;
    case 5:
      odom_test();
      break;
    case 6:
      tank_odom_test();
      break;
    case 7:
      holonomic_odom_test();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
//Driver period code
void usercontrol(void) {
  Intake.setVelocity(100, percentUnits::pct);

  while (1) {

    
    
    // intake code
    if (Controller1.ButtonR1.pressing()) {
      Intake.spin(forward, 100,  voltageUnits::volt);
    } 
    else if (Controller1.ButtonR2.pressing()) {
       Intake.spin(reverse, 100,  voltageUnits::volt);
    } 
    else {
      Intake.stop();
    }

    // cata code
    if (Controller1.ButtonL1.pressing()) {
      Cata.spinFor(forward, 180.0, degrees, true);
    } 
    
    chassis.control_tank();


    wait(20, msec);
                    
  }
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.

  wait(15, msec);
  pre_auton();

  while (true) {
    wait(100, msec);
  }

}
/*---------------------------------------------------------------------------*/
