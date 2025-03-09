#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void redRingSide(){
    //Init
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();
    masterTipper.retractExtension();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.startMainPID({10.0, 0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);

    //Reversses after scoring.
    masterChassis.startMainPID({-33.0, -6.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    AutonWaitFor(1100);
    masterMogo.retract();
    WaitChassisPID();
    AutonWaitFor(300);

    masterChassis.startHeadingPID(180.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({-49.0, -2.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-56.0, 6.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-40.0, 17.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-10.0, -10.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();

    
    masterChassis.updateDrive(0, 0);
}

void wBlueRingSide(){
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

    masterChassis.startHeadingPID(250.0, 70.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.updateDrive(40, 40);
    AutonWaitFor(2200);
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(100);
    masterChassis.updateDrive(-20, -20);
    AutonWaitFor(1000);

    masterChassis.startHeadingPID(70.0, 100.0);
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