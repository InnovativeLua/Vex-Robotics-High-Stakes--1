#include "main.h"
#include "headers/brain/controller.hpp"
#include "headers/mechs/lift.hpp"

void lift::initalize(){
    liftMotor.set_gearing(pros::E_MOTOR_GEARSET_06);
    liftMotor.set_reversed(false);
    liftMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
}

void lift::opControl(){
    switch(liftState){ //Looks at the different states the lift can be in.
    case E_MANUAL: //If the catapult is in manual state, part of the manual control system.
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
            spinForward(); //Spins the lift motor forwards.
        } else if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
            spinReverse(); //Spins the lift motor reverse.
        } else {
            stop(); //stops the lift motor.
        }
        break; //Breaks out of the switch statement.
    toggleDB += 10; ////Steps the toggleDB clock by 10 miliseconds.
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