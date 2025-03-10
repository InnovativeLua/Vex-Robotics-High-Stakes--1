#pragma once

//Required vex header.
#include "main.h"

//A global unique_ptr to be used by any file to access the main controller.
extern std::unique_ptr<pros::Controller> mainController;

//Buttons to be used by each mechanism.
constexpr pros::controller_digital_e_t INTAKE_FORWARD = pros::E_CONTROLLER_DIGITAL_R1; //R1
constexpr pros::controller_digital_e_t INTAKE_REVERSE = pros::E_CONTROLLER_DIGITAL_R2; //R2
constexpr pros::controller_digital_e_t LIFT_FORWARD = pros::E_CONTROLLER_DIGITAL_L2; //R1
constexpr pros::controller_digital_e_t LIFT_REVERSE = pros::E_CONTROLLER_DIGITAL_L1; //R2
constexpr pros::controller_digital_e_t LIFT_RESET = pros::E_CONTROLLER_DIGITAL_DOWN; //R2
constexpr pros::controller_digital_e_t GOALTIPPER_TOGGLE = pros::E_CONTROLLER_DIGITAL_X;
constexpr pros::controller_digital_e_t EXTENSION_TOGGLE = pros::E_CONTROLLER_DIGITAL_B;
constexpr pros::controller_digital_e_t MOGO_TOGGLE = pros::E_CONTROLLER_DIGITAL_A;
constexpr pros::controller_digital_e_t HANG_TOGGLE = pros::E_CONTROLLER_DIGITAL_DOWN;
constexpr pros::controller_digital_e_t PTO_TOGGLE = pros::E_CONTROLLER_DIGITAL_UP;
constexpr pros::controller_digital_e_t INTAKE_LOWERSTAGE_FORWARD = pros::E_CONTROLLER_DIGITAL_RIGHT;
constexpr pros::controller_digital_e_t INTAKE_LOWERSTAGE_REVERSE = pros::E_CONTROLLER_DIGITAL_LEFT;