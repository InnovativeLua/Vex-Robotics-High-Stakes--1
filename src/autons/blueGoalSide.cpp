#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueGoalSide(){
    //Init
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();
    masterTipper.retractExtension();

    //Reversses after scoring.
    masterChassis.startMainPID({40.0, 0.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    AutonWaitFor(300);
    masterTipper.extendTipper();
    WaitChassisPID();
    masterChassis.updateDrive(0, 0);
    AutonWaitFor(300);
    masterTipper.retractTipper();
    AutonWaitFor(300);


    //Reversses after scoring.
    masterChassis.startMainPID({20.0, 0.0}, 127.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();


    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(270.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    //Reversses after scoring.
    masterChassis.startMainPID({27.0, 9.0}, 127.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.updateDrive(0, 0);
    masterMogo.retract();
    AutonWaitFor(200);

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    //Reversses after scoring.
    masterChassis.startMainPID({38.0, -10.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-0.0, -33.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2500, 500);
    WaitChassisPID();

    masterTipper.extendExtension();
    AutonWaitFor(400);

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({10.0, -10.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2500, 500);
    WaitChassisPID();

    masterChassis.startMainPID({20.0, 20.0}, 70.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2500, 500);
    WaitChassisPID();

    masterChassis.updateDrive(0, 0);

}

void wBlueGoalSide(){

}