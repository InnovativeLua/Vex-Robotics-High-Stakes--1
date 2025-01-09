//Respective header file for the intake.
#include "headers/mechs/goalTipper.hpp"

/**
 * Runs during operator control code.
 * Makes the tipping mech extend/retract based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void goalTipper::opControl(){
    if (currentTimeout <= 0){ //Only runs until after the timeout has ran its course.
        if (mainController->get_digital(GOALTIPPER_TOGGLE)){
            currentTimeout = ResetTime; //Resets the timeout so it does not activate immediently again.
            if (tipperState == E_ENABLED){ //If tipper is enabled extend, else retract.
                extend();
            } else {
                retract();
            }
        } 
    } else {
        currentTimeout -= 20; //Reduces the timeout by 20 miliseconds.
    }
}

/**
 * Disables the tipping mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::extend(){
    tipperCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    tipperState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the tipping mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::retract(){
    tipperCylinder.set_value(false); //Tells the solenoid to retract the cylinder.
    tipperState = E_ENABLED; //Sets state to enabled.
}

/**
 * Runs during initialization.
 * Does nothing currently.
 * 
 * @return Nothing
 * 
 */
void goalTipper::initialize(){

}

goalTipper masterTipper; //Global master mobile goal mech to be used in other files.