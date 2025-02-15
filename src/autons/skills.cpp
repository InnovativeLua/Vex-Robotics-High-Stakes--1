#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"


void skillsStart(){

}

void skills(){
    //Scores alliance Stake.
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();
    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    AutonWaitFor(500.0);
    masterIntake.spinReverse();
    masterIntake.autonFlag = masterIntake.E_REVERSE_FLAG;
    AutonWaitFor(100.0);
    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;

    //Reversses after scoring.
    masterChassis.startMainPID({9.0, 4.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 2000, 500);
    WaitChassisPID();

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(270.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({8.0, 23.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(0.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({25.0, 22.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    WaitChassisPID();

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(90.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();


    masterChassis.startMainPID({25.0, 47.0}, 80.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(180.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({-10.0, 45.0}, 70.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterOdometry.setX(0.0);

    //Backs up.
    masterChassis.startMainPID({15.0, 40.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({15.0, 65.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterOdometry.setY(0.0);

    //Places the mobile goal in the corner.
    masterChassis.startMainPID({-10.0, 20.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterMogo.extend();

    AutonWaitFor(150.0);

    masterChassis.startMainPID({10.0, 10.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({10.0, 10.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({9.0, -120.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterMogo.retract();

    masterChassis.startMainPID({0.0, -150.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterMogo.retract();

    AutonWaitFor(150.0);

}