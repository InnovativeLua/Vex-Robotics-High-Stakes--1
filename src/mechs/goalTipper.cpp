//Respective header file for the intake.
#include "headers/mechs/goalTipper.hpp"

/**
 * Runs during operator control code.
 * Makes the mogo mech extend/retract based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void goalTipper::opControl(){
    if (currentTimeout <= 0){
        if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            currentTimeout = ResetTime;
            if (tipperState == E_ENABLED){
                extend();
            } else {
                retract();
            }
        } 
    } else {
        currentTimeout -= 20;
    }
}

/**
 * Disables the mobile goal mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::extend(){
    tipperCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    tipperState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the mobile goal mech.
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