#pragma once

//Built in libaries
#include <vector>

//Required vex library.
#include "main.h"

//Custom headers.
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"
#include "headers/mechs/PID.hpp"

class chassis {
 public:

    //Motor definitions with the respective ports defined in the ports.hpp file.
    pros::Motor leftFrontMotor = pros::Motor(LEFT_FRONT_MOTOR);
    pros::Motor leftBackMotor = pros::Motor(LEFT_BACK_MOTOR);
    pros::Motor leftTopMotor = pros::Motor(LEFT_TOP_MOTOR);

    pros::Motor rightFrontMotor = pros::Motor(RIGHT_FRONT_MOTOR);
    pros::Motor rightBackMotor = pros::Motor(RIGHT_BACK_MOTOR);
    pros::Motor rightTopMotor = pros::Motor(RIGHT_TOP_MOTOR);

    //Enum for each type of drive controls.
    enum E_driveControl {
        E_ARCADE_CONTROL, //Control type which uses one vertical joystick and one horizontal joystick.
        E_TANK_CONTROL //Control type which uses two vertical joysticks.
    };

    //Vector to hold which left motors are active. Implemented in case we want to have a PTO later.
    std::vector<pros::Motor> ActiveLeftMotors = {leftFrontMotor, leftBackMotor, leftTopMotor};

    //Vector to hold which right motors are active. Implemented in case we want to have a PTO later.
    std::vector<pros::Motor> ActiveRightMotors = {rightFrontMotor, rightBackMotor, rightTopMotor};

    pros::IMU ChassisIMU = pros::IMU(ODOMETRY_INERTIAL); //Chassis IMU to be used later.

    pros::Rotation leftTracker = pros::Rotation(ODOMETRY_LEFT);
    pros::Rotation auxTracker = pros::Rotation(ODOMETRY_AUX);

    bool driverControlPeriod; //Boolean to see if the driver control period is enabled.

    /**
     * Sets the current chassis control type.
     *
     * @param targetDriveControl(E_driveControl) Drive control to switch to.
     * @return Nothing
     * 
     */
    void setDriveControl(E_driveControl targetDriveControl);

    /**
     * Get the current chassis control type.
     *
     * @return driveControl(E_driveControl) current drive control type for the chassis.
     * 
     */
    E_driveControl getCurrentDriveControl();

    /**
     * Runs the left chassis motors based on the power param.
     *
     * @param power(int) Voltage for motors from -127 to 127
     * @return Nothing
     * 
     */
    void updateLeft(int power);

    /**
     * Runs the right chassis motors based on the power param.
     *
     * @param power(int) Voltage for motors from -127 to 127
     * @return Nothing
     * 
     */
    void updateRight(int power);

    void headingPIDLoop();

    /**
     * Runs both the left and right chassis motors.
     *
     * @param leftPower(int) Voltage for left chassis motors ranging from -127 to 127.
     * @param rightPower(int) Voltage for right chassis motors ranging from -127 to 127.
     * @return Nothing
     * 
     */
    void updateDrive(int leftPower, int rightPower);

    //void turnToAngle(double targetAngle); //Not Implemented will be later on.

    /**
     * Runs during operator control code.
     * Makes the drivetrain move based on the controller joysticks and the type of control we want. 
     * Arcade Control - One vertical joystick moves the drivetrain forward and one horizontal turns the drivetrain.
     * Tank Control - Each vertical joystick moves each side of the drivetrain.
     * 
     * @return Nothing
     * 
     */
    void opControl();


    /**
     * Runs during initialization.
     * Sets all the motors to the correct gearing, brake modes, and encoder units.
     * Resets the chassis IMU.
     * 
     * @return Nothing
     * 
     */
    void initialize();

    void startHeadingPID(double target, double maxVel);
    void PIDLoop();
    void startMainPID(std::vector<double> target, double maxVel,bool reversed);


    bool headingPIDEnabled = false;
    PID headingPID = PID(7.0, 0.0, 30.0, 0.0);
    PID distancePID = PID(10.0, 0, 0.0, 0);
    PID mainHeadingPID = PID(5.0, 0, 30.0, 0);
    bool mainPIDEnabled = false;
    bool mainPIDReversed = false;
    double maxMainPIDVelocity = 127.0;
    double maxHeadingPIDVelocity = 127.0;
    int motionProfileTime = 300;
    int motionTimer = 0;

    std::vector<double> mainPIDTarget = {0.0, 0.0};




private:
    E_driveControl driveControl; //Current drive control type the chassis is using.
};

extern chassis masterChassis; //Global main chassis to use the drivetrain in other files.