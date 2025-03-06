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
    masterChassis.startMainPID({10.0, 0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();

    masterChassis.updateDrive(0, 0);
    masterLift.currentAutonFlag = masterLift.E_AUTOFORWARD;
    AutonWaitFor(750);
    masterLift.currentAutonFlag = masterLift.E_AUTOIDLE;
    AutonWaitFor(500);

    //Reversses after scoring.
    masterChassis.startMainPID({-30.0, -6.0}, 127.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();
    masterMogo.retract();
    AutonWaitFor(500);

    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    masterChassis.startMainPID({-40.0, 17.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();
    masterChassis.updateDrive(0, 0);        


    //Ring Stack;
    masterChassis.startMainPID({4.0, -12.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();
    masterChassis.updateDrive(0, 0);   

    masterChassis.startMainPID({4.0, -16.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID();
    masterChassis.updateDrive(0, 0); 
    

    //Turns and heads towards the mobile goal, grabbing it.
    masterChassis.startHeadingPID(90.0, 100.0);
    masterChassis.headingPID.setExitCondition(0.01, 500.0, 3000, 300);
    masterMogo.extend();
    WaitChassisPID();

    masterChassis.startMainPID({3.0, -35.0}, 127.0, true);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID(); 

    masterMogo.retract();
    AutonWaitFor(500);

    masterChassis.startMainPID({20.0, -58.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID(); 

    masterChassis.startMainPID({-15.0, -15.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 5000, 500);
    WaitChassisPID(); 

    masterChassis.updateDrive(0, 0);  
}