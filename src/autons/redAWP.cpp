#include "headers/auton/autons.hpp"
#include "headers/brain/autonfunctions.hpp"

void redAWP(){
    masterIntake.spinForward();
    pros::delay(500);
    masterIntake.stop();
    pros::delay(100000);
}