#include "headers/brain/autonfunctions.hpp"
#include "headers/mechs/lift.hpp"

void AutonWaitFor(int MSTime){
    while (MSTime > 0){
        masterLift.autonUpdate();
        masterOdometry.update();
        if (masterChassis.headingPIDEnabled){
            masterChassis.headingPIDLoop();
        } else if (masterChassis.mainPIDEnabled){
            masterChassis.PIDLoop();
        }
		pros::delay(10);
        MSTime -= 10;
    }
}

void WaitChassisPID(){
    while (masterChassis.mainPIDEnabled == true || masterChassis.headingPIDEnabled == true){
        masterOdometry.update();
        masterLift.autonUpdate();
        if (masterChassis.headingPIDEnabled){
            masterChassis.headingPIDLoop();
        } else if (masterChassis.mainPIDEnabled){
            masterChassis.PIDLoop();
        }
		pros::delay(10);
    }
}