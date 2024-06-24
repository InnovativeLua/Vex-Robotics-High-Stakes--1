#include "headers/mechs/chassis/basechassis.hpp"
#include "headers/brain/controller.hpp"


//CONSTANTS FOR THE TURN PID TEMPORARY REMOVE THESE LATER AND HAVE A MORE PERMENANT SOLUTION;
const double P_X = 0.01;
const double I_X = 0;
const double D_X = 0;

void chassis::updateLeft(int power){
    for (auto i : ActiveLeftMotors) {
        i.move(power);
    }
}

void chassis::updateRight(int power){
    for (auto i : ActiveRightMotors) {
        i.move(power);
    }
}

void chassis::updateDrive(int leftPower, int rightPower){
    updateLeft(leftPower);
    updateRight(rightPower);
}

void chassis::opControl(){
    if (driverControlPeriod){
        if (driveControl == E_ARCADE_CONTROL){
			/*
            int power = mainController.get_analog(ANALOG_LEFT_Y);
            int turn = mainController.get_analog(ANALOG_RIGHT_X);
            int leftPower = power + turn;
            int rightPower = power - turn;

            updateDrive(leftPower, rightPower);

			*/
        } else if (driveControl == E_TANK_CONTROL){
            int leftPower = mainController->get_analog(ANALOG_LEFT_Y);
            int rightPower = mainController->get_analog(ANALOG_RIGHT_Y);

            updateDrive(leftPower, rightPower);
        }

		if (mainController->get_digital(DIGITAL_A)) {
			if (PTODB == true){
				PTOPistons.set_value(PTOValue);
				PTODB = false;
				PTOValue = !PTOValue;
			}
		} else {
			PTODB = true;
		}

		if (mainController->get_digital(DIGITAL_Y)){
			updateDrive(600, 600);
		}
    }
}

void chassis::initialize(){
    leftFrontMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    leftFrontMotor.set_reversed(true);
    leftFrontMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    leftBackMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    leftBackMotor.set_reversed(true);
    leftBackMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    leftTopMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    leftTopMotor.set_reversed(true);
    leftTopMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    rightFrontMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    rightFrontMotor.set_reversed(false);
    rightFrontMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    rightBackMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    rightBackMotor.set_reversed(false);
    rightBackMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    rightTopMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    rightTopMotor.set_reversed(false);
    rightTopMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    //ChassisIMU.reset(true);
}

/*
void chassis::turnToAngle(double targetAngle){
	double previousHeading = ChassisIMU.get_heading();
	double previousError = 0.0;
	while (true){
		if (ChassisIMU.is_calibrating()){
			pros::delay(20);
			continue;
		}
		double heading = ChassisIMU.get_heading();

		double error = targetAngle - heading;

		std::cout << "error1: " << error << std::endl;

		if (abs(error) > 180){
			error -= copysign(1.0, error) * 360;
		}

		std::cout << "error2: " << error << std::endl;

		double derivative = error - previousError;

		previousError = error;

		double turnPower = drivePID.constants.kp * error + derivative * drivePID.constants.kd;

		std::cout << "Turn power before change: " << turnPower << std::endl;

		if (error < 1){
			break;
		}
		if (turnPower > 127.0){
			turnPower = 127.0;
		}
		if (turnPower < -127.0){
			turnPower = -127.0;
		}

		std::cout << "Turn power after change: " << turnPower << std::endl;

        updateDrive(turnPower, -turnPower);

		pros::delay(20);
	}
}
*/

chassis masterChassis;