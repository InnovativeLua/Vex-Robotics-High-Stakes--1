#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void redAWP(){

    //Init
    masterIntake.stop();
    masterMogo.extend();

    //Move forward and backwards to push ring out of way.
    masterChassis.startMainPID({-30.0, 0}, 80.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-20.0, 0}, 80.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    //Turn towards the alliance stake.
    masterChassis.startHeadingPID(90.0, 75.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 2000, 300);
    WaitChassisPID();

    //Puts ring on alliance Stake.
    AutonWaitFor(300.0);
    masterIntake.spinForward();
    AutonWaitFor(500.0);
    masterIntake.spinReverse();
    AutonWaitFor(100.0);
    masterIntake.stop();

    //Backup slightly.
    masterChassis.startMainPID({-20.0, -0.0}, 90.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();

    //Turn towards goal + goes towards goal.
    masterChassis.startHeadingPID(235.0, 75.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

   masterChassis.startMainPID({9.0, 43.0}, 90.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Grabs goal.
    masterMogo.retract();
    AutonWaitFor(500.0);

    //Turns toward 1 ring.
    masterChassis.startHeadingPID(0.0, 75.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();


    masterIntake.spinForward();

    //Go to the first ring.
    masterChassis.startMainPID({25.0, 38.0}, 70.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Go to the first of the two rings in the middle.
    masterChassis.startMainPID({20.0, 59.0}, 70.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Backs up slightly.
    masterChassis.startMainPID({20.0, 45.0}, 70.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Go to the second of the two rings in the middle.
    masterChassis.startMainPID({30.0, 59.0}, 70.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Hit middle bar.
    masterChassis.startMainPID({0.0, 50.0}, 70.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 3000, 500);
    WaitChassisPID();

    masterIntake.stop();
}