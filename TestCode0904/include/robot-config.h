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
extern digital_out LeftFlap;
extern digital_out RightFlap;
extern digital_out PullBack;
extern inertial Inertial5;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );