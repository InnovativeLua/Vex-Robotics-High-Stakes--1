//Respective header file for the intake.
#include "headers/mechs/MOGOmech.hpp"

/**
 * Runs during operator control code.
 * Makes the mogo mech extend/retract based on what buttons are being pressed.
 * 
 * @return Nothing
 * 
 */
void mogoMech::opControl(){
    if (currentTimeout <= 0){
        if (mainController->get_digital(MOGO_TOGGLE)){
            currentTimeout = ResetTime;
            if (mogoMechState == E_ENABLED){
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
void mogoMech::extend(){
    mogoMechCylinder.set_value(true); //Tells the solenoid to extend the cylinder.
    mogoMechState = E_DISABLED; //Sets state to disabled.
}

/**
 * Enables the mobile goal mech.
 * 
 * @return Nothing
 * 
 */
void mogoMech::retract(){
    mogoMechCylinder.set_value(false); //Tells the solenoid to retract the cylinder.
    mogoMechState = E_ENABLED; //Sets state to enabled.
}

/**
 * Runs during initialization.
 * Does nothing currently.
 * 
 * @return Nothing
 * 
 */
void mogoMech::initialize(){

}

mogoMech masterMogo; //Global master mobile goal mech to be used in other files.