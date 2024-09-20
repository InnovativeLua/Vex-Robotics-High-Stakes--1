#include "main.h"
#include "headers/brain/controller.hpp"
#include "headers/mechs/lift.hpp"
#include "headers/mechs/intake.hpp"

void lift::initalize(){
    liftMotor.set_gearing(pros::E_MOTOR_GEARSET_36);
    liftMotor.set_reversed(false);
    liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
}

void lift::opControl(){
    switch(liftState){ //Looks at the different states the lift can be in.
    case E_MANUAL: //If the catapult is in manual state, part of the manual control system.
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_L1)){ //looks for press of R1 on controller.
            spinForward(); //Spins the lift motor forwards.
        } else if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_L2)){ //looks for press of R2 on controller.
            spinReverse(); //Spins the lift motor reverse.
        } else {
            stop(); //stops the lift motor.
        }
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
            liftState = E_IDLE;
        }
        break; //Breaks out of the switch statement.
    case E_IDLE: //If the catapult is in manual state, part of the manual control system.
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R1) || mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R1 on controller.
            liftState = E_MANUAL;
        }
        if (masterIntake.intakeState == intake::E_MANUALFORWARD || masterIntake.intakeState == intake::E_MANUALREVERSE){
            liftMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
            if (liftMotor.get_position() < liftTargetPosition){
                //liftMotor.move_velocity(50);
            }
        } else if (masterIntake.intakeState == intake::E_MANUALIDLE || masterIntake.intakeState == intake::E_IDLE){
            liftMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        } else {
            liftMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        }
        break; //Breaks out of the switch statement.
    }
}

 //Function when called spins the lift forwards.
void lift::spinForward(){
    liftMotor.move_velocity(200); //Sets the lift motor to 100 velocity or 50% speed.
}

 //Function when called spins the lift reverse.
void lift::spinReverse(){
    liftMotor.move_velocity(-200); //Sets the lift motor to -100 velocity or -50% speed.
}

//Function when called stops the lift from moving.
void lift::stop(){
    liftMotor.move_velocity(0); //Stops the lift motor from moving.
}

lift masterLift; //Defines the global lift object for other files to use.