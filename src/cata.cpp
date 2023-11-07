#include "main.h"

int power = -127;
bool ready = false;

void setCataMotor()
{
    if(limit_switch.get_value() && !ready)
    {
        power = 0;
        ready = true;
    }

    if(con.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && ready)
    {
        catapult.move(-127);
        pros::delay(80);
        catapult.move(0);
        
        ready = false;
        pros::delay(45);
    }

    if (!ready)
    {
        power = -127;
    }

    rapid_fire();
    catapult.move(power);
}
void rapid_fire()
{
    bool set = false;
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        if (!set)
        {
            catapult.move_velocity(-127);
            pros::delay(45);
        }
    }
    
}