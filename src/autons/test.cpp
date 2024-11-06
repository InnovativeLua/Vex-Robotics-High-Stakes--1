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
    pros::delay(375);
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
    masterChassis.updateDrive(50, -50);
    pros::delay(900);
    masterIntake.spinReverse();
    masterChassis.updateDrive(50, 50);
    pros::delay(1250);
    masterChassis.updateDrive(20, 20);
    pros::delay(600);
    masterChassis.updateDrive(0, 0);
    pros::delay(300);
    masterChassis.updateDrive(50, -50);
    pros::delay(700);
    masterIntake.stop();
    masterChassis.updateDrive(0, 0);
    pros::delay(1000);
    masterChassis.updateDrive(50, 50);
    pros::delay(1500);
    masterChassis.updateDrive(0, 0);
}

void test2(){
    masterMogo.extend();
    masterChassis.updateLeft(-60);
    masterChassis.updateRight(-60);
    
    pros::delay(550);

    masterChassis.updateDrive(-10, -50);

    pros::delay(350);

    masterChassis.updateDrive(-40, -40);
    pros::delay(300);

    masterChassis.updateDrive(0, 0);

    pros::delay(300);

    masterMogo.retract();
    pros::delay(500);
    masterChassis.updateDrive(50, -50);
    pros::delay(475);
    masterChassis.updateDrive(0, 0);
    pros::delay(500);
    masterChassis.updateDrive(50, 50);

    masterIntake.spinForward();
    pros::delay(1400);
    masterChassis.updateDrive(-30, -30);
    pros::delay(50);
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(-50, -50);
    pros::delay(800);
    masterChassis.updateDrive(50, -50);
    pros::delay(500);
    masterChassis.updateDrive(50, 50);
    pros::delay(350);
    masterChassis.updateDrive(30, 30);
    pros::delay(500);
    masterChassis.updateDrive(-50, -50);
    pros::delay(400);
    masterChassis.updateDrive(-40, 40);
    pros::delay(250);
    masterChassis.updateDrive(50, 50);
    pros::delay(300);
    masterChassis.updateDrive(40, 10);
    pros::delay(700);
    masterChassis.updateDrive(30, 30);
    pros::delay(100);
    masterChassis.updateDrive(-50, -50);
    pros::delay(1000);
    masterChassis.updateDrive(-20, -20);
    pros::delay(200);
    masterChassis.updateDrive(-50, -50);
    pros::delay(400);
    masterChassis.updateDrive(50, -50);
    pros::delay(500);
    masterChassis.updateDrive(-40, -40);
    pros::delay(500);
    masterMogo.extend();
    pros::delay(400);
    masterChassis.updateDrive(40, 40);
    pros::delay(500);
    masterChassis.updateDrive(-50, 50);
    pros::delay(850);
    masterChassis.updateDrive(0, 0);
    pros::delay(200);
    masterChassis.updateDrive(-25, -25);
    pros::delay(100);
    masterChassis.updateDrive(-50, -50);
    pros::delay(1000);
    masterChassis.updateDrive(0, 0);

}