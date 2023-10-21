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
  intake_piston.set(false);
  rightFlap.set(true);
  wait(0.1, seconds);
  rightFlap.set(false);
  drive(7, true);
  wait(0.4, seconds);
  drive_stop();
  wait(1, seconds);
  for(int i = 0; i<44; i++) {
    Cata.setVelocity(30, percent); 
    Cata.spinFor(forward, 75.0, degrees);
    wait(0.3, seconds);
    Cata.setVelocity(100, percent); 
    Cata.spinFor(forward, 105.0, degrees);
  }
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
/*                            Launch Side AWP                                */
/*---------------------------------------------------------------------------*/
void close_side(){
  //Drive in front of goal and score
  intake_piston.set(false);
  chassis.drive_distance(148);
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
  chassis.set_turn_exit_conditions(2.5, 300, 3000);
  //Back up, point towards the match load zone, and drive over there
  chassis.drive_distance(-40);
  chassis.turn_to_angle(210);
  chassis.drive_distance(132);
  chassis.turn_to_angle(145);
  intake_piston.set(true);
  rightFlap.set(true);
  intake_piston.set(false);
  /*RightFlap.set(true);
  Right1.spin(forward, 10, voltageUnits::volt);
  Right2.spin(forward, 10, voltageUnits::volt);
  Left1.spin(forward, 6, voltageUnits::volt);
  Left2.spin(forward, 6, voltageUnits::volt);
*/
  //chassis.turn_to_angle(215);
  //chassis.drive_distance(100);
}
/*---------------------------------------------------------------------------*/      
