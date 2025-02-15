#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueGoalSide(){
    //Init
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.updateDrive(40, 40);
    AutonWaitFor(500);

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);

    masterChassis.updateDrive(-60, -60);
    AutonWaitFor(1400);
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(100);
    masterMogo.retract();
    AutonWaitFor(100);

    masterChassis.startHeadingPID(110.0, 70.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.updateDrive(40, 40);
    AutonWaitFor(2200);
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(100);
    masterChassis.updateDrive(-20, -20);
    AutonWaitFor(1000);

    masterChassis.startHeadingPID(290.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.updateDrive(40, 40);
    AutonWaitFor(2400);
    masterChassis.updateDrive(0, 0);

    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.updateDrive(40, 40);
    AutonWaitFor(200);

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(500);

    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;
    AutonWaitFor(500);
}

void wBlueGoalSide(){
    //Init
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();

    AutonWaitFor(2000);
    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.updateDrive(40, 40);
    AutonWaitFor(500);

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);

    masterChassis.updateDrive(-60, -60);
    AutonWaitFor(1400);
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(100);
    masterMogo.retract();
    AutonWaitFor(100);

    masterChassis.startHeadingPID(110.0, 70.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.updateDrive(40, 40);
    AutonWaitFor(2200);
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(100);
    masterChassis.updateDrive(-20, -20);
    AutonWaitFor(1000);

    masterChassis.startHeadingPID(290.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.updateDrive(40, 40);
    AutonWaitFor(2400);
    masterChassis.updateDrive(0, 0);

    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.updateDrive(40, 40);
    AutonWaitFor(200);

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(500);

    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;
    AutonWaitFor(500);
}