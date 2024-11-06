#pragma once

//Custom headers.
#include "headers/mechs/chassis/basechassis.hpp"

//Built in libaries
#include <math.h>
#include <numbers>
#include <vector>

class odometry {
 public:

    void update();
    void initilize();
    void resetPosition();
    std::vector<double> getPosition();
    std::vector<double> getPreviousPosition();

 private:
    const double AuxOffset;
    const double leftOffset;

    double X;
    double Y;
    double prevX;
    double prevY;
    double Heading;
    double prevAux; //Sets the previous encoder value to the current value.
	double prevLE; //Sets the previous encoder value to the current value.
	double previousHeading; //Sets the previous heading to the current heading in radians.
};

extern odometry masterOdometry;