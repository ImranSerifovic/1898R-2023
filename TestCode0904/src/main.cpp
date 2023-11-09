#include "vex.h"
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
// leftFlap             digital_out   C               
// Inertial5            inertial      5               
// intake_piston        digital_out   D               
// hang                 digital_out   H               
// rightFlap            digital_out   F               
// Blocker              motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                            Drive Stuff                                    */
/*---------------------------------------------------------------------------*/
Drive chassis(

ZERO_TRACKER_NO_ODOM,

//Left Motors:
motor_group(Left1, Left2),

//Right Motors:
motor_group(Right1, Right2),

//Port number of inertial sensor. Make sure to put PORT in front of the number
PORT5,

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

//put the positive distance from the center of the robot to the right side of the drive.
6.5,

1,

-2.75,

5.5

);
/*---------------------------------------------------------------------------*/
/*                           Variable Declarations                           */
/*---------------------------------------------------------------------------*/
int current_auton_selection = 0;                                             
bool auto_started = false;                                                   
int start_cata_rotation = 111; 
bool down = true;                                            
/*---------------------------------------------------------------------------*/
/*                            PRE-AUTON                                      */
/*---------------------------------------------------------------------------*/
//Period before match starts when bot is sitting on field
void pre_auton(void) {
  vexcodeInit();
  default_constants();
  intake_piston.set(true);
  while(auto_started == false){            
    switch(current_auton_selection){       
      case 0:
        Brain.Screen.printAt(50, 50, "Close Side AWP");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Far Side AWP");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Far Side Scoring");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Auton Skills");
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
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                               Auton Functions                             */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
  auto_started = true;
  // all autons start with pulling back the cata ready to fire
    intake_piston.set(false);

  /*TEmporary*/


  switch(current_auton_selection){  
    case 0:
      //far_side();
       close_side();
       //skills();
      break;        
 }
      
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Pneumatic Functions                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                              Intake Pneumatic                             */
/*---------------------------------------------------------------------------*/
int pressed2 = 0;
void PullBackFunc() {
  // starts in at beginning of game
  // to stay in size

  // flips whether we supply air to push out the intake 
  intake_piston.set(!intake_piston.value());
  Cata.spinFor(113, degrees);


}
/*---------------------------------------------------------------------------*/
/*                              Side Flaps                                   */
/*---------------------------------------------------------------------------*/


void Flaps() {
    // starts in at beginning of game
    // flips whether flaps are in or out
    leftFlap.set(!leftFlap.value());
    rightFlap.set(!rightFlap.value());
}
void Hang() {
  hang.set(!hang.value());
}
void cataDown() {

}
int counter = 0;
void cataShoulder() {

}
/*---------------------------------------------------------------------------*/
/*                              Blocker                                      */
/*---------------------------------------------------------------------------*/
int blockerCounter = 1;
void BlockerActivation() {
  blockerCounter++;

  if(blockerCounter % 2  == 0) {
    Blocker.spinFor(forward, 165, degrees);;
  }
  if(blockerCounter % 2  == 1) {
    Blocker.spinToPosition(0,degrees);
  }
  
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Driver Code                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void drive_pls(int volts, bool go_forward) {
  if(go_forward) {
    Right1.spin(forward, volts, voltageUnits::volt);
    Right2.spin(forward, volts, voltageUnits::volt);
    Left1.spin(forward, volts, voltageUnits::volt);
    Left2.spin(forward, volts, voltageUnits::volt);
  }
  else {
    Right1.spin(reverse, volts, voltageUnits::volt);
    Right2.spin(reverse, volts, voltageUnits::volt);
    Left1.spin(reverse, volts, voltageUnits::volt);
    Left2.spin(reverse, volts, voltageUnits::volt);
  }
}

void usercontrol(void) {
  leftFlap.set(false);  
  rightFlap.set(false);
  Blocker.setVelocity(100, percent);
  Blocker.setBrake(hold);
  Blocker.stop();
  intake_piston.set(false);
  if(!auto_started) {
    // for testing and driver skills 
    // (otherwise, this will happen in void autonomous)
    Cata.spinFor(start_cata_rotation, degrees);
  }

   //DRIVER SKILLS CODE!!!
  
  /*intake_piston.set(false);
  rightFlap.set(true);
  wait(0.1, seconds);
  rightFlap.set(false);
  drive_pls(7, true);
  wait(0.62, seconds);
  drive_stop();
  wait(1, seconds);
  for(int i = 0; i<44; i++) {
    Cata.setVelocity(40, percent); 
    Cata.spinFor(forward, 75.0, degrees);
    // wait(0.05, seconds);
    Cata.setVelocity(100, percent); 
    Cata.spinFor(forward, 105.0, degrees);
  }
  Cata.setVelocity(40, percent); 
  Cata.spinFor(forward, 75.0, degrees);
  Cata.setVelocity(100, percent); 
  Cata.spinFor(forward, 90.0, degrees);
  */

  while (1) {
    /*---------------------------------------------------------------------------*/
    /*                              Intake Code                                  */
    /*---------------------------------------------------------------------------*/
    if (Controller1.ButtonR1.pressing()) {
      Intake.spin(forward, 100,  voltageUnits::volt);
      
  
    } 
    else if (Controller1.ButtonR2.pressing()) {
       Intake.spin(reverse, 100,  voltageUnits::volt);
    } 
    else {
      Intake.stop();
    }

    
    /*---------------------------------------------------------------------------*/
    /*                         Binding Functions                                 */
    /*---------------------------------------------------------------------------*/
    //shoot cata
    if(Controller1.ButtonL1.pressing()) {
      // velocity @ 17% so the cata has time to shoot and recover from
      // slight recoil off the foam bracing before the slipgear reengages
      // which prevents the slipgear from changing its position relative to
      // the gear on the catapult axle
      // the cata starts down, spins until slip...
      Cata.setVelocity(17, percent); 
      Cata.spinFor(forward, 75.0, degrees);
      // and spins back so we can intake, all in ~0.8 seconds (slowed for matchloaders)!
      Cata.setVelocity(100, percent); 
      Cata.spinFor(forward, 105.0, degrees);
    }
    else if (Controller1.ButtonDown.pressing()) {
      // this button is the less common cata control
      if(!down) {
        // pulls cata from all the way up (post-shot) to halfway down,
        // or halfway down to all the way down (ready to intake)
        // halfway down is to prevent intaking all the way, allowing
        // us to move acorns by intaking and outtaking
        Cata.setVelocity(100, percent); 
        Cata.spinFor(forward, 52.5, degrees);
      }
      else {
        // velocity @ 30% so the cata has time to shoot and recover from
        // slight recoil off the foam bracing before the slipgear reengages
        // which prevents the slipgear from changing its position relative to
        // the gear on the catapult axle
        Cata.setVelocity(17, percent); 
        Cata.spinFor(forward, 75.0, degrees);
        Cata.setVelocity(100, percent);
        Cata.spinFor(forward, 52.5, degrees);
      }
      down = !down;
    } 
    
    Controller1.ButtonL2.pressed(Flaps);
    Controller1.ButtonLeft.pressed(Hang);
    Controller1.ButtonUp.pressed(PullBackFunc);
    Controller1.ButtonB.pressed(BlockerActivation);
    /*---------------------------------------------------------------------------*/
    
    //Driving method
    chassis.control_tank();

    wait(20, msec);
                    
  }
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                 MAIN                                      */
/*---------------------------------------------------------------------------*/
int main() {
  //set pneumatics to false
  leftFlap.set(false);
  rightFlap.set(false);
  hang.set(false);
  intake_piston.set(true);
  //set default catapult speed / braking
  Cata.setVelocity(100.0, percent);
  Cata.setStopping(hold);
  Intake.setVelocity(100, percentUnits::pct);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.

  wait(15, msec);
  pre_auton();
}
/*---------------------------------------------------------------------------*/
