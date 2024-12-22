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
    intakeMotor2.move_velocity(-intakeVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Runs both the top intake and the bottom intake reverse based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void intake::spinReverse(){
    intakeMotor.move_velocity(intakeVelocity); //Sets the intake motor to the current intake velocity.
    intakeMotor2.move_velocity(intakeVelocity); //Stops the intake motors from moving.
}

/**
 * Stops both the top intake and the bottom intake.
 *
 * @return Nothing
 * 
 */
void intake::stop(){
    intakeMotor.move_velocity(0); //Stops the intake motors from moving.
    intakeMotor2.move_velocity(0); //Stops the intake motors from moving.
}

void intake::detectJam(){
    int deltaEncoderTick = abs(lastEncoderTick - intakeMotor.get_position());
    if (deltaEncoderTick < lowEncoderTickRate && mainController->get_digital(INTAKE_FORWARD)){
        std::cout << "Intake jam detected, correction occuring" << std::endl;
        intakeMotor.move_velocity(-600);
    }
}

/**
 * Runs during operator control code.
 * Makes the intake move based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void intake::opControl(){
    if (mainController->get_digital(INTAKE_LIFT)){ //looks for press of R2 on controller.
        intakeCylinder.set_value(false);
    } else {
        //If neither is pressed it stops the intake.
        intakeCylinder.set_value(true);
    }

    //Looks at the different states the intake can be in.
    switch(intakeState){ 

    //If the intake is in manual.
    case E_MANUAL:
        //looks for press of the respective forward button on the controller.
        if (intakeOptical.get_hue() > redRangeBottom && intakeOptical.get_hue() < redRangeTop){ //If the distance sensor detects a ring.
            intakeState = E_RINGDETECTED; //State is changed to ring being detected.
            break; //Stops the manual code underneath from running.
        }
        if (mainController->get_digital(INTAKE_FORWARD)){
            spinForward();
        //looks for press of the respective reverse button on the controller.
        } else if (mainController->get_digital(INTAKE_REVERSE)){ //looks for press of R2 on controller.
            spinReverse();
        } else {
            //If neither is pressed it stops the intake.
            stop();
        }
        detectJam();
        break;
    
    //If a ring has just been detected, waiting until ring has left the distance sensor.
    case E_RINGDETECTED:
        //Checks if the ring is no longer being deteced by the distance sensor.
        if (intakeOptical.get_hue() < redRangeBottom || intakeOptical.get_hue() > redRangeTop){
            intakeState = E_RINGLEFTWAITING; //Changes the state to ring having left.
            currentDelay = 0; //Resets the delay for the time before the intake starts reversing.
        }

    //If the ring has been deteced and is waiting to reverse.
    case E_RINGLEFTWAITING:
        //Checks if the currentDelay is larger than the time alloted for waiting.
        if (currentDelay > afterDelay){
            stop(); //Updates the motor with the 50% speed and reverses it.
            intakeState = E_REVERSING; //Sets the state to reversing.
            currentDelay = 0; //Resets the delay so it can be used for the reversing time.
        } else {
            currentDelay += 20; //If not enough time has passed then it adds to the timer.
        }

    //If the intake is to be reversing automatically.
    case E_REVERSING:
        stop(); //Updates the motor with the 50% speed and reverses it.
        //Checks if the currentDelay is larger than the alloted time for reversing.
        if (currentDelay > reversingTime){
            stop(); //Stops the intake.
            currentDelay = 0; //Resets the timer.
            intakeState = E_MANUAL; //Sets the intake state back to manual.
            intakeVelocity = 600.0; //Sets the intake speed to maximum.
        }
    case E_REVERSE:
        intakeVelocity = 600.0; //Sets the intake speed to maximum.
        spinReverse(); //Updates the speed of the motor and reverses it.
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

    intakeMotor2.set_gearing(pros::E_MOTOR_GEARSET_18); //High Speed Motor
    intakeMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor2.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    intakeState = E_MANUAL; //Default intake state is idle.
    intakeDetectionState = E_EJECTBOTH;
}

intake masterIntake; //Global main intake to use the intake in other files.