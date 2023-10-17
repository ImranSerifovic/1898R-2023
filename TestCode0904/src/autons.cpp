#include "vex.h"

void default_constants(){
  
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
  //drive pid, this is good
  chassis.set_drive_constants(12, 0.5, 200, 3, 0);

  //turn pid constants, mostly done but not fully yet
  chassis.set_turn_constants(12, .08, .0052, 0, 15);
  
}
//Stops Drivetrain
void drive_stop() {
  Right1.stop();
  Right2.stop();
  Left1.stop();
  Left2.stop();

}

void skills(){
  while(true) {
    Cata.setVelocity(30, percent); 
    Cata.spinFor(forward, 75.0, degrees);
    // wait(0.1, seconds);
    Cata.setVelocity(100, percent); 
    Cata.spinFor(forward, 105.0, degrees);

  }
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

/*---------------------------------------------------------------------------*/
/*                            Launch Side AWP                                */
/*---------------------------------------------------------------------------*/
void drive_test(){
  chassis.turn_to_angle(90);
  chassis.drive_distance(5);
  //Drive in front of goal and score
  /*chassis.drive_distance(128);
  chassis.turn_to_angle(270);
  Intake.spin(reverse);
  wait(0.4, seconds);
  Intake.stop();
  Right1.spin(forward, 12, voltageUnits::volt);
  Right2.spin(forward, 12, voltageUnits::volt);
  Left1.spin(forward, 12, voltageUnits::volt);
  Left2.spin(forward, 12, voltageUnits::volt);
  wait(0.35, seconds);
  drive_stop();
  //Back up, point towards the match load zone, and drive over there
  Right1.spin(reverse, 6, voltageUnits::volt);
  Right2.spin(reverse, 6, voltageUnits::volt);
  Left1.spin(reverse, 6, voltageUnits::volt);
  Left2.spin(reverse, 6, voltageUnits::volt);
  wait(0.3, seconds);
  drive_stop();
  chassis.turn_to_angle(215);
  //chassis.drive_distance(100);
*/




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