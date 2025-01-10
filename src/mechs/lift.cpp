//Respective header file for the lift.
#include "headers/mechs/lift.hpp"
#include "headers/mechs/intake.hpp"

/**
 * Moves the lift motor forward based on the velocity of the lift.
 *
 * @return Nothing
 * 
 */
void lift::spinForward(){
    //Protecting the motor from sending too high of a voltage, maximum is 200.
    if (liftVelocity > 200){
        liftVelocity = 200;
    } else if (liftVelocity < -200){
        liftVelocity = -200;
    }
    liftMotor.move_velocity(-liftVelocity); //Sets the lift motor to the current lift velocity in reverse.
}

/**
 * Moves the lift motor reverse based on the velocity of the lift.
 *
 * @return Nothing
 * 
 */
void lift::spinReverse(){
    //Protecting the motor from sending too high of a voltage, maximum is 200.
    if (liftVelocity > 200){
        liftVelocity = 200;
    } else if (liftVelocity < -200){
        liftVelocity = -200;
    }
    liftMotor.move_velocity(liftVelocity); //Sets the lift motor to the current lift velocity in reverse.
}

/**
 * Stops the lift from moving.
 *
 * @return Nothing
 * 
 */
void lift::stop(){
    liftMotor.move_velocity(0.0); //Stops the lift motor.
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
    switch(liftState){ 
    //For the manual state.
    case E_MANUAL:
        //looks for press of the respective forward button on the controller.
        if (mainController->get_digital(LIFT_REVERSE)){  //looks for press of reverse on the controller.
            spinReverse();
        //looks for press of the respective reverse button on the controller.
        } else if (mainController->get_digital(LIFT_FORWARD)){ //looks for press of forward on the controller.
            spinForward();
        } else {
            stop();
        }
        break;
    //For the idle state.
    case (E_IDLE):
        if (mainController->get_digital(LIFT_FORWARD)){ //looks for press of the prime button on the controller.
            liftState = E_PRIMED; //Changes state to primed
            //Reset liftPID and setting the speed in terms of P and D values:
            liftPID.resetVariables();
            liftPID.setConstants(0.3, 0.000, 0.0, 0);

            liftPID.setTarget(primedPosition);
            break;
        }
        if (liftTracker.get_value() < idleCoastPosition){ //Protection for motor as to not overheat.
            liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); //Releases the hold of the motor.
            liftVelocity = 0; //Sets the lift velocity to zero to make the lift fall.
        } else {
            liftVelocity = liftPID.compute(liftTracker.get_value()); //Computes the velocity of the lift based on the encoder value.
            spinForward(); //Updates the motor as to start moving.
        }
        break;
    //For the primed state.
    case (E_PRIMED):
        liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //Makes the motor hold its position.
        if (mainController->get_digital(LIFT_REVERSE)){ //Looks for press of the actviation on the controller.
            liftState = E_FORWARD;  //Changes state to activated
            //Reset liftPID and setting the speed in terms of P and D values:
            liftPID.resetVariables();
            liftPID.setConstants(1.0, 0.000, 0.0, 0);
            
            liftPID.setTarget(forwardPosition);
            reverseTimer = 0;
            intakeReverseFlag = true;
        }
        liftVelocity = liftPID.compute(liftTracker.get_value()); //Computes the velocity of the lift based on the encoder value.
        spinForward(); //Updates the motor as to start moving.
        break;
    //For the forwarded state.
    case (E_FORWARD):
        if (mainController->get_digital(LIFT_RESET)){ //Looks for press of the reset on the controller.
            liftState = E_IDLE;  //Changes state to activated
            liftPID.resetVariables(); //Reset liftPID.
            liftPID.setTarget(idlePosition); //Targets the PID to the starting position.
        }
        if (intakeReverseFlag == true){
            if (reverseTimer > maxReverseTime){
                intakeReverseFlag = false;
            }
            reverseTimer += 10;
        }
        liftVelocity = liftPID.compute(liftTracker.get_value()); //Computes the velocity of the lift based on the encoder value.
        spinForward(); //Updates the motor as to start moving.
        break;
    }
}

void lift::autonUpdate(){
    //Looks at the different states the lift can be in.
    switch(liftState){ 
    //For the manual state.
    case (E_IDLE):
        if (currentAutonFlag == E_AUTOPRIME){//looks for press of the prime button on the controller.
            liftState = E_PRIMED; //Changes state to primed
            //Reset liftPID and setting the speed in terms of P and D values:
            liftPID.resetVariables();
            liftPID.setConstants(0.3, 0.000, 0.0, 0);

            liftPID.setTarget(primedPosition);
            break;
        }
        if (liftTracker.get_value() < idleCoastPosition){ //Protection for motor as to not overheat.
            liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); //Releases the hold of the motor.
            liftVelocity = 0; //Sets the lift velocity to zero to make the lift fall.
        } else {
            liftVelocity = liftPID.compute(liftTracker.get_value()); //Computes the velocity of the lift based on the encoder value.
            spinForward(); //Updates the motor as to start moving.
        }
        break;
    //For the primed state.
    case (E_PRIMED):
        liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); //Makes the motor hold its position.
        if ((currentAutonFlag == E_AUTOFORWARD)){ //Looks for press of the actviation on the controller.
            liftState = E_FORWARD;  //Changes state to activated
            //Reset liftPID and setting the speed in terms of P and D values:
            liftPID.resetVariables();
            liftPID.setConstants(1.0, 0.000, 0.0, 0);
            
            liftPID.setTarget(forwardPosition);
            reverseTimer = 0;
            intakeReverseFlag = true;
        }
        liftVelocity = liftPID.compute(liftTracker.get_value()); //Computes the velocity of the lift based on the encoder value.
        spinForward(); //Updates the motor as to start moving.
        break;
    //For the forwarded state.
    case (E_FORWARD):
        if (currentAutonFlag == E_AUTOIDLE){ //Looks for press of the reset on the controller.
            liftState = E_IDLE;  //Changes state to activated
            liftPID.resetVariables(); //Reset liftPID.
            liftPID.setTarget(idlePosition); //Targets the PID to the starting position.
        }
        if (intakeReverseFlag == true){
            masterIntake.spinReverse();
            if (reverseTimer > maxReverseTime){
                masterIntake.stop();
                intakeReverseFlag = false;
            }
            reverseTimer += 10;
        }
        liftVelocity = liftPID.compute(liftTracker.get_value()); //Computes the velocity of the lift based on the encoder value.
        spinForward(); //Updates the motor as to start moving.
        break;
    }
}

/**
 * Runs during initialization.
 * Sets the motor to the correct gearing, brake modes, and encoder units.
 * Sets up the PID and sensor.
 * 
 * @return Nothing
 * 
 */
void lift::initalize(){

	//Setsthe lift motor to the correct gearing, brake mode, and encoder units.
    liftMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

    liftState = E_IDLE; //Default lift state is idle.
    liftPID.resetVariables(); 
    liftPID.setExitCondition(0.0, 100000.0, 1000000, 1000000); //(Unnecessary), sets the lift PID to never end.
    liftPID.setTarget(idlePosition); //The default position for the lift.

    liftTracker.reset(); //Resets the lift encoder.
}

lift masterLift; //Global main lift to use the lift in other files.