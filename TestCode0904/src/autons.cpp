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
  Cata.spinFor(111, degrees);
  intake_piston.set(false);
  rightFlap.set(true);
  wait(1, seconds);
  rightFlap.set(false);
  drive(7, true);
  wait(0.4, seconds);
  drive_stop();
  wait(1, seconds);
  for(int i = 0; i<2; i++) {
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
  Cata.setVelocity(25, percent); 
  Cata.spinFor(forward, 75.0, degrees);
    // wait(0.05, seconds);
  Cata.setVelocity(100, percent); 
  Cata.spinFor(forward, 90.0, degrees);
  chassis.drive_distance(-20, -125);
  chassis.drive_distance(-60);
  setVelocity(100);
  drive(12, false);
  wait(0.8, seconds);
  drive_stop();
  chassis.drive_distance(67, 180);
  chassis.drive_distance(210, 188);
  chassis.drive_distance(55, 172);
  chassis.drive_distance(20, 60);
  chassis.drive_distance(80);
  chassis.drive_distance(50, 170);
  leftFlap.set(true);
  rightFlap.set(true);
  drive(12, true);
  wait(1.5, seconds);
  drive_stop();
  chassis.drive_distance(-80);
  chassis.turn_to_angle(150);
  chassis.drive_distance(40, 180);
  drive(12, true);
  // chassis.drive_distance(200);fl
  // chassis.turn_to_angle(-75);
  // chassis.drive_distance(40);
  // flaps.set(true);
  // chassis.drive_distance(180, 15);
  
}
/*---------------------------------------------------------------------------*/
/*                            Close Side AWP                                 */
/*---------------------------------------------------------------------------*/
void close_side(){
  //Drive in front of goal and score
  intake_piston.set(false);
  wait(0.5, seconds);
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
  chassis.set_turn_exit_conditions(2.5, 300, 800);
  //Back up, point towards the match load zone, and drive over there
  chassis.drive_distance(-62);
  chassis.turn_to_angle(214);
  chassis.drive_distance(131);
  drive(12, true);
  wait(0.1, seconds);
  drive_stop();
  rightFlap.set(true);            
  chassis.turn_to_angle(142);
  // intake_piston.set(true);
  rightFlap.set(true);            
  Right1.spin(forward, 11, voltageUnits::volt);
  Right2.spin(forward, 11, voltageUnits::volt);                                                                                            
  wait(0.3, seconds);
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);   
  Right1.stop();
  Right2.stop();
  rightFlap.set(false);
  // intake_piston.set(false);
  /*RightFlap.set(true);

  Left1.spin(forward, 6, voltageUnits::volt);
  Left2.spin(forward, 6, voltageUnits::volt);
*/
  wait(0.1, seconds);
  chassis.turn_to_angle(98);
  chassis.drive_distance(102);
  leftFlap.set(true);
}
/*---------------------------------------------------------------------------*/
/*                            Far Side AWP                                   */
/*---------------------------------------------------------------------------*/

void far_side() {
  intake_piston.set(false);
  wait(0.5, seconds);
  Cata.spinFor(61, degrees);
  chassis.drive_distance(132);
  chassis.turn_to_angle(90);
  Intake.spin(reverse);
  wait(0.4, seconds);
  Intake.stop();
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);
  Left1.spin(forward, 12, voltageUnits::volt);
  Left2.spin(forward, 12, voltageUnits::volt);
  wait(0.4, seconds);
  drive_stop();
  chassis.set_turn_exit_conditions(2.5, 300, 800);
  //Back up, point towards the match load zone, and drive over there
  chassis.drive_distance(-62);
  chassis.turn_to_angle(233);
  Intake.spin(forward);
  chassis.drive_distance(22);
  wait(0.1, seconds);
  Intake.stop();
  chassis.turn_to_angle(80);
  chassis.drive_distance(40,90);
  Intake.spin(reverse);
  drive(12,true);
  wait(0.3,seconds);
  drive_stop();
  chassis.turn_to_angle(225);
  chassis.drive_distance(50);

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
