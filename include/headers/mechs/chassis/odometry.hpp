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

    double X = 0.0;
    double Y = 0.0;
    double prevX = 0.0;
    double prevY = 0.0;
    double Heading = 0.0;
    double prevAux = 0.0; //Sets the previous encoder value to the current value.
	double prevLE = 0.0; //Sets the previous encoder value to the current value.
	double previousHeading = 0.0; //Sets the previous heading to the current heading in radians.
    double estimatedVelocityX; //in inches/second
    double estimatedVelocityY; //in inches/second
    double estimatedAngularVelocity; //Might be an explicit way to do this;
    //In radians / second
};

extern odometry masterOdometry;