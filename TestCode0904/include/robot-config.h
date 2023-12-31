using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Right1;
extern motor Right2;
extern motor Left1;
extern motor Left2;
extern controller Controller1;
extern motor Intake;
extern motor_group Cata;
extern digital_out leftFlap;
extern inertial Inertial5;
extern digital_out intake_piston;
extern digital_out hang;
extern digital_out rightFlap;
extern motor Blocker;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );