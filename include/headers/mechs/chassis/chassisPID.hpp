#pragma once
#include <math.h>
#include <numbers>
#include <vector>
#include <algorithm>
#include "headers/mechs/PID.hpp"
#include "headers/mechs/chassis/odometry.hpp"
#include "headers/mechs/chassis/basechassis.hpp"

class chassisPID {

 public:

    void update();
    void initilize();
    
    void setHeadingPID(double headingTarget, int timeoutTime);
    void setDistancePID(double xTarget, double yTarget, int timeoutTime, double smallExitError=2, double largeExitError=100);

public:
    bool distancePIDActive = false;
    bool headingPIDActive = false;

    bool targetExists;
    double targetX;
    double targetY;
    double targetHeading;

    PID headingPID;
    PID distancePID;

 private:

    double m_currentOdometryX;
    double m_currentOdometryY;
    
};

extern chassisPID masterChassisPID;