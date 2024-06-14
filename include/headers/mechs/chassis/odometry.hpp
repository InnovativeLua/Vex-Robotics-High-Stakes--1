#pragma once
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
    std::vector<double> getEstimatedVelocity();

 private:
    const double AuxOffset = 0;
    const double leftOffset = 0;

    double X;
    double Y;
    double prevX;
    double prevY;
    double Heading;
    double prevAux; //Sets the previous encoder value to the current value.
	double prevLE; //Sets the previous encoder value to the current value.
	double previousHeading; //Sets the previous heading to the current heading in radians.
    double estimatedVelocityX; //in inches/second
    double estimatedVelocityY; //in inches/second
    double estimatedAngularVelocity; //Might be an explicit way to do this;
    //In radians / second
};

extern odometry masterOdometry;