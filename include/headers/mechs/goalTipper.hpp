#pragma once

//Required vex library.
#include "main.h"
#include <string>
#include <cstdint>
#include <utility>

//Custom headers.<
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"

class goalTipper {
 public:

    //Solenoid definition with the respective ports defined in the ports.hpp file.

	pros::adi::ext_adi_port_pair_t portpairExtension = pros::adi::ext_adi_port_pair_t(EXTENSION_SOLENOID_SMART, EXTENSION_SOLENOID_ADI);
	pros::adi::ext_adi_port_pair_t portpairTipper = pros::adi::ext_adi_port_pair_t(TIPPER_SOLENOID_SMART, TIPPER_SOLENOID_ADI);

	pros::adi::DigitalOut tipperCylinder = pros::adi::DigitalOut(portpairTipper);
	pros::adi::DigitalOut extensionCylinder = pros::adi::DigitalOut(portpairExtension);
    
    //Enum for each state of the tipping states.
    enum E_tipperStates { //Different states the tipper can be in.
        E_ENABLED, //Enabled / Extended
        E_DISABLED, //Disabled / Retracted
    };

    /**
     * Runs during operator control code.
     * Makes the goal tipping mech extend/retract based on what buttons are being pressed.
     * 
     * @return Nothing
     * 
     */
    void opControl();

    /**
     * Disables the goal tipping mech.
     * 
     * @return Nothing
     * 
     */
    void extendTipper();

    /**
     * Enables the goal tipping mech.
     * 
     * @return Nothing
     * 
     */
    void retractTipper();

    /**
     * Disables the extension mech.
     * 
     * @return Nothing
     * 
     */
    void extendExtension();

    /**
     * Enables the extension mech.
     * 
     * @return Nothing
     * 
     */
    void retractExtension();

    /**
     * Runs during initialization.
     * Does nothing currently.
     * 
     * @return Nothing
     * 
     */
    void initialize();

private:
    int resetTimeTipper = 500; //Constant, the time it takes until the tipper's state can be changed.
    int resetTimeExtension = 500; //Constant, the time it takes until the extensions's state can be changed.
    int currentTipperTimeout = 0; //Current time until the tipper has reached the time it can reset.
    int currentExtensionTimeout = 0; //Current time until the extension has reached the time it can reset.
    E_tipperStates tipperState; //Current state the tipper is in.
    E_tipperStates extensionState; //Current state the tipper is in.
};

extern goalTipper masterTipper; //Global main tipper to use the tipper in other files.