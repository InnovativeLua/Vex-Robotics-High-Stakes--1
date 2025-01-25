#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueAWP(){
    //Init
    masterIntake.stop();
    masterMogo.extend();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.startMainPID({12.0, 0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;

    masterChassis.startMainPID({-37.0, 4.0}, 90.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    AutonWaitFor(1100);
    masterMogo.retract();
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.startMainPID({-53.0, 30.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-66.0, 24.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-35.0, 10.0}, 90.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-64.0, 10.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-40.0, -50.0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;
    masterChassis.updateDrive(0, 0);
}
}