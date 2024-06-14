#include "headers/mechs/chassis/chassisPID.hpp"

void chassisPID::initilize(){
    headingPID.setConstants(0, 0, 0, 0);
    distancePID.setConstants(0, 0, 0, 0);
}

void chassisPID::update(){
    std::vector<double> robotPosition = masterOdometry.getPosition();
    currentOdometryX = robotPosition[0];
    currentOdometryY = robotPosition[1];
    double deltaX = targetX - currentOdometryX;
    double deltaY = targetY - currentOdometryY;
    if (targetExists){
        double distanceFromTarget = hypot(deltaX, deltaY);
        double headingDistanceFromTarget = atan2(deltaY, deltaX);
        double headingPower = (1/4) * std::clamp(headingPID.compute(headingDistanceFromTarget), -127.0, 127.0);
        double distancePower = std::clamp(distancePID.compute(distanceFromTarget), -127.0, 127.0);
        //bias of 1/4th on heading, this has to be tuned so that the heading do

        if (distancePID.checkExitCondition() == distancePID.SMALL_EXIT){
            distancePIDFinished = true;
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
}