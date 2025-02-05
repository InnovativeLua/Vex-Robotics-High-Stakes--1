#pragma once
#include "main.h"
//Header which includes all the ports.
//Ports with a negative number correspond to reversing the motor.

//Motors
constexpr int RIGHT_FRONT_MOTOR = 7;
constexpr int RIGHT_TOP_MOTOR = -10;
constexpr int RIGHT_BACK_MOTOR = 9;
constexpr int LEFT_FRONT_MOTOR = -4;
constexpr int LEFT_TOP_MOTOR = 1;
constexpr int LEFT_BACK_MOTOR = -3;
constexpr int LIFT_MOTOR = -20;
constexpr int INTAKEMOTOR = 19;
constexpr int INTAKEMOTOR2 = 18;

//Sensors
constexpr int INTAKE_OPTICAL = 17;
constexpr int ODOMETRY_INERTIAL = 12;
constexpr char ODOMETRY_AUX = 16;
constexpr char ODOMETRY_LEFT = 13;
constexpr char LIFT_TRACKER = -15;
constexpr char LIFT_TOP = 'H';
constexpr char LIFT_BOTTOM = 'G';
constexpr char AUTON_POT = 'A';

//Solenoids
constexpr char MOGO_MECH_SOLENOID = 'B';
constexpr char TIPPER_SOLENOID_ADI = 'A';    //Should be C, changed for now.
constexpr int TIPPER_SOLENOID_SMART = 13;
constexpr char EXTENSION_SOLENOID_ADI = 'B';    //Should be C, changed for now.
constexpr int EXTENSION_SOLENOID_SMART = 13;
