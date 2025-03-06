//Respective header file for the tipper.
#include "headers/mechs/hang.hpp"

/**
 * Runs during operator control code.
 * Makes the tipping mech extend/retract based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void hangMech::opControl(){
    if (currentHangTimeout <= 0){ //Only runs until after the timeout has ran its course.
        if (mainController->get_digital(HANG_TOGGLE)){
            currentHangTimeout = resetTimeHang; //Resets the timeout so it does not activate immediently again.
            if (hangState == E_ENABLED){ //If tipper is enabled extend, else retract.
                extendHang();
            } else {
                retractHang();
            }
        } 
    } else {
        currentHangTimeout -= 20; //Reduces the timeout by 20 miliseconds.
    }

    //Exact same thing but for the extension instead of just the tipper.
    if (currentPTOTimeout <= 0){ //Only runs until after the timeout has ran its course.
        if (mainController->get_digital(PTO_TOGGLE)){
            currentPTOTimeout = resetTimePTO; //Resets the timeout so it does not activate immediently again.
            if (PTOState == E_ENABLED){ //If extension is enabled extend, else retract.
                extendPTO();
            } else {
                retractPTO();
            }
        } 
    } else {
        currentPTOTimeout -= 20; //Reduces the timeout by 20 miliseconds.
    }
}

/**
 * Disables the tipping mech.
 * 
 * @return Nothing
 * 
 */
void hangMech::extendHang(){
    hangCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    hangState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the tipping mech.
 * 
 * @return Nothing
 * 
 */
void hangMech::retractHang(){
    hangCylinder.set_value(false); //Tells the solenoid to retract the cylinder.
    hangState = E_ENABLED; //Sets state to enabled.
}

/**
 * Disables the extension mech.
 * 
 * @return Nothing
 * 
 */
void hangMech::extendPTO(){
    PTOCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    PTOState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the extension mech.
 * 
 * @return Nothing
 * 
 */
void hangMech::retractPTO(){
    PTOCylinder.set_value(false); //Tells the solenoid to retract the cylinder.
    PTOState = E_ENABLED; //Sets state to enabled.
}

/**
 * Runs during initialization.
 * Does nothing currently.
 * 
 * @return Nothing
 * 
 */
void hangMech::initialize(){
    
}

hangMech masterHang; //Global master mobile goal mech to be used in other files.