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
    bool targetExists;
    double currentOdometryX;
    double currentOdometryY;
    double targetX;
    double targetY;
    double targetHeading;
    PID headingPID;
    PID distancePID;
    bool distancePIDActive = false;
    bool headingPIDActive = false;

 private:
    const double AuxOffset = 0;
    const double leftOffset = 0;
};

extern chassisPID masterChassisPID;