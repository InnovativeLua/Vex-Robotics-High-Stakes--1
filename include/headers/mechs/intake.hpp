#pragma once

//Required vex library.
#include "main.h"

//Custom headers.
#include "headers/brain/ports.hpp"
#include "headers/brain/controller.hpp"

class intake{
public:

    //Motor definitions with the respective ports defined in the ports.hpp file.
    pros::Motor intakeMotor = pros::Motor(INTAKEMOTOR);
    pros::Motor intakeMotor2 = pros::Motor(INTAKEMOTOR2);

    pros::Optical intakeOptical = pros::Optical(INTAKE_OPTICAL);

    bool colorRed = false;

    //Enum for the control types define what the intake is doing at any point.
    enum E_intakeStates {
        E_DISABLED,
        E_MANUAL,
        E_RINGDETECTED,
        E_RINGLEFTWAITING,
        E_REVERSING,
        E_REVERSE
    };

    enum autonFlags{
        E_FORWARD_FLAG,
        E_REVERSE_FLAG,
        E_IDLE_FLAG
    };

    autonFlags autonFlag = E_IDLE_FLAG;

    enum E_DetectionStates {
        E_NONE,
        E_EJECTOPPOSITE,
        E_EJECTSAME,
        E_EJECTBOTH
    };

    /**
     * Sets the current intake velocity.
     *
     * @param targetVelocity(double) velocity to set the intake to.
     * @return Nothing
     * 
     */
    void setVelocity(double targetVelocity);

    /**
     * Gets the current intake velocity.
     *
     * @return The current intake velocity.
     * 
     */
    double getVelocity();

    /**
     * Gets the current intake state.
     *
     * @return The current intake state.
     * 
     */
    intake::E_intakeStates getCurrentState();

    /**
     * Runs both the top intake and the bottom intake forward based on the current intake velocity.
     *
     * @return Nothing
     * 
     */
    void spinForward();


    /**
     * Runs both the top intake and the bottom intake reverse based on the current intake velocity.
     *
     * @return Nothing
     * 
     */
    void spinReverse();

    /**
     * Stops both the top intake and the bottom intake.
     *
     * @return Nothing
     * 
     */
    void stop();

    void acceptInput();


    void detectJam();

    /**
     * Runs during operator control code.
     * Makes the drivetrain move based on what buttons are being pressed.
     * R1 - Forward
     * R2 - Reverse
     * 
     * @return Nothing
     * 
     */
    void opControl(bool intakeReverseFlag);

    void update(bool intakeReverseFlag);

    /**
     * Runs during initialization.
     * Sets all the motors to the correct gearing, brake modes, and encoder units.
     * 
     * @return Nothing
     * 
     */
    void initalize();

    E_intakeStates intakeState; //Current intake state the intake is in.
    E_DetectionStates intakeDetectionState;

private:
    double intakeVelocity = 600.0; //Velocity of the intake.

    int afterDelay = 500; //Time for intake to wait before reversing after a ring leaves its sight.
    int reversingTime = 300; //Time for the intake to reverse before stopping.
    int currentDelay = 0; //Timer for both the afterDelay and the reversingTime.

    double redRangeBottom = 5.0;
    double redRangeTop = 30.0;
    double blueRangeBottom = 140.0;
    double blueRangeTop = 200.0;

    int lastEncoderTick = 0;
    int lowEncoderTickRate = 2;
};

extern intake masterIntake; //Global intake object to be accessed by any files.