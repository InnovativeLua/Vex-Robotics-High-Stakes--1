#pragma once

//Required vex header.
#include "main.h"

//A global unique_ptr to be used by any file to access the main controller.
extern std::unique_ptr<pros::Controller> mainController;

//Buttons to be used by each mechanism.
constexpr pros::controller_digital_e_t INTAKE_FORWARD = pros::E_CONTROLLER_DIGITAL_R1; //R1
constexpr pros::controller_digital_e_t INTAKE_REVERSE = pros::E_CONTROLLER_DIGITAL_R2; //R2
constexpr pros::controller_digital_e_t INTAKE_SLOW = pros::E_CONTROLLER_DIGITAL_DOWN; //Left Button
constexpr pros::controller_digital_e_t LIFT_FORWARD = pros::E_CONTROLLER_DIGITAL_L1; //R1
constexpr pros::controller_digital_e_t LIFT_REVERSE = pros::E_CONTROLLER_DIGITAL_L2; //R2