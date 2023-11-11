#include "vex.h"
/*---------------------------------------------------------------------------*/
/*                              PID Constants                                */
/*---------------------------------------------------------------------------*/
void default_constants(){
  
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

  chassis.set_drive_constants(12, 0.5, 200, 3, 0);
  chassis.set_turn_constants(12, .075, .0057, 0.01, 15);
  
}
void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}
/*---------------------------------------------------------------------------*/
/*                              Defining Functions                           */
/*---------------------------------------------------------------------------*/
//Stops Drivetrain
void drive_stop() {
  Right1.stop();
  Right2.stop();
  Left1.stop();
  Left2.stop();

}
void drive(int volts, bool go_forward) {
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

void setVelocity(int percentage) {
    Right1.setVelocity(percentage, percent);
    Right2.setVelocity(percentage, percent);
    Left1.setVelocity(percentage, percent);
    Left2.setVelocity(percentage, percent);
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               Auton Routes                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                   Skills                                  */
/*---------------------------------------------------------------------------*/
void skills(){

  // Note: This section of code is in driver skills too...
  Cata.spinFor(111, degrees);
  // expand intake at beginning:
  intake_piston.set(false);
  // hit acorn onto close goal:
  rightFlap.set(true);
  wait(1, seconds);
  rightFlap.set(false);
  // drive to touch match load bar:
  drive(7, true);
  wait(0.45, seconds);
  drive_stop();

  wait(1, seconds);

  /*
  // shoot all 44 match loads:
  for(int i = 0; i<44; i++) {
    // velocity @ 17% so the cata has time to shoot and recover from
    // slight recoil off the foam bracing before the slipgear reengages
    // which prevents the slipgear from changing its position relative to
    // the gear on the catapult axle
    // the cata starts down, spins until slip...
    Cata.setVelocity(17, percent); 
    Cata.spinFor(forward, 75.0, degrees);
    // and spins back so we can intake, all in ~0.9 seconds (slowed down extra for matchloaders)!
    Cata.setVelocity(100, percent); 
    Cata.spinFor(forward, 105.0, degrees);
  }

  //Cata.setVelocity(25, percent); 
  //Cata.spinFor(forward, 75.0, degrees);
  Cata.setVelocity(100, percent); 
  // (pull down cata again so we can drive under elevation bar:)
  Cata.spinFor(forward, 90.0, degrees);
  //...here is when driver skills automated tasks end
  */


  // score our two preloads:
  chassis.drive_distance(-20, -125);
  chassis.drive_distance(-60);
  setVelocity(100);
  drive(12, false);
  wait(0.8, seconds);
  drive_stop();

  // Drive to other side of field:
  chassis.drive_distance(67, 180);
  chassis.drive_distance(210, 188);
  chassis.drive_distance(55, 172);
  // drive so we face goal, to effectively push in acorns:
  chassis.drive_distance(20, 60);
  chassis.drive_distance(80);
  chassis.drive_distance(50, 170);
   chassis.set_drive_exit_conditions(5, 600, 5000);
   chassis.set_turn_exit_conditions(5, 600, 5000);
  // push:
  leftFlap.set(true);
  rightFlap.set(true);
  drive(12, true);
  wait(1.5, seconds);
  drive_stop();
  // push again further along the goal:

  chassis.drive_distance(-80);
  chassis.turn_to_angle(1);
  chassis.drive_distance(40, 1);
  drive(12, true);
}
/*---------------------------------------------------------------------------*/
/*                            Close Side AWP                                 */
/*---------------------------------------------------------------------------*/
void close_side(){
  //Drive in front of goal and score...

  // expand intake:
  intake_piston.set(false);

  wait(0.5, seconds);
  // pull down cata:
  Cata.spinFor(111, degrees);

  chassis.drive_distance(136);
  chassis.turn_to_angle(270);
  Intake.spin(reverse);
  wait(0.4, seconds);
  Intake.stop();  
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);
  Left1.spin(forward, 12, voltageUnits::volt);
  Left2.spin(forward, 12, voltageUnits::volt);
  wait(0.4, seconds);
  drive_stop();
  // acorn preload scored!

  chassis.set_turn_exit_conditions(2.5, 300, 800);
  
  //Back up, point towards the match load zone, and drive over there
  chassis.drive_distance(-62);
  chassis.turn_to_angle(214);
  chassis.drive_distance(131);
  drive(12, true);
  wait(0.1, seconds);
  drive_stop();

  //Descore match load acorn with our flap:
  rightFlap.set(true);            
  chassis.turn_to_angle(142);
  // slight left turn, engage right side only, slightly under max voltage for best results:
  Right1.spin(forward, 11, voltageUnits::volt);
  Right2.spin(forward, 11, voltageUnits::volt);                                                                                            
  wait(0.3, seconds);
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);   
  Right1.stop();
  Right2.stop();
  rightFlap.set(false);
  wait(0.1, seconds);
  // touch elevation bar with flap:
  chassis.turn_to_angle(98);
  chassis.drive_distance(102);
  leftFlap.set(true);
}
/*---------------------------------------------------------------------------*/
/*                            Far Side                                       */
/*---------------------------------------------------------------------------*/

void far_side() {
  // expand intake at beginning:
  intake_piston.set(false);
  wait(0.5, seconds);
  // pull cata halfway down (so we can intake and outtake acorns without them getting in cata):
  Cata.spinFor(70, degrees);
  // drive to net and score preload:
  chassis.drive_distance(132);
  chassis.set_turn_exit_conditions(4, 300, 3000);
  chassis.turn_to_angle(90);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  Intake.spin(reverse);
  wait(0.4, seconds);
  Intake.stop();
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);
  Left1.spin(forward, 12, voltageUnits::volt);
  Left2.spin(forward, 12, voltageUnits::volt);
  wait(0.4, seconds);
  drive_stop();
  //scored!

  chassis.set_turn_exit_conditions(2.5, 300, 800);
  
  // pick up acorn by barrier bar:
  chassis.drive_distance(-62);
  chassis.turn_to_angle(228);
  // intake acorn:
  Intake.spin(forward);
  chassis.drive_distance(22);
  wait(0.1, seconds);
  Intake.stop();
  // get other acorns nearby:
  chassis.turn_to_angle(80);
  chassis.drive_distance(30,90);
  // outtake acorn:
  Intake.spin(reverse);
  wait(0.6, seconds);
  Intake.stop();
  //get closer intake
  chassis.turn_to_angle(0);
  Intake.spin(forward);
  chassis.drive_distance(20);
  wait(0.3, seconds);
  Intake.stop();
  chassis.turn_to_angle(90);
  Intake.spin(reverse);
  wait(0.3, seconds);
  Intake.stop();
  rightFlap.set(true);
  leftFlap.set(true);
  intake_piston.set(false);
  drive(12,true);
  Cata.spinFor(43, degrees);
  //back up and point at the other
  /*chassis.turn_to_angle(95);
  chassis.turn_to_angle(270);
  chassis.drive_distance(20,-50);
  Intake.spin(forward);
  chassis.drive_distance(15,-54);
  wait(0.2,seconds);
  Intake.stop(); */
  //rotate towards goal to score both
  /*
  Right1.spin(forward, -9, voltageUnits::volt);
  Right2.spin(forward, -9, voltageUnits::volt); 
  Left1.spin(forward, 7, voltageUnits::volt);
  Left2.spin(forward, 7, voltageUnits::volt); 
  wait(0.49, seconds);
  drive_stop();
  */


  /*rightFlap.set(true);
  leftFlap.set(true);
  drive(12, true);
  wait(0.6, seconds);
  */


  //score second
  /*wait(0.2, seconds);
  drive(10,true);
  wait(0.3,seconds);
  drive_stop();
  chassis.drive_distance()
  */
  
// TODO: shorten auton to fit in more acorn scoring (may or may not be possible with our 
// bot, but we have time to try :) )
  /*drive(12, true);
  wait(0.4, seconds);
  Intake.spin(reverse);
  wait(0.4, seconds);
  Intake.stop();
  drive_stop();
  chassis.drive_distance(-15);
  */


  //Cata.spinFor(50, degrees);
}

/*---------------------------------------------------------------------------*/      
