//Respective header file for the intake.
#include "headers/mechs/lift.hpp"




/**
 * Runs both the top intake and the bottom intake forward based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void lift::spinForward(){
    liftMotor.move_velocity(-liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Runs both the top intake and the bottom intake reverse based on the current intake velocity.
 *
 * @return Nothing
 * 
 */
void lift::spinReverse(){
    liftMotor.move_velocity(liftVelocity); //Sets the intake motor to the current intake velocity in reverse.
}

/**
 * Stops both the top intake and the bottom intake.
 *
 * @return Nothing
 * 
 */
void lift::stop(){
    liftMotor.move_velocity(0.0); //Sets the intake motor to the current intake velocity in reverse.
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
void lift::opControl(){
    //Looks at the different states the intake can be in.
    //For every intake state except for disabled.
    switch(liftState){ 
    case E_MANUAL:
        //looks for press of the respective forward button on the controller.
        if (mainController->get_digital(LIFT_FORWARD)){
            liftVelocity = 90.0;
            spinForward();
        //looks for press of the respective reverse button on the controller.
        } else if (mainController->get_digital(LIFT_REVERSE)){ //looks for press of R2 on controller.
            liftVelocity = 100.0 - liftMotor.get_position()/5;
            spinReverse();
        } else {
            stop();
        }
        break;
    }
}

void lift::liftPFoward(){
    liftVelocity = 100.0 - liftMotor.get_position()/5;
    spinReverse();
}

void lift::liftPReverse(){
    liftVelocity = 50.0;
    spinForward();
}

/**
 * Runs during initialization.
 * Sets all the motors to the correct gearing, brake modes, and encoder units.
 * 
 * @return Nothing
 * 
 */
void lift::initalize(){

	//Sets the intake motors to the correct gearing, brake mode, and encoder units.
    liftMotor.set_gearing(pros::E_MOTOR_GEARSET_36);
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);


    liftState = E_MANUAL; //Default intake state is idle.
}

lift masterLift; //Global main intake to use the intake in other files.