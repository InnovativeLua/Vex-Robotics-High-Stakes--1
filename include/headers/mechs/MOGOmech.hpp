#pragma once
#include <vector>
#include "main.h"
#include "headers/brain/ports.hpp"

class mogoMech {

 public:

	pros::adi::DigitalOut mogoMechCylinder = pros::adi::DigitalOut(MOGO_MECH_SOLENOID);


    enum E_mogoMechStates { //Different states the PTO can be in.
        E_ENABLED, //Enabled / Extended
        E_DISABLED, //Disabled / Retracted
    };


    bool driverControlPeriod;

    E_mogoMechStates mogoMechState;

    void opControl();
    void extend();
    void retract();
    void initialize();
};

extern mogoMech masterMogo;