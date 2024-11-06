#pragma once

//Required vex library.
#include "main.h"

//Custom headers.
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"

class lift{
public:

    pros::Motor liftMotor = pros::Motor(LIFT_MOTOR); //Declares a motor for the lift with port "LiftMotor"

    double liftVelocity = 100; //Variable which controls how fast the lift is moving.

    //Control types define what the lift is doing at any point during OPControl.
    enum liftStates {
        E_DISABLED,
        E_IDLE,
        E_MANUAL
    };

    int liftState = E_MANUAL; //The default state currently is manual.

    /**
     * Moves the lift down based on the velocity of the lift.
     *
     * @return Nothing
     * 
     */
    void spinForward();

    /**
     * Moves the lift up based on the velocity of the lift.
     *
     * @return Nothing
     * 
     */
    void spinReverse(); //Function when called spins the lift reverse.

    /**
     * Stops the lift from moving.
     *
     * @return Nothing
     * 
     */
    void stop(); //Function when called stops the lift from moving.

    /**
     * Runs during operator control code.
     * Makes the lift move based on what buttons are being pressed.
     * 
     * @return Nothing
     * 
     */
    void opControl(); //Function called every time the OPControl loop is ran in main.cpp.

    /**
     * Runs during initialization.
     * Sets all the motors to the correct gearing, brake modes, and encoder units.
     * 
     * @return Nothing
     * 
     */
    void initalize();
};

extern lift masterLift; //Global lift object to be accessed by any files.