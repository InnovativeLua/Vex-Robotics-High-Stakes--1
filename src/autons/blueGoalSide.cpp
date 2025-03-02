#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueGoalSide(){
    //Init
    masterIntake.stop();
    masterMogo.extend();
    masterTipper.retractTipper();

    //Reversses after scoring.
    masterChassis.startMainPID({20.0, 20.0}, 127.0, false);
    masterChassis.distancePID.setExitCondition(1.0, 200.0, 2000, 500);
    WaitChassisPID();
    masterChassis.updateDrive(0, 0);
}

void wBlueGoalSide(){

}