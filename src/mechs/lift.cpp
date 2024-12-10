//Respective header file for the lift.
#include "headers/mechs/lift.hpp"

/**
 * Moves the lift down based on the velocity of the lift.
 *
 * @return Nothing
 * 
 */
void lift::spinForward(){
    if (liftVelocity > 200){
        liftVelocity = 200;
    } else if (liftVelocity < -200){
        liftVelocity = -200;
    }
    liftMotor.move_velocity(-liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
    liftMotor2.move_velocity(liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Moves the lift up based on the velocity of the lift.
 *
 * @return Nothing
 * 
 */
void lift::spinReverse(){
    if (liftVelocity > 200){
        liftVelocity = 200;
    } else if (liftVelocity < -200){
        liftVelocity = -200;
    }
    liftMotor.move_velocity(liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
    liftMotor2.move_velocity(-liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Stops the lift from moving.
 *
 * @return Nothing
 * 
 */
void lift::stop(){
    liftMotor.move_velocity(0.0); //Sets the intake motor to the current intake velocity in reverse.
    liftMotor2.move_velocity(0.0); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Runs during operator control code.
 * Makes the lift move based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void lift::opControl(){
    std::cout << "Tracker pos: " << (liftTracker.get_value()) << std::endl;
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
    case (E_IDLE):
        
        if (mainController->get_digital(LIFT_FORWARD)){
            liftState = E_PRIMED;
            liftPID.resetVariables();
            liftPID.setConstants(0.3, 0.000, 0.0, 0);
            liftPID.setTarget(primedPosition);
        }
        if (liftTracker.get_value() < idleCoastPosition){
            liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        } else {
            liftVelocity = liftPID.compute(liftTracker.get_value());
            spinForward();
        }
        break;
    case (E_PRIMED):
        liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        if (mainController->get_digital(LIFT_REVERSE)){
            liftState = E_FORWARD;
            liftPID.resetVariables();
            liftPID.setConstants(1.0, 0.000, 0.0, 0);
            liftPID.setTarget(forwardPosition);
        }
        liftVelocity = liftPID.compute(liftTracker.get_value());
        spinForward();
        break;
    case (E_FORWARD):
        if (mainController->get_digital(LIFT_RESET)){
            liftState = E_IDLE;
            liftPID.resetVariables();
            liftPID.setTarget(idlePosition);
            }
        liftVelocity = liftPID.compute(liftTracker.get_value());
        spinForward();
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
    liftMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    liftMotor2.set_gearing(pros::E_MOTOR_GEARSET_18);
    liftMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    liftMotor2.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);


    liftState = E_IDLE; //Default lift state is idle.
    liftPID.resetVariables();
    liftPID.setExitCondition(0.0, 100000.0, 1000000, 1000000);
    liftPID.setTarget(idlePosition);

    liftRot.reset_position();
    liftMotor.set_zero_position(0.0);
    liftTracker.reset();
}

lift masterLift; //Global main lift to use the lift in other files.