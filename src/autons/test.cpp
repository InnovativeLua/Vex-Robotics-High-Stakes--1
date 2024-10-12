#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"


void test(){
    masterMogo.extend();
    masterChassis.updateLeft(-60);
    masterChassis.updateRight(-60);
    
    pros::delay(500);

    masterChassis.updateDrive(-50, -10);

    pros::delay(350);

    masterChassis.updateDrive(-40, -40);
    pros::delay(300);

    masterChassis.updateDrive(0, 0);

    pros::delay(300);

    masterMogo.retract();
    pros::delay(500);
    masterChassis.updateDrive(-50, 50);
    pros::delay(400);
    masterChassis.updateDrive(0, 0);
    pros::delay(500);
    masterChassis.updateDrive(50, 50);

    masterIntake.spinForward();
    pros::delay(1000);
    masterChassis.updateDrive(-30, -30);
    pros::delay(50);
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(-50, -50);
    pros::delay(1000);
    masterChassis.updateDrive(-50, 50);
    pros::delay(500);

    masterChassis.updateDrive(-30, -30);
    pros::delay(500);

    masterMogo.extend();
    pros::delay(500);
    masterChassis.updateDrive(40, 40);
    pros::delay(400);
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(-50, 50);
    pros::delay(735);
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterIntake.stop();
    masterChassis.updateDrive(-75, -75);
    pros::delay(650);
    masterChassis.updateDrive(-20, -20);
    pros::delay(300);
    masterMogo.retract();
    pros::delay(500);
    masterChassis.updateDrive(25, -25);
    pros::delay(200);
    masterChassis.updateDrive(75, 75);
    pros::delay(1300);
    masterIntake.spinForward();
    masterChassis.updateDrive(30, 30);
    pros::delay(1300);
    masterChassis.updateDrive(0, 0);
    masterChassis.updateDrive(-50, 50);
    pros::delay(300);
    masterChassis.updateDrive(-35, -35);
    pros::delay(500);
}