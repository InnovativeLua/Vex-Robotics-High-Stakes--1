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
    if (currentTipperTimeout <= 0){ //Only runs until after the timeout has ran its course.
        if (mainController->get_digital(GOALTIPPER_TOGGLE)){
            currentTipperTimeout = resetTimeTipper; //Resets the timeout so it does not activate immediently again.
            if (tipperState == E_ENABLED){ //If tipper is enabled extend, else retract.
                extendTipper();
            } else {
                retractTipper();
            }
        } 
    } else {
        currentTipperTimeout -= 20; //Reduces the timeout by 20 miliseconds.
    }

    //Exact same thing but for the extension instead of just the tipper.
    if (currentExtensionTimeout <= 0){ //Only runs until after the timeout has ran its course.
        if (mainController->get_digital(EXTENSION_TOGGLE)){
            currentExtensionTimeout = resetTimeExtension; //Resets the timeout so it does not activate immediently again.
            if (extensionState == E_ENABLED){ //If extension is enabled extend, else retract.
                extendExtension();
            } else {
                retractExtension();
            }
        } 
    } else {
        currentTipperTimeout -= 20; //Reduces the timeout by 20 miliseconds.
    }
}

/**
 * Disables the tipping mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::extendTipper(){
    tipperCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    tipperState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the tipping mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::retractTipper(){
    tipperCylinder.set_value(false); //Tells the solenoid to retract the cylinder.
    tipperState = E_ENABLED; //Sets state to enabled.
}

/**
 * Disables the extension mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::extendExtension(){
    extensionCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    extensionState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the extension mech.
 * 
 * @return Nothing
 * 
 */
void goalTipper::retractExtension(){
    extensionCylinder.set_value(false); //Tells the solenoid to retract the cylinder.
    extensionState = E_ENABLED; //Sets state to enabled.
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