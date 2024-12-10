#pragma once
//Header which includes all the ports.
//Ports with a negative number correspond to reversing the motor.

//Motors
constexpr int RIGHT_FRONT_MOTOR = 1;
constexpr int RIGHT_TOP_MOTOR = -3;
constexpr int RIGHT_BACK_MOTOR = 4;
constexpr int LEFT_FRONT_MOTOR = -5;
constexpr int LEFT_TOP_MOTOR = 6;
constexpr int LEFT_BACK_MOTOR = -7;
constexpr int LIFT_MOTOR = 11;
constexpr int LIFT_MOTOR2 = 12;
constexpr int INTAKEMOTOR = 9;
constexpr int INTAKEMOTOR2 = 10;

//Sensors
constexpr int DISTANCESENSOR = 12;
constexpr int ODOMETRY_INERTIAL = 8;
constexpr char ODOMETRY_AUX_TOP = 'C';
constexpr char ODOMETRY_AUX_BOTTOM = 'D';
constexpr char ODOMETRY_LEFT_TOP = 'F';
constexpr char ODOMETRY_LEFT_BOTTOM = 'B';
constexpr char LIFT_TOP = 'H';
constexpr char LIFT_BOTTOM = 'G';
constexpr char LIFT_ROT = 15;

//Solenoids
constexpr char MOGO_MECH_SOLENOID = 'A';
constexpr char TIPPER_SOLENOID = 'E';   