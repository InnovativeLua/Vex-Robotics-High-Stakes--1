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
    void reset();
    void setTarget();
    bool targetExists;
    double currentOdometryX;
    double currentOdometryY;
    double targetX;
    double targetY;
    PID headingPID;
    PID distancePID;
    bool distancePIDFinished = true;

 private:
    const double AuxOffset = 0;
    const double leftOffset = 0;
};

extern chassisPID masterChassisPID;