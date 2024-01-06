#include "main.h"

// MOTORS (PORT, GEAR COLOR, CLOCKWISE, Track Movement as counts, rotations, or degrees)

pros::Motor FR_Drive (11, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BR_Drive (14, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor TR_Drive (12, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor TL_Drive (7, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FL_Drive (8, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BL_Drive (9, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor intake (15, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::ADIMotor pushy_one ('A');

// CATAPULT STUFF
pros::Motor catapult (20, pros::E_MOTOR_GEAR_RED, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::ADIMotor limit_switch('B');


// CONTROLLER
pros::Controller con (pros::E_CONTROLLER_MASTER);

//MISC
pros::IMU gyro(16);
pros::ADIMotor wings ('C');