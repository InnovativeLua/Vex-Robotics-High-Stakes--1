//Respective header file for the lift.
#include "headers/mechs/lift.hpp"

/**
 * Moves the lift down based on the velocity of the lift.
 *
 * @return Nothing
 * 
 */
void lift::spinForward(){
    liftMotor.move_velocity(-liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Moves the lift up based on the velocity of the lift.
 *
 * @return Nothing
 * 
 */
void lift::spinReverse(){
    liftMotor.move_velocity(liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Stops the lift from moving.
 *
 * @return Nothing
 * 
 */
void lift::stop(){
    liftMotor.move_velocity(0.0); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Runs during operator control code.
 * Makes the lift move based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void lift::opControl(){
    //Looks at the different states the lift can be in.
    //For the manual state.
    switch(liftState){ 
    case E_MANUAL:
        //looks for press of the respective forward button on the controller.
        if (mainController->get_digital(LIFT_FORWARD)){
            spinReverse();
        //looks for press of the respective reverse button on the controller.
        } else if (mainController->get_digital(LIFT_REVERSE)){ //looks for press of R2 on controller.
            spinForward();
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
void lift::initalize(){

	//Sets the lift motors to the correct gearing, brake mode, and encoder units.
    liftMotor.set_gearing(pros::E_MOTOR_GEARSET_36);
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);


    liftState = E_MANUAL; //Default lift state is idle.
}

lift masterLift; //Global main lift to use the lift in other files.