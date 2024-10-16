#pragma once

#include "main.h"
#include "headers/brain/ports.hpp"
class lift{
public:

    //Control types define what the intake is doing at any point during OPControl.
    enum liftStates {
        E_DISABLED,
        E_IDLE,
        E_MANUAL
    };

    double liftTargetPosition = 40.0;

    int liftState = E_MANUAL; //The default state currently is manual.

    int toggleDB = 0; //Debounce for the toggle in ms.

    void spinForward(); //Function when called spins the lift forward.

    void initalize();

    void spinReverse(); //Function when called spins the lift reverse.

    void stop(); //Function when called stops the lift from moving.

    void opControl(); //Function called every time the OPControl loop is ran in main.cpp.

    pros::Motor liftMotor = pros::Motor(LIFT_MOTOR); //Declares a motor for the lift with port "IntakeMotor"
};

extern lift masterLift; //Global lift object to be accessed by any files.