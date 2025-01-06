#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void skills(){

    masterIntake.stop();
    masterMogo.extend();
    masterIntake.spinForward();
    AutonWaitFor(500.0);
    masterIntake.spinReverse();
    AutonWaitFor(100.0);
    masterIntake.stop();

    masterChassis.startMainPID({18.0, 0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(270.0, 50.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 1000);
    WaitChassisPID();

    masterChassis.startMainPID({18.0, 20.0}, 75.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    masterChassis.startHeadingPID(0.0, 50.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 1000);
    WaitChassisPID();

    masterChassis.startMainPID({45.0, 25.0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    masterIntake.spinForward();
    WaitChassisPID();

    masterChassis.startHeadingPID(95.0, 50.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 1000);
    WaitChassisPID();

    masterChassis.startMainPID({40.0, 65.0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({40.0, 54.0}, 50.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(180.0, 50.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 1000);
    WaitChassisPID();

    masterChassis.startMainPID({7.0, 60.0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-5.0, 60.0}, 50.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    AutonWaitFor(500.0);

    masterChassis.startMainPID({15.0, 60.0}, 50.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(90.0, 50.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 1000);
    WaitChassisPID();

    masterChassis.startMainPID({15.0, 85.0}, 50.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterIntake.stop();
}

void redLeft(){
    masterMogo.extend();
    masterChassis.updateLeft(-60);
    masterChassis.updateRight(-60);
    
    pros::delay(550);

    masterChassis.updateDrive(-10, -50);

    pros::delay(390);

    masterChassis.updateDrive(-40, -40);
    pros::delay(500);

    masterChassis.updateDrive(0, 0);

    pros::delay(300);

    masterMogo.retract();
    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(100.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    
    masterChassis.updateDrive(40, 40);
    masterIntake.spinForward();
    pros::delay(1300);
    masterChassis.updateDrive(-30, -30);
    pros::delay(50);
    pros::delay(200);
    masterChassis.updateDrive(0, 0);
    masterIntake.spinForward();
    pros::delay(2000);
    masterIntake.spinReverse();
    pros::delay(500);
    masterIntake.spinForward();

    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(180.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }

    masterChassis.updateDrive(40, 40);
    pros::delay(600);
    masterChassis.updateDrive(20, 20);
    pros::delay(200);
    masterChassis.updateDrive(0, 0);
    pros::delay(200);
    masterChassis.updateDrive(-40, -40);
    pros::delay(1000);
    masterChassis.updateDrive(0, 0);

    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(160.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(40, 40);
    pros::delay(700);
    masterChassis.updateDrive(20, 20);
    pros::delay(200);
    masterChassis.updateDrive(0, 0);
    pros::delay(200);
    masterChassis.updateDrive(-40, -40);
    pros::delay(1000);
    masterChassis.updateDrive(0, 0);
    masterIntake.stop();
}







void redRight(){
    masterIntake.spinForward();
    pros::delay(500);
    masterIntake.stop();


}

void blueLeft(){
    masterMogo.extend();
    masterChassis.updateLeft(-60);
    masterChassis.updateRight(-60);
    
    pros::delay(550);

    masterChassis.updateDrive(-10, -50);

    pros::delay(390);

    masterChassis.updateDrive(-40, -40);
    pros::delay(500);

    masterChassis.updateDrive(0, 0);

    pros::delay(300);

    masterMogo.retract();
    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(100.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    
    masterChassis.updateDrive(40, 40);
    masterIntake.spinForward();
    pros::delay(1300);
    masterChassis.updateDrive(-30, -30);
    pros::delay(50);
    pros::delay(200);
    masterChassis.updateDrive(0, 0);
    masterIntake.spinForward();
    pros::delay(2000);
    masterIntake.spinReverse();
    pros::delay(500);
    masterIntake.spinForward();

    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(270.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }

    masterChassis.updateDrive(40, 40);
    pros::delay(1000);
    masterIntake.stop();
    pros::delay(2000);
    masterChassis.updateDrive(0, 0);
}