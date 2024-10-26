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
    intakeMotor2.move_velocity(-intakeVelocity);
    intakeState = E_FORWARD;
}

/**
 * Runs both the top intake and the bottom intake reverse based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void intake::spinReverse(){
    intakeMotor.move_velocity(intakeVelocity); //Sets the intake motor to the current intake velocity.
    intakeMotor2.move_velocity(intakeVelocity);
    intakeState = E_REVERSE;
}

/**
 * Stops both the top intake and the bottom intake.
 *
 * @return Nothing
 * 
 */
void intake::stop(){
    intakeMotor.move_velocity(0); //Stops the intake motors from moving.
    intakeMotor2.move_velocity(0);
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
    //Looks at the different states the intake can be in.
    //For every intake state except for disabled.
    switch(intakeState){ 
    case E_FORWARD:
    case E_REVERSE:
    case E_IDLE:
        //looks for press of the respective slow button on the controller.
        if (mainController->get_digital(INTAKE_SLOW)){
            intakeVelocity = 165.0; //Slows down the intake.
        } else {
            intakeVelocity = 200.0; //Sets the intake to maximum velocity.
        }
        //looks for press of the respective forward button on the controller.
        if (mainController->get_digital(INTAKE_FORWARD)){
            spinForward();
        //looks for press of the respective reverse button on the controller.
        } else if (mainController->get_digital(INTAKE_REVERSE)){ //looks for press of R2 on controller.
            spinReverse();
        } else {
            stop();
        }
        break;
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
    intakeMotor.set_gearing(pros::E_MOTOR_GEARSET_36);
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    intakeMotor2.set_gearing(pros::E_MOTOR_GEARSET_36);
    intakeMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor2.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    intakeState = E_IDLE; //Default intake state is idle.
}

intake masterIntake; //Global main intake to use the intake in other files.