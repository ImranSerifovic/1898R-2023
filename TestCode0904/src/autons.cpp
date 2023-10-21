#include "vex.h"

void default_constants(){
  
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

  chassis.set_drive_constants(12, 0.5, 200, 3, 0);
  chassis.set_turn_constants(12, .08, .0052, 0, 15);
  
}
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

void skills(){
  rightFlap.set(true);
  wait(0.1, seconds);
  rightFlap.set(false);
  drive(7, true);
  wait(0.4, seconds);
  drive_stop();
  wait(1, seconds);
  for(int i = 0; i<3; i++) {
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

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

/*---------------------------------------------------------------------------*/
/*                            Launch Side AWP                                */
/*---------------------------------------------------------------------------*/
void close_side(){
  //Drive in front of goal and score
  chassis.drive_distance(148);
  chassis.turn_to_angle(270);
  Intake.spin(reverse);
  wait(0.4, seconds);
  Intake.stop();
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);
  Left1.spin(forward, 12, voltageUnits::volt);
  Left2.spin(forward, 12, voltageUnits::volt);
  wait(0.3, seconds);
  drive_stop();
  //Back up, point towards the match load zone, and drive over there
  Right1.spin(reverse, 6, voltageUnits::volt);
  Right2.spin(reverse, 6, voltageUnits::volt);
  Left1.spin(reverse, 6, voltageUnits::volt);
  Left2.spin(reverse, 6, voltageUnits::volt);
  wait(0.3, seconds);
  drive_stop();
  chassis.drive_distance(-18);
  chassis.turn_to_angle(214);
  chassis.drive_distance(128);
  chassis.turn_to_angle(145);
  rightFlap.set(true);
  leftFlap.set(true);
  Right1.spin(forward, 10, voltageUnits::volt);
  Right2.spin(forward, 10, voltageUnits::volt);
  Left1.spin(forward, 6, voltageUnits::volt);
  Left2.spin(forward, 6, voltageUnits::volt);

  //chassis.turn_to_angle(215);
  //chassis.drive_distance(100);






}
/*---------------------------------------------------------------------------*/      
void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}