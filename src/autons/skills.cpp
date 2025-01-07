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

    masterChassis.startMainPID({18.0, 0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 2000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(270.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({17.0, 20.0}, 127.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    masterChassis.startHeadingPID(0.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({45.0, 25.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    masterIntake.spinForward();
    WaitChassisPID();

    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({42.0, 65.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({42.0, 54.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(180.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({10.0, 55.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-3.0, 55.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 4000, 500);
    WaitChassisPID();

    AutonWaitFor(500.0);

    masterChassis.startMainPID({20.0, 59.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({18.0, 85.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 4000, 500);
    WaitChassisPID();

    masterIntake.stop();
}