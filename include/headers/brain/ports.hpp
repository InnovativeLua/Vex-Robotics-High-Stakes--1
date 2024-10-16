#pragma once
//Header which includes all the ports.
//Ports with a negative number correspond to reversing the motor.

//Motors
constexpr int RIGHT_FRONT_MOTOR = 1;
constexpr int RIGHT_BACK_MOTOR = -3;
constexpr int RIGHT_TOP_MOTOR = 4;
constexpr int LEFT_FRONT_MOTOR = -5;
constexpr int LEFT_BACK_MOTOR = 6;
constexpr int LEFT_TOP_MOTOR = -7;
constexpr int LIFT_MOTOR = 8;
constexpr int INTAKEMOTOR = 9;
constexpr int INTAKEMOTOR2 = -10;

//Sensors
constexpr int RINGDETECTOR = 11;
constexpr char ODOMETRY_AUX_TOP = 'A';
constexpr char ODOMETRY_AUX_BOTTOM = 'B';
constexpr char ODOMETRY_LEFT_TOP = 'C';
constexpr char ODOMETRY_LEFT_BOTTOM = 'D';

//Solenoids
constexpr char MOGO_MECH_SOLENOID = 'G';