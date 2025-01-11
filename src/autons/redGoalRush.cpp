#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"


void redGoalRush(){
    //Init
    masterIntake.stop();
    masterMogo.extend();

    //Move forward and grab middle goal.
    masterChassis.startMainPID({50.0, 0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    AutonWaitFor(500);
    masterTipper.extendTipper();
    WaitChassisPID();
    masterTipper.extendExtension();

    //Reverses after grabbing it and lets go.
    masterChassis.startMainPID({40.0, 0}, 80.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterTipper.retractExtension();
    masterTipper.retractTipper();

    //Goes towards the other mobile goal and grabs it.
    masterChassis.startMainPID({30.0, -10}, 80.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();
    AutonWaitFor(300);

    masterMogo.retract();
    AutonWaitFor(300);

    //Intakes the ring on the ground.
    masterIntake.spinForward();
    masterChassis.startMainPID({35.0, 10}, 80.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    //Reverses back to around where the second goal grabbed started and releases the goal.
    masterChassis.startMainPID({30.0, -15}, 80.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    masterMogo.extend();
    WaitChassisPID();

    //Goes back forwards.
    masterChassis.startMainPID({35.0, 0}, 80.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    //Turns towards the middle grabbed goal and goes to it and picks it up.
    masterChassis.startHeadingPID(0.0, 75.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 2000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({40.0, 0}, 80.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(300);

    //Goes for the corner ring.
    masterIntake.spinForward();
    masterChassis.startMainPID({0, 20.0}, 80.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();
}