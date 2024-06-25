#include "headers/mechs/chassis/chassisPID.hpp"
// Initialize the PID controllers for heading and distance.
void chassisPID::initilize(){
    // Set PID constants for heading control: (Kp, Ki, Kd, Kf)
    headingPID.setConstants(0, 0, 0, 0);

    // Set PID constants for distance control: (Kp, Ki, Kd, Kf)
    distancePID.setConstants(0, 0, 0, 0);
}

// Set up PID control for heading with specified parameters.
void chassisPID::setHeadingPID(double p_targetHeading, int p_timeout){
    // Reset all PID variables to their initial state such as the error, derivative, etc.
    headingPID.resetVariables();

    // Set the target heading for the PID controller.
    targetHeading = p_targetHeading;
    targetExists = true;

    // Configure the PID controller with the new target heading.
    headingPID.setTarget(p_targetHeading);

    // Set the exit conditions for the PID loop:
    // - SmallExitError - Minimum error in degrees before ending the PID (1 degree).
    // - LargeExitError - Maximum allowed error in degrees (180 degrees).
    // - Maximum allowed time to reach target in milliseconds (5000 ms).
    headingPID.setExitCondition(1, 180, p_timeout);

    headingPIDActive = true;
}

/**
 * Calculate and set the inital PID targets. Resets the variables for the PID's along with setting the exit conditions.
 *
 * @param p_targetX X coordinate of the target points's position, in inches starting from the inital robot's position.
 * @param p_targetY Y coordinate of the target points's position, in inches starting from the inital robot's position.
 * @param p_timeout Time in miliseconds which when reached automatically exit the PID even if not finished.
 * @param smallExitError Error term in degrees for when the PID is close enough to its target heading to exit.
 * @param largeExitError Error term in degrees for when the PID is too far away from its target heading so it exits the PID (assuming something went wrong).
 * @return Nothing
 * 
 */
void chassisPID::setDistancePID(double p_targetX, double p_targetY, int p_timeout, double smallExitError, double largeExitError){
    // Reset all PID variables to their initial state such as the error, derivative, etc.
    headingPID.resetVariables();
    distancePID.resetVariables();

    //Setting the target coordinates for the PID.
    targetX = p_targetX;
    targetY = p_targetY;
    targetExists = true;

    //Gets the current robot x and y coordinates along with the heading.
    //Index 0 is the x, Index 1 is the y, Index 2 is the heading.
    std::vector<double> robotPosition = masterOdometry.getPosition();
    m_currentOdometryX = robotPosition[0];
    m_currentOdometryY = robotPosition[1];

    //Calculates how far in the x and y directions the robot is from its target position.
    double deltaX = targetX - m_currentOdometryX;
    double deltaY = targetY - m_currentOdometryY;  

    //
    double distanceFromTarget = std::hypot(deltaX, deltaY);
    double headingDistanceFromTarget = std::atan2(deltaY, deltaX);

    headingPID.setTarget(headingDistanceFromTarget);
    distancePID.setTarget(0.0);

    headingPID.setExitCondition(0, 180, p_timeout);
    distancePID.setExitCondition(smallExitError, largeExitError, p_timeout);

    distancePIDActive = true;
}

void chassisPID::update(){
    std::vector<double> robotPosition = masterOdometry.getPosition();
    m_currentOdometryX = robotPosition[0];
    m_currentOdometryY = robotPosition[1];
    double deltaX = targetX - m_currentOdometryX;
    double deltaY = targetY - m_currentOdometryY;
    if (distancePIDActive && targetExists){
        double distanceFromTarget = std::hypot(deltaX, deltaY);
        double headingDistanceFromTarget = std::atan2(deltaY, deltaX);
        //This is the target so I need to update the target instead of ocmputing with it.
        //Instead the input will be the current
        targetHeading = headingDistanceFromTarget;
        headingPID.setTarget(headingDistanceFromTarget);
        double headingPower = (1/4) * std::clamp(headingPID.compute(robotPosition[2]), -127.0, 127.0);
        double distancePower = std::clamp(distancePID.compute(distanceFromTarget), -127.0, 127.0);
        //bias of 1/4th on heading, this has to be tuned so that the heading do

        if (distancePID.checkExitCondition() == distancePID.SMALL_EXIT){
            distancePIDActive = false;
            targetX = 0;
            targetY = 0;
            targetExists = false;
            return;
        }

        double leftPower = 127 * (distancePower + headingPower)/
        std::max(std::abs(distancePower + headingPower), 
                 std::abs(distancePower - headingPower));

        double rightPower = 127 * (distancePower - headingPower)/
        std::max(std::abs(distancePower + headingPower), 
                 std::abs(distancePower - headingPower));
        //These equations combine the heading and distance equally. 
        //Maybe something that prioritzes distance would be better however that may stop it.
        //There is a large bias added to the heading power by only taking a forth of the disatncde power
        //Still however right and left outputs go from -127 to 127;


        masterChassis.updateLeft(leftPower);
        masterChassis.updateRight(rightPower);
    }
    if (headingPIDActive && targetExists){
        double headingPower = std::clamp(headingPID.compute(masterOdometry.getPosition()[2]), -127.0, 127.0);

        if (headingPID.checkExitCondition() == headingPID.SMALL_EXIT){
            headingPIDActive = false;
            targetHeading = 0;
            targetExists = false;
            return;
        }

        double leftPower = headingPower;
        double rightPower = -headingPower;


        masterChassis.updateLeft(leftPower);
        masterChassis.updateRight(rightPower);
    }
}

chassisPID masterChassisPID;