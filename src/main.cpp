#include "main.h"
#include "headers/mechs/chassis/basechassis.hpp"
#include "headers/mechs/intake.hpp" 
#include "headers/mechs/MOGOmech.hpp"
#include "headers/mechs/lift.hpp"
#include "headers/brain/ports.hpp"
#include "headers/brain/autonselector.hpp"
#include "headers/auton/autons.hpp"
#include "headers/mechs/chassis/odometry.hpp"
#include "headers/brain/controller.hpp"

#include <vector>
#include <cstdint>

//AutonSelector masterAutonSelector = AutonSelector();





/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void callProfile(){
	//masterProfile.profileTask();
}

pros::adi::DigitalIn limitSwitch = pros::adi::DigitalIn('G');
bool limitDebounce = false;

void initialize() {
	masterOdometry.initilize();
	masterChassis.initialize();
	masterMogo.initialize();
	masterOdometry.initilize();


	std::vector<Auton> autonsList = {};

	Auton a_RedAWP;
	a_RedAWP.autonFunction = *redAWP;
	a_RedAWP.Name = "DefensiveAWP";

	Auton a_test;
	a_test.autonFunction = *test;
	a_test.Name = "OffensiveAWP";

	Auton a_test2;
	a_test2.autonFunction = *test;
	a_test2.Name = "RedFinals";

	Auton a_test3;
	a_test3.autonFunction = *test;
	a_test3.Name = "BlueFinals";

	autonsList.push_back(a_RedAWP);
	autonsList.push_back(a_test);
	autonsList.push_back(a_test2);
	autonsList.push_back(a_test3);

	masterAutonSelector.addAutons(autonsList);


	//pros::Task motionProfileTask(callProfile);
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
void autonomous() {
	//masterAutonSelector.callSelectedAuton();
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
	const int mSecWaitTime = 10;
	masterChassis.driverControlPeriod = true;

	masterChassis.ChassisIMU.reset(true);

	while (masterChassis.ChassisIMU.is_calibrating()){
		pros::delay(20);
	}

	while (true) {
		int screen = 2;

		switch (screen){
			case 0:
				pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Current Auton: %3d", masterAutonSelector.currentAutonPage);
				pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Current Auton: %s", masterAutonSelector.Autons[masterAutonSelector.currentAutonPage].Name);

				pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Position X: %g", masterOdometry.getPosition()[0]);
				pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Position Y: %g", masterOdometry.getPosition()[1]);
				pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Orientation: %g", masterOdometry.getPosition()[2]);


				//55 Degrees celcius is overheating and power power is reduced
				//Only in resolution of 5 degrees so starts as 35 then 40 then 45 etc
				pros::screen::print(pros::E_TEXT_MEDIUM, 6, "LeftBackMotor Temperature: %g°C", masterChassis.leftBackMotor.get_temperature());
				pros::screen::print(pros::E_TEXT_MEDIUM, 7, "LeftTopMotor Temperature: %g°C", masterChassis.leftTopMotor.get_temperature());
				pros::screen::print(pros::E_TEXT_MEDIUM, 8, "LeftFrontMotor Temperature: %g°C", masterChassis.leftFrontMotor.get_temperature());

				pros::screen::print(pros::E_TEXT_MEDIUM, 9, "RightBackMotor Temperature: %g°C", masterChassis.rightBackMotor.get_temperature());
				pros::screen::print(pros::E_TEXT_MEDIUM, 10, "RightTopMotor Temperature: %g°C", masterChassis.rightTopMotor.get_temperature());
				pros::screen::print(pros::E_TEXT_MEDIUM, 11, "RightFrontMotor Temperature: %g°C", masterChassis.rightFrontMotor.get_temperature());

				break;
			case 1:
				pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Current Auton: %3d", masterAutonSelector.currentAutonPage);
				pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Current Auton: %s", masterAutonSelector.Autons[masterAutonSelector.currentAutonPage].Name);

				pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Position X: %g", masterOdometry.getPosition()[0]);
				pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Position Y: %g", masterOdometry.getPosition()[1]);
				pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Orientation: %g", masterOdometry.getPosition()[2]);
			case 2:
				pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Color Hue: %g", masterIntake.ringDetector.get_hue());
				pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Lift Angle: %g", masterLift.liftMotor.get_position());
		}

		//masterOdometry.update();
		masterChassis.opControl();
		masterIntake.opControl();
		masterLift.opControl();
		masterMogo.opControl();

		if (limitSwitch.get_value() != limitDebounce){
			limitDebounce = limitSwitch.get_value();
			if (limitSwitch.get_value() == true){
				masterAutonSelector.cycleAutons();
				std::cout << masterAutonSelector.currentAutonPage << std::endl;
			}
		}

		std::cout << masterOdometry.getPosition()[0] << "," << masterOdometry.getPosition()[1] << std::endl;
		pros::delay(mSecWaitTime);
	}
}