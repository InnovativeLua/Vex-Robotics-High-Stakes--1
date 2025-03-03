#pragma once
#include "main.h"
//Header which includes all the ports.
//Ports with a negative number correspond to reversing the motor.

//Motors
constexpr int RIGHT_FRONT_MOTOR = 1;
constexpr int RIGHT_TOP_MOTOR = 2;
constexpr int RIGHT_BACK_MOTOR = -3;
constexpr int LEFT_FRONT_MOTOR = -4;
constexpr int LEFT_TOP_MOTOR = 6;
constexpr int LEFT_BACK_MOTOR = -5;
constexpr int LIFT_MOTOR = -8;
constexpr int INTAKEMOTOR = -9;
constexpr int INTAKEMOTOR2 = -7;

//Sensors
constexpr int INTAKE_OPTICAL = 14;
constexpr int ODOMETRY_INERTIAL = 13;
constexpr char ODOMETRY_AUX = 11;
constexpr char ODOMETRY_LEFT = 12;
constexpr char LIFT_TRACKER = -10;
constexpr char LIFT_TOP = 'A';
constexpr char LIFT_BOTTOM = 'A';
constexpr char AUTON_POT = 'F';

//Solenoids
constexpr char MOGO_MECH_SOLENOID = 'G';
constexpr char TIPPER_SOLENOID_ADI = 'H';    //Should be C, changed for now.
constexpr int TIPPER_SOLENOID_SMART = 19;
constexpr char EXTENSION_SOLENOID_ADI = 'E';    //Should be C, changed for now.
constexpr int EXTENSION_SOLENOID_SMART = 19;
