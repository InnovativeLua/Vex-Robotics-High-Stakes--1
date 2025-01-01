#pragma once

//Custom headers.
#include "headers/mechs/chassis/basechassis.hpp"

//Built in libaries
#include <math.h>
#include <numbers>
#include <vector>

#define PI std::numbers::pi //Replaces PI with the number pi to make the code cleaner.

class odometry {
 public:

     /**
     * Sets the current X and Y positions to (0, 0);
     * 
     * @return Nothing
     * 
     */
    void resetPosition();

     /**
     * Returns the current position and heading in a vector format.
     * 
     * @return std::vector<double> the current X, Y, and Heading positions of the robot in format {X, Y, Heading}
     * 
     */
     std::vector<double> getPosition();

     /**
     * Returns the previous position and heading in a vector format.
     * 
     * @return std::vector<double> the previous X, Y, and Heading positions of the robot in format {X, Y, Heading}
     * 
     */
     std::vector<double> getPreviousPosition();

     /**
     * Updates the X, Y, and heading values.
     *
     * @return Nothing
     * 
     */
     void update();

     /**
     * Runs during initialization.
     * Sets up several variables and resets encoders.
     * 
     * @return Nothing
     * 
     */
     void initilize();

 private:

    const double AuxOffset = 0.01/8.0; //Constant to indicate vertical offset of the auxiliary wheel.
    const double leftOffset = 0.01/8.0; //Constant to indicate horizontal offset of the forward wheel.

    double X; //X position of the last update call.
    double Y; //Y position of the last update call.
    double Heading; //Heading of the last update call.

    double prevX; //X position of the update call before the last update call.
    double prevY; //Y position of the update call before the last update call.
    double previousHeading; //Heading of the update call before the last update call.
    double prevAux; //Aux position of the update call before the last update call.
    double prevLE; //Forward encoder position of the update call before the last update call.
};

extern odometry masterOdometry; //Global Odometry object to be accessed by any files.