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

    pros::adi::Encoder leftTracker = pros::adi::Encoder(ODOMETRY_LEFT_TOP, ODOMETRY_LEFT_BOTTOM, false);
    pros::adi::Encoder auxTracker = pros::adi::Encoder(ODOMETRY_AUX_TOP, ODOMETRY_AUX_BOTTOM, false);

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

    void startHeadingPID(double target);
    void PIDLoop();


    bool headingPIDEnabled = false;
    PID headingPID = PID(6.0, 0, 20.0, 0, "HeadingPID");

private:
    E_driveControl driveControl; //Current drive control type the chassis is using.
};

extern chassis masterChassis; //Global main chassis to use the drivetrain in other files.