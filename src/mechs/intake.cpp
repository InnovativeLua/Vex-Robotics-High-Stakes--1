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
    intakeMotor.move_velocity(-intakeVelocity); //Sets the intake motor to 100 velocity or 50% speed.
    intakeMotor2.move_velocity(-intakeVelocity); //Sets the intake motor to 100 velocity or 50% speed.
    intakeState = E_FORWARD;
}

/**
 * Runs both the top intake and the bottom intake reverse based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void intake::spinReverse(){
    intakeMotor.move_velocity(intakeVelocity); //Sets the intake motor to -100 velocity or -50% speed.
    intakeMotor2.move_velocity(intakeVelocity); //Sets the intake motor to 100 velocity or 50% speed.
    intakeState = E_REVERSE;
}

/**
 * Stops both the top intake and the bottom intake.
 *
 * @return Nothing
 * 
 */
void intake::stop(){
    intakeMotor.move_velocity(0); //Stops the intake motor from moving.
    intakeMotor2.move_velocity(0); //Sets the intake motor to 100 velocity or 50% speed.
    intakeState = E_IDLE;
}

/**
 * Runs during operator control code.
 * Makes the drivetrain move based on what buttons are being pressed.
 * R1 - Forward
 * R2 - Reverse
 * 
 * @return Nothing
 * 
 */
void intake::opControl(){
    switch(intakeState){ //Looks at the different states the intake can be in.
    //For every intake state except for disabled it will run the same thing.
    case E_FORWARD:
    case E_REVERSE:
    case E_IDLE:
        //Allows
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
            intakeVelocity = 165.0; //Slows down the intake.
        } else {
            intakeVelocity = 200.0; //Sets the intake to maximum velocity.
        }
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
            spinForward(); //Spins the intake motor forwards.
        } else if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
            spinReverse(); //Spins the intake motor reverse.
        } else {
            stop(); //stops the intake motor.
        }
        break; //Breaks out of the switch statement.
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
    intakeMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    intakeMotor2.set_gearing(pros::E_MOTOR_GEARSET_18);
    intakeMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor2.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    intakeState = E_IDLE;
}

intake masterIntake; //Global main intake to use the intake in other files.