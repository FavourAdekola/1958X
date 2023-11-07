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
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
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
	pros::lcd::set_text(1, "Produced by Kash Krabs");
	pros::lcd::set_text(2, "Lucas is Still Gay");

	FR_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BR_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	TR_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	FL_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	BL_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	TL_Drive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	gyro.reset();
	con.clear();
	pros::Task controller(controllerScreen, "print");
	pros::delay(2000);
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
	driveStraight(100,true);
}

void driveStraight(double distance, bool direction)
{
	// Convert distance to encoder ticks
	int targetTicks = (int)((distance / (3.25 * 3.14159)) * 360);

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
		push_intake();
		setCataMotor();
		set_wings();

		pros::delay(10);
	}
}
