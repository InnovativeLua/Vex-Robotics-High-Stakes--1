#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void redElimination(){
    masterIntake.autonFlag = masterIntake.E_FORWARD_FLAG;
    AutonWaitFor(10000);
}