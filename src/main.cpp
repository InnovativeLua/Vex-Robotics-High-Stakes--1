#include "main.h"
#include "headers/mechs/chassis/basechassis.hpp"
#include "headers/mechs/intake.hpp" 
#include "headers/brain/ports.hpp"
#include "headers/brain/autonselector.hpp"
#include "headers/auton/autons.hpp"
#include "headers/mechs/chassis/odometry.hpp"

#include <vector>
#include <cstdint>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

//AutonSelector masterAutonSelector = AutonSelector();


bool pressed2 = false;
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
		if (pressed2 == false){
			//masterAutonSelector.cycleAutons();
			pressed2 = true;
		}
	} else {
		if (pressed2 == true){
			pressed2 = false;
		}
		pros::lcd::clear_line(2);
	}
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void callProfile(){
	//masterProfile.profileTask();
}

void initialize() {
	masterOdometry.initilize();//May cause a problem because the robot
	//could be moved in the time between initalize and the start of 
	//drive control period.

	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	std::vector<Auton> autonsList = {};

	Auton a_RedAWP;
	a_RedAWP.autonFunction = *redAWP;
	a_RedAWP.Name = "DefensiveAWP";

	Auton a_test;
	a_test.autonFunction = *test;
	a_test.Name = "OffensiveAWP";

	autonsList.push_back(a_RedAWP);
	autonsList.push_back(a_test);

	//masterAutonSelector.addAutons(autonsList);

	pros::lcd::register_btn1_cb(on_center_button);

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
	masterChassis.driveControl = masterChassis.E_TANK_CONTROL;
	masterChassis.driverControlPeriod = true;

	//auto myLights = sylib::Addrled(0, 'A', 32);
	//myLights.turn_on();
	//myLights.set_all(0x00FF00);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);


		masterOdometry.update();
		masterChassis.opControl();
		masterIntake.opControl();

		std::cout << masterOdometry.getPosition()[0] << "," << masterOdometry.getPosition()[1] << std::endl;


		pros::delay(mSecWaitTime);
	}
}