#pragma once

//Required vex library.
#include "main.h"
#include <string>
#include <cstdint>
#include <utility>

//Custom headers.<
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"


class hangMech {
 public:

    //Solenoid definition with the respective ports defined in the ports.hpp file.

	//pros::adi::ext_adi_port_pair_t portpairExtension = pros::adi::ext_adi_port_pair_t(EXTENSION_SOLENOID_SMART, EXTENSION_SOLENOID_ADI);
	//pros::adi::ext_adi_port_pair_t portpairTipper = pros::adi::ext_adi_port_pair_t(TIPPER_SOLENOID_SMART, TIPPER_SOLENOID_ADI);

	pros::adi::DigitalOut hangCylinder = pros::adi::DigitalOut(HANG_SOLENOID_ADI);
	pros::adi::DigitalOut PTOCylinder = pros::adi::DigitalOut(PTO_SOLENOID_ADI);
    
    //Enum for each state of the tipping states.
    enum E_HANGSTATES { //Different states the tipper can be in.
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
    void extendHang();

    /**
     * Enables the goal tipping mech.
     * 
     * @return Nothing
     * 
     */
    void retractHang();

    /**
     * Disables the extension mech.
     * 
     * @return Nothing
     * 
     */
    void extendPTO();

    /**
     * Enables the extension mech.
     * 
     * @return Nothing
     * 
     */
    void retractPTO();

    /**
     * Runs during initialization.
     * Does nothing currently.
     * 
     * @return Nothing
     * 
     */
    void initialize();

private:
    int resetTimePTO = 500; //Constant, the time it takes until the tipper's state can be changed.
    int resetTimeHang = 500; //Constant, the time it takes until the extensions's state can be changed.
    int currentHangTimeout = 0; //Current time until the tipper has reached the time it can reset.
    int currentPTOTimeout = 0; //Current time until the extension has reached the time it can reset.
    E_HANGSTATES hangState; //Current state the tipper is in.
    E_HANGSTATES PTOState; //Current state the tipper is in.
};

extern hangMech masterHang; //Global main tipper to use the tipper in other files.