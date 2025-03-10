#include "main.h"
#include "headers/mechs/chassis/basechassis.hpp"
#include "headers/mechs/intake.hpp" 
#include "headers/mechs/MOGOmech.hpp"
#include "headers/mechs/lift.hpp"
#include "headers/mechs/goalTipper.hpp"
#include "headers/mechs/hang.hpp"
#include "headers/brain/ports.hpp"
#include "headers/auton/autons.hpp"
#include "headers/mechs/chassis/odometry.hpp"
#include "headers/brain/autonselector.hpp"
#include "headers/brain/controller.hpp"

#include <vector>
#include <cstdint>




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	masterChassis.initialize();
	masterOdometry.initilize();
	masterTipper.initialize();
	masterMogo.initialize();
	masterHang.initialize();
	masterIntake.initalize();
	masterLift.initalize();
	masterAutonSelector.initilize();
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
void competition_initialize() {
	while (true){
		masterAutonSelector.compTask();
		pros::delay(20);
	}
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
void autonomous() {
	masterAutonSelector.updatePage();
	masterIntake.colorRed = masterAutonSelector.Autons[masterAutonSelector.currentAutonPage].colorRed;
	masterAutonSelector.callSelectedAuton();
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
	int n = 0;
	masterChassis.driverControlPeriod = true;

	masterAutonSelector.updatePage();
	masterIntake.colorRed = masterAutonSelector.Autons[masterAutonSelector.currentAutonPage].colorRed;

	if (masterAutonSelector.Autons[masterAutonSelector.currentAutonPage].Name == "skills" && true){
		//skillsStart();	
	}


	while (true) {
		n += 1;
		int screen = 1;
		pros::screen::erase();

		switch (screen){
			case 0:

				//pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Position X: %g", masterOdometry.getPosition()[0]);
				//pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Position Y: %g", masterOdometry.getPosition()[1]);
				//pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Orientation: %g", masterOdometry.getPosition()[2]);


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
				pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Position X: %g", masterOdometry.getPosition()[0]);
				pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Position Y: %g", masterOdometry.getPosition()[1]);
				pros::screen::print(pros::E_TEXT_MEDIUM, 3, "AUX: %i", masterChassis.auxTracker.get_position());
				pros::screen::print(pros::E_TEXT_MEDIUM, 4, "LEFT: %i", masterChassis.leftTracker.get_position());
				pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Orientation: %g", 180/3.14159*masterOdometry.getPosition()[2]);
				//pros::screen::print(pros::E_TEXT_MEDIUM, 8, "Distance: %g", masterIntake.distanceSensor.get());
				//std::cout << "Intake distance " << masterIntake.distanceSensor.get() << std::endl;
				//std::cout << "Motor Position " << masterLift.liftMotor.get_position() << std::endl;
				pros::screen::print(pros::E_TEXT_MEDIUM, 8, "Current Auton: %s", masterAutonSelector.getSelectedAuton());
				pros::screen::print(pros::E_TEXT_MEDIUM, 9, "intake ve : %g", abs(masterIntake.intakeMotor.get_actual_velocity()));
				mainController->print(0, 0, "C: %s", masterAutonSelector.getSelectedAuton());

				break;
		}

		if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			masterAutonSelector.callSelectedAuton();
		}
		
		masterOdometry.update();
		masterChassis.opControl();
		masterLift.opControl();
		masterIntake.opControl(masterLift.intakeReverseFlag);
		masterMogo.opControl();
		masterTipper.opControl();
		masterHang.opControl();
		masterAutonSelector.compTask();

		pros::delay(mSecWaitTime);
	}
}