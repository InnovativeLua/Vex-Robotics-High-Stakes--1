#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueAWP(){
    //Init
    masterIntake.stop();
    masterMogo.extend();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.startMainPID({12.0, -0}, 75.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;

    masterChassis.startMainPID({-37.0, -4.0}, 90.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    AutonWaitFor(100);
    masterMogo.retract();

    masterIntake.spinForward();

    masterChassis.startMainPID({-53.0, -32.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-73.0, -26.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-50.0, -20.0}, 90.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-69.0, -18.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-40.0, 40.0}, 90.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.updateDrive(0, 0);
}