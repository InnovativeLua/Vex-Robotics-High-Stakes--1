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
    pros::adi::Encoder liftTracker = pros::adi::Encoder(LIFT_TOP, LIFT_BOTTOM, false); //Declares an optical encoder.

    double liftVelocity = 200; //Controls how fast the lift is moving.
    int idlePosition = 0; //Default position for the lift to go towards while idle.
    int idleCoastPosition = 60; //Position to make the motor coast as to protect the motor from overheating.
    int primedPosition = 90; //Position for priming the lift.
    int forwardPosition = 400; //Position to target when going to place it onto wall states. Prevents the lift from going over maximum expansion.

    //Control types define what the lift is doing at any point during OPControl.
    enum liftPositions {
        E_DISABLED, //Not going to do anything.
        E_MANUAL, //Controls based on an up and down button.
        E_IDLE, //Goes to default position and waits.
        E_PRIMED, //Primes itself targetting the primed position, waiting for a ring.
        E_FORWARD //Moves the ring forwards, targetting the forward position to get it onto the wall stake.
    };

    liftPositions liftState; //State the lift is currently in.

    bool liftPIDEnabled = false;
    PID liftPID = PID(0.3, 0.000, 0.0, 0, "liftPID"); //Sets the default constants and name for the PID.

    /**
     * Moves the lift motor forward based on the velocity of the lift.
     *
     * @return Nothing
     * 
     */
    void spinForward();

    /**
     * Moves the lift motor reverse based on the velocity of the lift.
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
     * Sets the motor to the correct gearing, brake modes, and encoder units.
     * Sets up the PID and sensor.
     * 
     * @return Nothing
     * 
     */
    void initalize();
};

extern lift masterLift; //Global lift object to be accessed by any files.