#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		autonomous();
	} else {
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	FR_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BR_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	TR_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	FL_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BL_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	TL_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	gyro.reset();
	con.clear();
	pros::Task controller(controllerScreen, "print");
	pros::delay(200);
	
}

void controllerScreen()
{
	con.print(0,0, "%f", gyro.get_heading());
	pros::delay(50);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void auton(){

}
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	// //SKILLS AUTON
	
	// // // //Match Load
	// catapult.move_velocity(127);
	// pros::delay(30500);
	// catapult.move_velocity(0);

	// // //Cross To Other Side
	// pushy_one.set_value(127);
	// rotateToAngle(45, false);
	// pros::delay(100);
	// driveStraight(98, false);
	// pros::delay(100);

	// // // PUSH on Red Goal One
	// wings.set_value(127);
	// rotateToAngle(20, false);
	// pros::delay(100);
	// driveStraight(72, false);
	// pros::delay(100);
	// driveStraight(12, true);
	// pros::delay(100);
	// driveStraight(13, false);
	// wings.set_value(0);
	// pros::delay(100);

	// driveStraight(24, true);
	// pros::delay(100);
	// rotateToAngle(340, false);
	// pros::delay(100);
	// driveStraight(90, false);
	// pros::delay(100);
	// rotateToAngle(85, false);
	// wings.set_value(127);
	// pros::delay(100);
	// driveStraight(50, false);
	// pros::delay(100);
	// driveStraight(12, true);
	// pros::delay(50);
	// driveStraight(13, false);
	// pros::delay(50);

	//Red Offense
	driveStraight(51, false);
	pros::delay(100);
	rotateToAngle(90,false);
	pros::delay(100);
	intake.move_velocity(600);
	pros::delay(500);
	intake.move_velocity(0);
	setDriveMotors(20,20);
	pros::delay(4000);
	stop();

	//Red Defense
	// driveStraight(51, false);
	// pros::delay(100);
	// rotateToAngle(240,false);
	// pros::delay(100);
	// intake.move_velocity(600);
	// pros::delay(1000);
	// intake.move_velocity(0);
	// setDriveMotors(20,20);
	// pros::delay(4000);
	// stop();
	

	//SKILLS
	// setDriveMotors(40,40);
	// pros::delay(2000);
	// setDriveMotors(80,-80);
	// pros::delay(1000);
	// stop();
	// while(true)
	// {
	// 	catapult.move(200);
	// }
	
	



	

//walk forward x 
//turn 45 degrees clockwise (Abs = -45)
//activate wings
//deactive wings
//back up into matchload zone
//MATCHLOAD -> 15 times therefore assuming 2 sec each launch -> 30sec

//rotate 45 degrees clockwise (abs = -90)
//line up infront of underpass
//move foward x

//rotate 20 degrees counterclockwise (line up towards right of goal) (abs = -70)
// activate wings
//move foward x1 amount 
//move backward x1+5in amount

// rotate 70 degrees counterclockwise (abs = 0)
//move foward x amount (to match front of goal)

//rotate 90 degrees clockwise (abs = -90)
//move forward x1 amount
//move backward x1+5in amount

//rotate 90 degrees counterclockwise (abs = 0)
//move forward x amount (match left of goal)

//rotate 110 degrees clockwise (abs = -110)
//move forward x1 amount

//END


}

void driveStraight(double distance, bool direction)
{
	// Convert distance to encoder ticks
	int targetTicks = (int)((distance / (4 * 3.14159)) * 360);

	// Reset encoders
	FR_Drive.tare_position();
	FL_Drive.tare_position();

	// Calculate initial heading
	int initialHeading = gyro.get_heading();

	// PID constants
	double Kp = 1.0; // Proportional gain (increased)
	double Ki = 0.0; // Integral gain
	double Kd = 0.1; // Derivative gain (introduced)

	// PID variables
	double error = 0.0;
	double integral = 0.0;
	double derivative = 0.0;
	double lastError = 0.0;

	// Drive loop
	if(direction){
		while (FL_Drive.get_position() < targetTicks && FR_Drive.get_position() < targetTicks)
		{
			// Calculate error
			error = targetTicks - (FL_Drive.get_position() + FR_Drive.get_position()) / 2;

			// Update integral
			integral += error;

			// Calculate derivative
			derivative = error - lastError;

			// Calculate PID output
			double output = Kp * error + Ki * integral + Kd * derivative;

			// Set motor speeds

			// Update last error
			lastError = error;

			// Update heading correction
			int currentHeading = gyro.get_heading();
			int headingError = currentHeading - initialHeading;
			double headingCorrection = headingError * 0.1; // Increased heading correction sensitivity

			// Apply heading correction to motor speeds
			setDriveMotors(300 + headingCorrection, 300 - headingCorrection); // Increased motor power

			// Delay to allow motors to update
			pros::delay(20);
		}
	}else{
		while (FL_Drive.get_position() < targetTicks && FR_Drive.get_position() < targetTicks)
		{
			// Calculate error
			error = targetTicks - (FL_Drive.get_position() + FR_Drive.get_position()) / 2;

			// Update integral
			integral += error;

			// Calculate derivative
			derivative = error - lastError;

			// Calculate PID output
			double output = Kp * error + Ki * integral + Kd * derivative;

			// Set motor speeds

			// Update last error
			lastError = error;

			// Update heading correction
			int currentHeading = gyro.get_heading();
			int headingError = currentHeading - initialHeading;
			double headingCorrection = headingError * 0.1; // Increased heading correction sensitivity

			// Apply heading correction to motor speeds
			setDriveMotors(600 + headingCorrection, 600 - headingCorrection); // Increased motor power

			// Delay to allow motors to update
			pros::delay(20);
		}
	}
	

	// Stop motors
	stop();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	
	while (true) {
		setDrive();
		setIntakeMotors();
		setCataMotor();

		pros::delay(10);
	}
}
