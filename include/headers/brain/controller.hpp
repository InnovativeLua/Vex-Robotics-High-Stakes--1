#pragma once

//Required vex header.
#include "main.h"

//A global unique_ptr to be used by any file to access the main controller.
extern std::unique_ptr<pros::Controller> mainController;

//Buttons to be used by each mechanism.
constexpr int INTAKE_FORWARD = pros::E_CONTROLLER_DIGITAL_R1; //R1
constexpr int INTAKE_REVERSE = pros::E_CONTROLLER_DIGITAL_R2; //R2
constexpr int LIFT_FORWARD = pros::E_CONTROLLER_DIGITAL_L1; //L1
constexpr int LIFT_REVERSE = pros::E_CONTROLLER_DIGITAL_L2; //L2
constexpr int MOGO_TOGGLE = pros::E_CONTROLLER_DIGITAL_A; //A