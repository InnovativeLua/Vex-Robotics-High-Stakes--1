//Respective header file for the chassis.
#include "headers/mechs/chassis/basechassis.hpp"

/**
 * Sets the current chassis control type.
 *
 * @param targetDriveControl(E_driveControl) Drive control to switch to.
 * @return Nothing
 * 
 */
void chassis::setDriveControl(E_driveControl targetDriveControl){
    driveControl = targetDriveControl;
}

/**
 * Get the current chassis control type.
 *
 * @return driveControl(E_driveControl) current drive control type for the chassis.
 * 
 */
chassis::E_driveControl chassis::getCurrentDriveControl(){
    return driveControl;
}

/**
 * Runs the left chassis motors based on the power param.
 *
 * @param power(int) Voltage for motors from -127 to 127
 * @return Nothing
 * 
 */
void chassis::updateLeft(int power){
    for (auto i : ActiveLeftMotors) {
        i.move(power);
    }
}

/**
 * Runs the right chassis motors based on the power param.
 *
 * @param power(int) Voltage for motors from -127 to 127
 * @return Nothing
 * 
 */
void chassis::updateRight(int power){
    for (auto i : ActiveRightMotors) {
        i.move(power);
    }
}

/**
 * Runs both the left and right chassis motors.
 *
 * @param leftPower(int) Voltage for left chassis motors ranging from -127 to 127.
 * @param rightPower(int) Voltage for right chassis motors ranging from -127 to 127.
 * @return Nothing
 * 
 */
void chassis::updateDrive(int leftPower, int rightPower){
    updateLeft(leftPower);
    updateRight(rightPower);
}

/**
 * Runs during operator control code.
 * Makes the drivetrain move based on the controller joysticks and the type of control we want. 
 * Arcade Control - One vertical joystick moves the drivetrain forward and one horizontal turns the drivetrain.
 * Tank Control - Each vertical joystick moves each side of the drivetrain.
 * 
 * @return Nothing
 * 
 */
void chassis::opControl(){
    if (headingPIDEnabled){
        if (headingPID.checkExitCondition() == headingPID.SMALL_EXIT){
            headingPIDEnabled = false;
            std::cout << "Disabled Heading PID" << std::endl;
        }
        double power = headingPID.compute(ChassisIMU.get_heading());
        std::cout << "power: " << power << std::endl;
        std::cout << "target: " << headingPID.getTarget()<< std::endl;
        std::cout << "current: " << ChassisIMU.get_heading() << std::endl;
        if (power > 75){
            power = 75;
        } else if (power < -75){
            power = -75;
        }
        updateDrive(power, -power);
        std::cout << "Power: " << std::endl;
    } else if (driverControlPeriod){ 
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
            headingPIDEnabled = true;
            headingPID.resetVariables();
            headingPID.setTarget(180.0);
            return;
        }
		//Arcade control for the drivetrain in case we want to use it.
        if (driveControl == E_ARCADE_CONTROL){
            int power = mainController->get_analog(ANALOG_LEFT_Y);
            int turn = mainController->get_analog(ANALOG_RIGHT_X);
            int leftPower = power + turn; 
            int rightPower = power - turn;

            updateDrive(leftPower, rightPower);

		//Tank control for the drivetrain in case we want to use it.
        } else if (driveControl == E_TANK_CONTROL){
            int leftPower = mainController->get_analog(ANALOG_LEFT_Y);
            int rightPower = mainController->get_analog(ANALOG_RIGHT_Y);

            updateDrive(leftPower, rightPower);
        }
		
    }
}

void chassis::startHeadingPID(double target){
    headingPIDEnabled = true;
    headingPID.resetVariables();
    headingPID.setTarget(target);
}

/**
 * Runs during initialization.
 * Sets all the motors to the correct gearing, brake modes, and encoder units.
 * Resets the chassis IMU.
 * 
 * @return Nothing
 * 
 */
void chassis::initialize(){
	//Sets the left front motor to the correct gearing, brake mode, and encoder units.
    leftFrontMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
	leftFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leftFrontMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

	//Sets the left back motor to the correct gearing, brake mode, and encoder units.
    leftBackMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
	leftBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leftBackMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

	//Sets the left top motor to the correct gearing, brake mode, and encoder units.
    leftTopMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
	leftTopMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leftTopMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

	//Sets the right front motor to the correct gearing, brake mode, and encoder units.
    rightFrontMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
	rightFrontMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    rightFrontMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

	//Sets the right back motor to the correct gearing, brake mode, and encoder units.
    rightBackMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
	rightBackMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    rightBackMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

	//Sets the right top motor to the correct gearing, brake mode, and encoder units.
    rightTopMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
	rightTopMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    rightTopMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    driveControl = E_TANK_CONTROL;

    headingPID.resetVariables();
    headingPID.setExitCondition(0.1, 500.0, 5000, 200);

    ChassisIMU.reset(true); //Resets the chassis IMU.
}

chassis masterChassis; //Global main chassis to use the drivetrain in other files.