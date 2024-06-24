#include "headers/mechs/chassis/chassisPID.hpp"

void chassisPID::initilize(){
    headingPID.setConstants(0, 0, 0, 0);
    distancePID.setConstants(0, 0, 0, 0);
}

void chassisPID::setHeadingPID(double headingTarget, int timeoutTime){
    headingPID.resetVariables();
    targetHeading = headingTarget;
    targetExists = true;
    headingPID.setTarget(headingTarget);
    headingPID.setExitCondition(1, 180, 5000);
    headingPIDActive = true;
}

void chassisPID::setDistancePID(double xTarget, double yTarget, int timeoutTime, double smallExitError, double largeExitError){
    headingPID.resetVariables();
    distancePID.resetVariables();
    targetX = xTarget;
    targetY = yTarget;
    targetExists = true;

    std::vector<double> robotPosition = masterOdometry.getPosition();
    m_currentOdometryX = robotPosition[0];
    m_currentOdometryY = robotPosition[1];
    double deltaX = targetX - m_currentOdometryX;
    double deltaY = targetY - m_currentOdometryY;  
    double distanceFromTarget = std::hypot(deltaX, deltaY);
    double headingDistanceFromTarget = std::atan2(deltaY, deltaX);

    headingPID.setTarget(headingDistanceFromTarget);
    distancePID.setTarget(0.0);

    headingPID.setExitCondition(0, 180, timeoutTime);
    distancePID.setExitCondition(smallExitError, largeExitError, timeoutTime);

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