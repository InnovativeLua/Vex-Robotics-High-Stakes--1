#include "headers/auton/autons.hpp"

void redAWP(){
    masterChassis.updateLeft(100);
    masterChassis.updateRight(100);
    
    pros::delay(1000);

    masterChassis.updateDrive(0, 0);
}