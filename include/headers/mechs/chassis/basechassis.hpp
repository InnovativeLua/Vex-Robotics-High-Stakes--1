#pragma once
#include <vector>
#include "main.h"
#include "headers/brain/ports.hpp"

class chassis {

 public:

    pros::Motor leftFrontMotor = pros::Motor(LEFT_FRONT_MOTOR);
    pros::Motor leftBackMotor = pros::Motor(LEFT_BACK_MOTOR);
    pros::Motor leftTopMotor = pros::Motor(LEFT_TOP_MOTOR);

    pros::Motor rightFrontMotor = pros::Motor(RIGHT_FRONT_MOTOR);
    pros::Motor rightBackMotor = pros::Motor(RIGHT_BACK_MOTOR);
    pros::Motor rightTopMotor = pros::Motor(RIGHT_TOP_MOTOR);

    enum E_driveControl {
        E_ARCADE_CONTROL,
        E_TANK_CONTROL
    };

    enum E_PTO { //Different states the PTO can be in.
        E_PTOTYPE_ENABLED, //Enabled / Extended
        E_PTOTYPE_DISABLED, //Disabled / Retracted
    };

    std::vector<pros::Motor> ActiveLeftMotors = {leftFrontMotor, leftBackMotor, leftTopMotor};
    std::vector<pros::Motor> ActiveRightMotors = {rightFrontMotor, rightBackMotor, rightTopMotor};

    pros::IMU ChassisIMU = pros::IMU(10);

    pros::adi::Encoder leftTracker = pros::adi::Encoder(ODOMETRY_LEFT_BOTTOM, ODOMETRY_LEFT_TOP);
    pros::adi::Encoder auxTracker = pros::adi::Encoder(ODOMETRY_AUX_BOTTOM, ODOMETRY_AUX_TOP);

    bool driverControlPeriod;

    E_driveControl driveControl;
    E_PTO PTOControl;

    bool PTODB;
    bool PTOValue;

    pros::adi::DigitalOut PTOPistons = pros::adi::DigitalOut('G'); //Pnemautic cylinder object / right wing in the A port.

    void setDriveControl(int v);

    void updateDrive(int leftPower, int rightPower);

    void opControl();

    void updateLeft(int power);

    void updateRight(int power);

    void turnToAngle(double targetAngle);

    //Runs constantly during auton
    void chassisAutoTask();

    void initialize();
};

extern chassis masterChassis;