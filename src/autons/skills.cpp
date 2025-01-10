#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void skills(){

    masterIntake.stop();
    masterMogo.extend();
    masterIntake.spinForward();
    AutonWaitFor(500.0);
    masterIntake.spinReverse();
    AutonWaitFor(100.0);
    masterIntake.stop();

    masterChassis.startMainPID({14.0, 0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(270.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({11.0, 20.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    masterChassis.startHeadingPID(0.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({45.0, 25.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    masterIntake.spinForward();
    WaitChassisPID();


    masterChassis.startMainPID({60.0, 63.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    AutonWaitFor(500);

    masterChassis.startMainPID({60.0, 70.0}, 50.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

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

    masterChassis.startMainPID({60.0, 51.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(180.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.spinForward();
    masterChassis.startMainPID({40.0, 55.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({20.0, 55.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-5.0, 55.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({15.0, 55.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({15.0, 75.0}, 85.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({0.0, 75.0}, 85.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 6000, 500);
    WaitChassisPID();

    masterMogo.extend();

    masterChassis.startMainPID({14.0, 0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();

}