#include "main.h"
#include "custom/brain/controller.hpp"
#include "custom/mechs/intake.hpp"

void intake::opControl(){
    switch(intakeState){ //Looks at the different states the intake can be in.
    case E_MANUAL: //If the catapult is in manual state, part of the manual control system.
        if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
            spinForward(); //Spins the intake motor forwards.
        } else if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
            spinReverse(); //Spins the intake motor reverse.
        } else {
            stop(); //stops the intake motor.
        }
        break; //Breaks out of the switch statement.
    
    case E_IDLE: //If the catapult is in idle state, part of the toggle control system.
        stop(); //stops the intake motor.
        if (toggleDB > 100){
            if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
                intakeState = E_INTAKING; //Sets the state of the intake to be intaking
                toggleDB = 0; //Resets the toggleDB clock.
                spinForward(); //Spins the intake motor forwards.
            } else if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
                intakeState = E_OUTTAKING; //Sets the state of the intake to be outtaking
                toggleDB = 0; //Resets the toggleDB clock.
                spinReverse(); //Spins the intake motor reverse.
            }
        }
        break; //Breaks out of the switch statement.

    case E_INTAKING: //If the catapult is in intaking state, part of the toggle control system.
        spinForward(); //Spins the intake motor forwards.
        if (toggleDB > 100){
            if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
                intakeState = E_IDLE; //Sets the state of the intake to be idle
                toggleDB = 0; //Resets the toggleDB clock.
                stop(); //stops the intake motor.
            } else if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
                intakeState = E_OUTTAKING; //Sets the state of the intake to be outtaking.
                toggleDB = 0; //Resets the toggleDB clock.
                spinReverse(); //Spins the intake motor reverse.
            }
        }
        break; //Breaks out of the switch statement.

    case E_OUTTAKING: //If the catapult is in outtaking state, part of the toggle control system.
        spinReverse(); //Spins the intake motor reverse.
        if (toggleDB > 100){
            if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //looks for press of R1 on controller.
                intakeState = E_INTAKING; //Sets the state of the intake to be intaking.
                toggleDB = 0; //Resets the toggleDB clock.
                spinForward(); //Spins the intake motor forwards.
            } else if (mainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){ //looks for press of R2 on controller.
                intakeState = E_IDLE; //Sets the state of the intake to be idle.
                toggleDB = 0; //Resets the toggleDB clock.
                stop(); //stops the intake motor.
            }
        }
        break; //Breaks out of the switch statement.
    toggleDB += 10; ////Steps the toggleDB clock by 10 miliseconds.
    }
}

 //Function when called spins the intake forwards.
void intake::spinForward(){
    intakeMotor.move_velocity(200); //Sets the intake motor to 100 velocity or 50% speed.
}

 //Function when called spins the intake reverse.
void intake::spinReverse(){
    intakeMotor.move_velocity(-200); //Sets the intake motor to -100 velocity or -50% speed.
}

//Function when called stops the intake from moving.
void intake::stop(){
    intakeMotor.move_velocity(0); //Stops the intake motor from moving.
}

intake masterIntake; //Defines the global intake object for other files to use.