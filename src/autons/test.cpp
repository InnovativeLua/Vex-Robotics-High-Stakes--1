#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"


void skills(){

    masterIntake.stop();
    masterMogo.extend();
    masterIntake.spinForward();
    pros::delay(500);
    masterIntake.spinReverse();
    pros::delay(100);
    masterIntake.stop();
    masterChassis.updateDrive(60.0, 57.0);
    pros::delay(470);
    masterChassis.updateDrive(20.0, 19.0);
    pros::delay(150);
    masterChassis.updateDrive(0, 0);

    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(94.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(-50.0, -47.5);
    pros::delay(850);
    masterChassis.updateDrive(-20.0, -19.0);
    pros::delay(500);
    masterMogo.retract();
    masterChassis.updateDrive(0, 0);
    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(274.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterIntake.spinForward();
    masterChassis.updateDrive(50, 47.5);
    pros::delay(2000);
    masterChassis.updateDrive(20, 19);
    pros::delay(500);
    masterChassis.updateDrive(-20, -19);
    pros::delay(500);
    masterChassis.updateDrive(0, 0);

    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(10.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterIntake.spinReverse();
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterIntake.spinForward();
    masterChassis.updateDrive(-40, -38);
    pros::delay(900);
    masterChassis.updateDrive(0, 0);
    masterMogo.extend();
    pros::delay(200);
    masterChassis.updateDrive(40, 38);
    pros::delay(600);
    masterChassis.updateDrive(0, 0);

    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(274.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(-50, -58.5);
    pros::delay(4000);
    masterChassis.updateDrive(-20, -20.5);
    pros::delay(500);
    masterMogo.retract();
    masterChassis.updateDrive(0, 0);
    pros::delay(100);


    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(88.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(40.0, 38.0);
    pros::delay(2000);
    masterChassis.updateDrive(20.0, 19.0);
    pros::delay(500);
    masterChassis.updateDrive(0, 0);
    pros::delay(100); 
    masterChassis.updateDrive(-30.0, -28.5);
    pros::delay(500);

    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(358.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }
    masterChassis.updateDrive(0, 0);
    pros::delay(100);
    masterChassis.updateDrive(-40, -38);
    pros::delay(900);
    masterChassis.updateDrive(0, 0);
    masterMogo.extend();
    pros::delay(200);
    masterChassis.updateDrive(40, 38);
    pros::delay(600);
    masterChassis.updateDrive(0, 0);

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

    masterLift.liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    masterLift.liftVelocity = 40;
    masterLift.spinForward();
    masterMogo.extend();
    masterChassis.updateLeft(-60);
    masterChassis.updateRight(-60);
    
    pros::delay(550);

    masterLift.liftVelocity = 0;
    masterLift.spinForward();

    masterChassis.updateDrive(-50, -10);

    pros::delay(390);

    masterChassis.updateDrive(-40, -40);
    pros::delay(500);

    masterChassis.updateDrive(0, 0);

    pros::delay(300);

    masterMogo.retract();
    pros::delay(500);
    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(270.0);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    } 
    masterChassis.updateDrive(40, 40);
    masterIntake.spinForward();
    pros::delay(1300);
    masterChassis.updateDrive(-30, -30);
    pros::delay(50);

    masterChassis.headingPIDEnabled = true;
    masterChassis.headingPID.resetVariables();
    masterChassis.headingPID.setTarget(225);
    while (masterChassis.headingPIDEnabled){
        masterChassis.PIDLoop();
        pros::delay(20);
    }

    masterChassis.updateDrive(40, 40);
    pros::delay(1800);
    masterIntake.stop();

    masterLift.liftVelocity = 200;
    masterLift.spinForward();
    
    pros::delay(500);

    masterLift.liftVelocity = 0;
    masterLift.spinForward();

    pros::delay(900);

    masterLift.liftVelocity = 100;
    masterLift.spinReverse();

    pros::delay(900);
    masterLift.liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    masterLift.liftVelocity = 0;
    masterLift.spinForward();

    masterChassis.updateDrive(-50, -50);
    pros::delay(700);

    masterIntake.spinForward();
    masterChassis.updateDrive(50, 10);
    pros::delay(1000);

    masterChassis.updateDrive(30, 30);
    pros::delay(1000);

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