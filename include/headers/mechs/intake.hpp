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

    pros::Distance distanceSensor = pros::Distance(DISTANCESENSOR);

	pros::adi::DigitalOut intakeCylinder = pros::adi::DigitalOut(INTAKE_RAISE_SOLENOID);

    //Enum for the control types define what the intake is doing at any point.
    enum E_intakeStates {
        E_DISABLED,
        E_MANUAL,
        E_RINGDETECTED,
        E_RINGLEFTWAITING,
        E_REVERSING,
        E_REVERSE
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

    /**
     * Runs during operator control code.
     * Makes the drivetrain move based on what buttons are being pressed.
     * R1 - Forward
     * R2 - Reverse
     * 
     * @return Nothing
     * 
     */
    void opControl();

    /**
     * Runs during initialization.
     * Sets all the motors to the correct gearing, brake modes, and encoder units.
     * 
     * @return Nothing
     * 
     */
    void initalize();

    E_intakeStates intakeState; //Current intake state the intake is in.

private:
    double intakeVelocity = 600.0; //Velocity of the intake.

    int afterDelay = 2500; //Time for intake to wait before reversing after a ring leaves its sight.
    int reversingTime = 1000; //Time for the intake to reverse before stopping.
    int currentDelay = 0; //Timer for both the afterDelay and the reversingTime.
    int distanceTargetDistance = 30; //Target distance for a ring to be considered "detected".


};

extern intake masterIntake; //Global intake object to be accessed by any files.