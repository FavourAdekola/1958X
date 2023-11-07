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

void rotateToAngle(float target_angle, bool direction)
{
  
  if(direction)
  {
    
    float currentHeading = gyro.get_heading();
    float angleDifference = 10;
    float initialDifference;
    if (target_angle < 180 && currentHeading > 180 && currentHeading < 359.999)
    {
      initialDifference = fabs(currentHeading - 360) + target_angle;
    }else{
      initialDifference = fabs(target_angle - currentHeading);
    }
    
      while(angleDifference > 1){
      currentHeading = gyro.get_heading();
      if (target_angle < 180 && currentHeading > 180 && currentHeading < 359.999)
      {
        angleDifference = fabs(currentHeading - 360) + target_angle;
      }else{
          angleDifference = fabs(target_angle - currentHeading);
        }

        float drivepower = 150 * (angleDifference / initialDifference);
        if(drivepower < 45){
          drivepower = 45;
        }
        // con.print(0,0,"%d", (int)drivepower);
        
        setDriveMotors(drivepower, -drivepower);
        con.print(0, 8, "%d/%d", initialDifference, angleDifference);
      }
      con.print(0,0, "%d", (int)gyro.get_heading());
      stop();
    }
    else
    {
      float currentHeading = gyro.get_heading();
      float angleDifference = 10;
      float initialDifference;
      if (target_angle > 180 && currentHeading < 180 && currentHeading >= 0)
      {
        initialDifference = fabs(currentHeading - 360) + target_angle;
      }
      else
      {
        initialDifference = fabs(target_angle - currentHeading);
      }

      while (angleDifference > 1)
      {
        currentHeading = gyro.get_heading();
        if (target_angle > 180 && currentHeading < 180 && currentHeading >= 0)
        {
          angleDifference = fabs(currentHeading - 360) + target_angle;
        }
        else
        {
          angleDifference = fabs(target_angle - currentHeading);
        }

        float drivepower = 150 * (angleDifference / initialDifference);
        if (drivepower < 25)
        {
          drivepower = 25;
        }

        setDriveMotors(-drivepower, drivepower);
        con.print(0, 8, "%d/%d", initialDifference, angleDifference);
      }
      con.print(0, 0, "%d", (int)gyro.get_heading());
      stop();
  }
}
void stop()
{
    setDriveMotors(0,0);
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