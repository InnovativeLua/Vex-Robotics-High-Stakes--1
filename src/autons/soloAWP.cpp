#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void soloREDAWP(){
    //Init
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();
    masterTipper.retractExtension();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    masterChassis.startMainPID({5.0, -1.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 1000, 500);
    WaitChassisPID();

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);

    //Reversses after scoring.
    masterChassis.startMainPID({-19.0, -5.0}, 127.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(500);

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({-27.0, 10.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();
    masterChassis.updateDrive(0, 0);    

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({0.0, -5.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();
    masterChassis.updateDrive(0, 0);   
}