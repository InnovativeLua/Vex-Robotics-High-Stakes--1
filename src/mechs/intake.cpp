#include "main.h"
#include "headers/brain/controller.hpp"
#include "headers/mechs/intake.hpp"

void intake::initalize(){
    intakeMotor.set_gearing(pros::E_MOTOR_GEARSET_18);
    intakeMotor.set_reversed(false);
    intakeMotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    intakeState = E_MANUALIDLE;
}

void intake::opControl(){
    switch(intakeState){ //Looks at the different states the intake can be in.
    case E_MANUALFORWARD: //If the catapult is in manual state, part of the manual control system.
    case E_MANUALREVERSE:
    case E_MANUALIDLE:
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
            intakeVelocity = 165.0;
        } else {
            intakeVelocity = 200.0;
        }
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && ((ringDetector.get_hue() < ringDectorMinHue) || (ringDetector.get_hue() > ringDectorMaxHue))){
            spinReverse();
        } else {
            if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
                intakeState = E_MANUALFORWARD;
                spinForward(); //Spins the intake motor forwards.
            } else if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
                intakeState = E_MANUALREVERSE;
                spinReverse(); //Spins the intake motor reverse.
            } else {
                intakeState = E_MANUALIDLE;
                stop(); //stops the intake motor.
            }
            break; //Breaks out of the switch statement.
        }
    }
}

 //Function when called spins the intake forwards.
void intake::spinForward(){
    intakeMotor.move_velocity(-intakeVelocity); //Sets the intake motor to 100 velocity or 50% speed.
    intakeMotor2.move_velocity(-intakeVelocity); //Sets the intake motor to 100 velocity or 50% speed.
}

 //Function when called spins the intake reverse.
void intake::spinReverse(){
    intakeMotor.move_velocity(intakeVelocity); //Sets the intake motor to -100 velocity or -50% speed.
    intakeMotor2.move_velocity(intakeVelocity); //Sets the intake motor to 100 velocity or 50% speed.
}

//Function when called stops the intake from moving.
void intake::stop(){
    intakeMotor.move_velocity(0); //Stops the intake motor from moving.
    intakeMotor2.move_velocity(0); //Sets the intake motor to 100 velocity or 50% speed.
}

intake masterIntake; //Defines the global intake object for other files to use.