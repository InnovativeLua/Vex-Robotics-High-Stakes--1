#pragma once

//Required vex library.
#include "main.h"

//Custom headers.
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"
#include "headers/mechs/PID.hpp"

class lift{
public:

    pros::Motor liftMotor = pros::Motor(LIFT_MOTOR); //Declares a motor for the lift with port "LiftMotor"

    double liftVelocity = 100; //Variable which controls how fast the lift is moving.
    int idlePosition = 0;
    int idleCoastPosition = 5;
    int primedPosition = 30;
    int forwardPosition = 250;

    //Control types define what the lift is doing at any point during OPControl.
    enum liftPositions {
        E_DISABLED,
        E_MANUAL,
        E_FORWARD,
        E_IDLE,
        E_PRIMED
    };

    liftPositions liftState = E_IDLE; //The default state currently is manual.

    bool liftPIDEnabled = false;
    PID liftPID = PID(6.0, 0, 0.0, 0, "liftPID");
    pros::Rotation liftRot = pros::Rotation(liftRot);

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