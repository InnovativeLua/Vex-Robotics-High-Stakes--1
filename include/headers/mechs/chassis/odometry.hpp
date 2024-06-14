#pragma once
#include <math.h>
#include <numbers>

class odometry {

 public:

    void update();

    void initilize();
    void resetPosition();

 private:

    double X;
    double Y;
    double prevAux; //Sets the previous encoder value to the current value.
	double prevLE; //Sets the previous encoder value to the current value.
	double previousHeading; //Sets the previous heading to the current heading in radians.

};

odometry masterOdometry;