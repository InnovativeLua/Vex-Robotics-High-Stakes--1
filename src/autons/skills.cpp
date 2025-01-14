#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void skills(){
    //Scores alliance Stake.
    masterIntake.stop();
    masterMogo.extend();
    masterIntake.spinForward();
    AutonWaitFor(500.0);
    masterIntake.spinReverse();
    AutonWaitFor(100.0);
    masterIntake.stop();

    //Reversses after scoring.
    masterChassis.startMainPID({14.0, 0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 2000, 500);
    WaitChassisPID();

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(270.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({11.0, 20.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(0.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({45.0, 25.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    masterIntake.spinForward();
    WaitChassisPID();

    //Goes for second ring and primes the lady brown.
    masterChassis.startMainPID({60.0, 63.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    AutonWaitFor(500);

    //Goes forward to hopefully get a better grip on the ring
    masterChassis.startMainPID({60.0, 70.0}, 50.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Turns towards the stake and puts the ring on it.
    masterChassis.startHeadingPID(87.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    AutonWaitFor(1000);

    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    masterIntake.spinReverse();
    AutonWaitFor(100);
    masterIntake.stop();
    AutonWaitFor(2000);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;

    //Backs up.
    masterChassis.startMainPID({60.0, 48.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    //Goes for the line of rings.
    masterChassis.startHeadingPID(180.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.spinForward();
    masterChassis.startMainPID({40.0, 52.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({20.0, 52.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-15.0, 52.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();
    masterOdometry.setY(0.0);

    //Backs up.
    masterChassis.startMainPID({15.0, 52.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({15.0, 75.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterOdometry.setX(0.0);

    //Places the mobile goal in the corner.
    masterChassis.startMainPID({3.0, 3.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterMogo.extend();

    masterChassis.startMainPID({10.0, 10.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

}