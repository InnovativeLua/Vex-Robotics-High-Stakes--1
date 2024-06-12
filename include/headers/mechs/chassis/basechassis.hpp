#pragma once
#include <vector>
#include "main.h"
#include "headers/brain/ports.hpp"

class chassis {

 public:

    pros::Motor leftFrontMotor = pros::Motor(4);
    pros::Motor leftBackMotor = pros::Motor(5);
    pros::Motor leftTopMotor = pros::Motor(6);

    pros::Motor rightFrontMotor = pros::Motor(1);
    pros::Motor rightBackMotor = pros::Motor(2);
    pros::Motor rightTopMotor = pros::Motor(3);

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

    pros::adi::Encoder left_tracker = pros::adi::Encoder('D', 'G');
    pros::adi::Encoder right_tracker = pros::adi::Encoder('E', 'F');

    bool driverControlPeriod;

    E_driveControl driveControl;
    E_PTO PTOControl;

    bool PTODB;
    bool PTOValue;

    pros::adi::DigitalOut PTOPistons = pros::adi::DigitalOut('A'); //Pnemautic cylinder object / right wing in the A port.

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