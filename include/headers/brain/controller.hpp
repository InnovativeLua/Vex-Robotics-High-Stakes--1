#pragma once
#include "main.h"
extern std::unique_ptr<pros::Controller> mainController;

constexpr int INTAKE_FORWARD = pros::E_CONTROLLER_DIGITAL_R1;
constexpr int INTAKE_REVERSE = pros::E_CONTROLLER_DIGITAL_R2;
constexpr int LIFT_FORWARD = pros::E_CONTROLLER_DIGITAL_L1;
constexpr int LIFT_REVERSE = pros::E_CONTROLLER_DIGITAL_L2;
constexpr int MOGO_TOGGLE = pros::E_CONTROLLER_DIGITAL_A;