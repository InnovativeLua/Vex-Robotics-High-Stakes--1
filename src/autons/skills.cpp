#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"


void skillsStart(){

}

void skills(){
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();
    masterTipper.retractExtension();

    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    AutonWaitFor(100);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);


    //Reversses after scoring.
    masterChassis.startMainPID({-9.0, -1.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 2000, 500);
    WaitChassisPID();

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({-9.0, -23.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(180.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({-30.0, -20.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);

    masterChassis.startMainPID({-57.0, -50.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);


    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(270.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();


    //Move forward and backwards to push ring out of way.
    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;

    masterChassis.startMainPID({-58.0, -55.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    AutonWaitFor(2000);

    masterIntake.autonFlag = masterIntake.E_REVERSE_FLAG;
    AutonWaitFor(150);
    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;



    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(1000);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);

    masterChassis.startMainPID({-57.0, -45.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(0.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.startMainPID({0.0, -45.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-15.0, -45.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(270.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 5000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({-15.0, -55.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-0.0, -55.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterMogo.extend();

    masterChassis.startMainPID({-8.0, 0.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(270.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();


    //This is when we go for the other side and clamp the other goal.

    masterChassis.startMainPID({-7.0, 29.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 5000, 500);
    WaitChassisPID();
    masterMogo.retract();




    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(180.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({-26.0, 29.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();


    masterChassis.startMainPID({-47.0, 56.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(100.0);


    masterLift.currentAutonFlag = masterLift.E_AUTOPRIME;
    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(90.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();


    //Move forward and backwards to push ring out of way.

    masterChassis.startMainPID({-47.0, 60.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    AutonWaitFor(2000);

    masterIntake.autonFlag = masterIntake.E_REVERSE_FLAG;
    AutonWaitFor(150);
    masterIntake.autonFlag = masterIntake.E_IDLE_FLAG;



    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(1000);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);
    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;

    masterChassis.startMainPID({-45.0, 50.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(0.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({0.0, 50.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({-15.0, 50.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    //Turns towards the first ring and goes towards it.
    masterChassis.startHeadingPID(90.0, 85.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    WaitChassisPID();

    masterChassis.startMainPID({-15.0, 60.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    masterChassis.startMainPID({0.0, 60.0}, 100.0, true);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 3000, 500);
    WaitChassisPID();

    masterMogo.extend();

    masterChassis.startMainPID({-60.0, 50.0}, 100.0, false);
    masterChassis.distancePID.setExitCondition(2.0, 200.0, 7000, 500);
    WaitChassisPID();



    masterChassis.updateDrive(0, 0);

}