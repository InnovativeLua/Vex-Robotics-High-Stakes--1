#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"
#include "headers/mechs/chassis/chassisPID.hpp"


void test(){
    masterChassis.updateLeft(100);
    masterChassis.updateRight(100);
    
    AutonWaitFor(1000);

    masterChassis.updateDrive(0, 0);

    masterChassisPID.setDistancePID(20, 32, 10000, 2, 100);
    WaitChassisPID();

    masterChassisPID.setHeadingPID(50, 5000);
    WaitChassisPID();

    masterChassisPID.setDistancePID(10, 10, 10000, 2, 100);
    AutonWaitFor(1000);
    masterIntake.spinForward();
    AutonWaitFor(1000);
    masterIntake.spinReverse();
    AutonWaitFor(1000);
    masterIntake.stop();
    WaitChassisPID();

    
}