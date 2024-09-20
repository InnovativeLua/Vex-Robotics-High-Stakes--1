#pragma once

#include "main.h"
#include "headers/brain/ports.hpp"
class intake{
public:

    //Control types define what the intake is doing at any point during OPControl.
    enum intakeStates {
        E_DISABLED,
        E_MANUALFORWARD,
        E_MANUALREVERSE,
        E_MANUALIDLE,
        E_IDLE
    };

    double intakeVelocity = 200.0;

    int intakeState = E_MANUALIDLE; //The default state currently is manual.

    int toggleDB = 0; //Debounce for the toggle in ms.

    void spinForward(); //Function when called spins the intake forward.

    void initalize();

    void spinReverse(); //Function when called spins the intake reverse.

    void stop(); //Function when called stops the intake from moving.

    void opControl(); //Function called every time the OPControl loop is ran in main.cpp.

    pros::Motor intakeMotor = pros::Motor(INTAKEMOTOR); //Declares a motor for the catapult with port "8"
    pros::Motor intakeMotor2 = pros::Motor(INTAKEMOTOR2); //Declares a motor for the catapult with port "8"

    pros::Optical ringDetector = pros::Optical(RINGDETECTOR);

    double ringDectorMaxHue = 60.0;
    double ringDectorMinHue = 29.0;
};

extern intake masterIntake; //Global intake object to be accessed by any files.