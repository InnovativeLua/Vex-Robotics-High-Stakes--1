#include "headers/brain/autonfunctions.hpp"
#include "headers/mechs/chassis/odometry.hpp"
#include "headers/mechs/chassis/chassisPID.hpp"

void AutonWaitFor(int MSTime){
    while (MSTime > 0){
        MSTime -= 10;
        masterOdometry.update();
        masterChassisPID.update();
		pros::delay(10);
    }
}

void WaitChassisPID(){
    while (masterChassisPID.distancePIDActive == true && masterChassisPID.headingPIDActive == true){
        masterOdometry.update();
        masterChassisPID.update();
		pros::delay(10);
    }
}