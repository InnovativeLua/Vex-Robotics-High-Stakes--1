#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void blueElimination(){
    masterIntake.spinForward();
    pros::delay(2000);
    masterIntake.stop();
    pros::delay(100000);
}