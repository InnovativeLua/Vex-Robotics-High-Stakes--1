#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueAWP(){
    //Init
    masterIntake.stop();
    masterMogo.extend();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.updateDrive(40, 40);
    AutonWaitFor(500);

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;

    masterChassis.updateDrive(-50, -50);
    AutonWaitFor(1650);
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(100);
    masterMogo.retract();
    AutonWaitFor(100);

    masterChassis.updateDrive(40, -40);
    AutonWaitFor(1000);

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.updateDrive(40, 40);
    AutonWaitFor(2400);
    masterChassis.updateDrive(0, 0);

    masterChassis.updateDrive(-50, 50);
    AutonWaitFor(1200);

    masterChassis.updateDrive(60, 60);
    AutonWaitFor(2000);
    masterChassis.updateDrive(0, 0);

    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.updateDrive(40, 40);
    AutonWaitFor(200);

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(500);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;

    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;
    AutonWaitFor(500);
}