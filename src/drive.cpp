#include "main.h"

void setDriveMotors(int R, int L)
{
    FL_Drive.move(L);
    BL_Drive.move(L);
    TL_Drive.move(L);

    FR_Drive.move(R);
    BR_Drive.move(R);
    TR_Drive.move(R);

}

void setDrive()
{

    int R_Power = con.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int L_Power = con.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

    setDriveMotors(R_Power, L_Power);
}

void setIntake(int power)
{
    intake.move_velocity(power);
}


void setIntakeMotors()
{
    int power = 0;
    if(con.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
    {
        power = 600;
    }
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
        power = -600;
    }
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) || (con.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)))
    {
        power = 0;
    }

    setIntake(power);
}

void push_intake()
{
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        // Pistons Push Out
        pushy_one.set_value(127);
    }
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        // Pistons Retract 
        pushy_one.set_value(0);
    }
}