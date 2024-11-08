#pragma once

//Required vex library.
#include "main.h"

//Custom headers.
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"

class mogoMech {

 public:

    //Solenoid definition with the respective ports defined in the ports.hpp file.
	pros::adi::DigitalOut mogoMechCylinder = pros::adi::DigitalOut(MOGO_MECH_SOLENOID);

    //Enum for each state of the MOGO states.
    enum E_mogoMechStates { //Different states the PTO can be in.
        E_ENABLED, //Enabled / Extended
        E_DISABLED, //Disabled / Retracted
    };

    /**
     * Runs during operator control code.
     * Makes the mogo mech extend/retract based on what buttons are being pressed.
     * 
     * @return Nothing
     * 
     */
    void opControl();

    /**
     * Disables the mobile goal mech.
     * 
     * @return Nothing
     * 
     */
    void extend();

    /**
     * Enables the mobile goal mech.
     * 
     * @return Nothing
     * 
     */
    void retract();

    /**
     * Runs during initialization.
     * Does nothing currently.
     * 
     * @return Nothing
     * 
     */
    void initialize();
    
private:
    int ResetTime = 500; //Constant, the time it takes until the MOGO's state can be changed.
    int currentTimeout = 0; //Current time until the MOGO has reached the time it can reset.
    E_mogoMechStates mogoMechState; //Current state the MOGO is in.
};

extern mogoMech masterMogo; //Global master mobile goal mech to be used in other files.