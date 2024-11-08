//Required vex library.
#include "main.h"

//Custom headers.
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"

class goalTipper {
 public:

    //Solenoid definition with the respective ports defined in the ports.hpp file.
	pros::adi::DigitalOut tipperCylinder = pros::adi::DigitalOut(TIPPER_SOLENOID);

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
    void extend();

    /**
     * Enables the goal tipping mech.
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
    E_tipperStates tipperState; //Current state the MOGO is in.
};

extern goalTipper masterTipper; //Global main chassis to use the drivetrain in other files.