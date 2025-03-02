#include "headers/brain/autonfunctions.hpp"
#include "headers/mechs/lift.hpp"
#include "headers/mechs/intake.hpp"

void AutonWaitFor(int MSTime){
    while (MSTime > 0){
        masterOdometry.update();
        masterIntake.update(false);
        masterLift.autonUpdate();
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
        pros::screen::erase();
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Position X: %g", masterOdometry.getPosition()[0]);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Position Y: %g", masterOdometry.getPosition()[1]);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "AUX: %i", masterChassis.auxTracker.get_position());
        masterOdometry.update();
        masterIntake.update(false);
        masterLift.autonUpdate();
        if (masterChassis.headingPIDEnabled){
            masterChassis.headingPIDLoop();
        } else if (masterChassis.mainPIDEnabled){
            masterChassis.PIDLoop();
        }
		pros::delay(10);
    }
}