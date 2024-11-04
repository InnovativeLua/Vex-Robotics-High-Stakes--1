//Respective header file for the intake.
#include "headers/mechs/intake.hpp"

/**
 * Sets the current intake velocity.
 *
 * @param targetVelocity(double) velocity to set the intake to.
 * @return Nothing
 * 
 */
void intake::setVelocity(double targetVelocity){
    intakeVelocity = targetVelocity;
}

/**
 * Gets the current intake velocity.
 *
 * @return The current intake velocity.
 * 
 */
double intake::getVelocity(){
    return intakeVelocity;
}

/**
 * Gets the current intake state.
 *
 * @return The current intake state.
 * 
 */
intake::E_intakeStates intake::getCurrentState(){
    return intakeState;
}

/**
 * Runs both the top intake and the bottom intake forward based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void intake::spinForward(){
    intakeMotor.move_velocity(-intakeVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Runs both the top intake and the bottom intake reverse based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void intake::spinReverse(){
    intakeMotor.move_velocity(intakeVelocity); //Sets the intake motor to the current intake velocity.
}

/**
 * Stops both the top intake and the bottom intake.
 *
 * @return Nothing
 * 
 */
void intake::stop(){
    intakeMotor.move_velocity(0); //Stops the intake motors from moving.
}

/**
 * Runs during operator control code.
 * Makes the drivetrain move based on what buttons are being pressed.
 * R1 - Forward
 * R2 - Reverse
 * Down - Intake Redirect
 * 
 * @return Nothing
 * 
 */
void intake::opControl(){
    //Looks at the different states the intake can be in.
    switch(intakeState){ 

    //If the intake is in manual.
    case E_MANUAL:
        if (mainController->get_digital(INTAKE_REDIRECT)){
            //If redirection is activated.
            intakeVelocity = 300.0; //Slows intake to half speed to increase accuracy.
            spinForward(); //Spins the intake forward at the slower speed.
            if (distanceSensor.get_distance() < distanceTargetDistance){ //If the distance sensor detects a ring.
                intakeState = E_RINGDETECTED; //State is changed to ring being detected.
                intakeVelocity = 70.0; //Slows intake even more to 11.7% velocity.
                spinForward(); //Spins the intake forward at the slower speed.
                break; //Stops the manual code underneath from running.
            }
        } else {
            //Sets intake to maximum speed for manual control.
            intakeVelocity = 600.0;
        }
        //looks for press of the respective forward button on the controller.
        if (mainController->get_digital(INTAKE_FORWARD)){
            spinForward();
        //looks for press of the respective reverse button on the controller.
        } else if (mainController->get_digital(INTAKE_REVERSE)){ //looks for press of R2 on controller.
            spinReverse();
        } else {
            //If neither is pressed it stops the intake.
            stop();
        }
        break;
    
    //If a ring has just been detected, waiting until ring has left the distance sensor.
    case E_RINGDETECTED:
        //Checks if the ring is no longer being deteced by the distance sensor.
        if (distanceSensor.get_distance() > distanceTargetDistance){
            intakeState = E_RINGLEFTWAITING; //Changes the state to ring having left.
            currentDelay = 0; //Resets the delay for the time before the intake starts reversing.
        }

    //If the ring has been deteced and is waiting to reverse.
    case E_RINGLEFTWAITING:
        //Checks if the currentDelay is larger than the time alloted for waiting.
        if (currentDelay > afterDelay){
            intakeVelocity = 300; //Increases speed of intake to 50% for reversing.
            spinReverse(); //Updates the motor with the 50% speed and reverses it.
            intakeState = E_REVERSING; //Sets the state to reversing.
            currentDelay = 0; //Resets the delay so it can be used for the reversing time.
        } else {
            currentDelay += 20; //If not enough time has passed then it adds to the timer.
        }

    //If the intake is to be reversing automatically.
    case E_REVERSING:
        //Checks if the currentDelay is larger than the alloted time for reversing.
        if (currentDelay > reversingTime){
            stop(); //Stops the intake.
            currentDelay = 0; //Resets the timer.
            intakeState = E_MANUAL; //Sets the intake state back to manual.
            intakeVelocity = 600.0; //Sets the intake speed to maximum.
        } else {
            intakeVelocity = 300.0; //If the time alloted has not exceeded, sets velocity to 50%.
            currentDelay += 20; //Adds to the timer.
            spinReverse(); //Updates the speed of the motor and reverses it.
        }
    }

}

/**
 * Runs during initialization.
 * Sets all the motors to the correct gearing, brake modes, and encoder units.
 * 
 * @return Nothing
 * 
 */
void intake::initalize(){

	//Sets the intake motors to the correct gearing, brake mode, and encoder units.
    intakeMotor.set_gearing(pros::E_MOTOR_GEARSET_06); //High Speed Motor
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    intakeState = E_MANUAL; //Default intake state is idle.
}

intake masterIntake; //Global main intake to use the intake in other files.