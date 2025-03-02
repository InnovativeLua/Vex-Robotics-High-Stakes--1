//Respective header file for the odometry.
#include "headers/mechs/chassis/odometry.hpp"

//Converts encoder ticks to radians, based on 3.25" wheels.
constexpr double in_per_tick = 2 * PI / 360 * 3.25 / 2.0;
constexpr double in_per_tick_mec = 2 * PI /360 * 2 / 2.0 / 100.0;

/**
 * Sets the current X and Y positions to (0, 0);
 * 
 * @return Nothing
 * 
 */
void odometry::resetPosition(){
	double X = 0.0;
	double Y = 0.0;
}

void odometry::setX(double num){
	X = num;
}

void odometry::setY(double num){
	Y = num;
}

/**
 * Returns the current position and heading in a vector format.
 * 
 * @return std::vector<double> the current X, Y, and Heading positions of the robot in format {X, Y, Heading}
 * 
 */
std::vector<double> odometry::getPosition(){
	return {X, Y, Heading};
}

/**
 * Returns the previous position and heading in a vector format.
 * 
 * @return std::vector<double> the previous X, Y, and Heading positions of the robot in format {X, Y, Heading}
 * 
 */
std::vector<double> odometry::getPreviousPosition(){
	return {prevX, prevY, previousHeading};
}

/**
 * Updates the X, Y, and heading values.
 *
 * @return Nothing
 * 
 */
void odometry::update(){
	//Sets variables composed of the encoder values. Casts to double to keep types consistent.
	double LEncoder = -(double)(masterChassis.leftTracker.get_position());
	double auxEncoder = -(double)(masterChassis.auxTracker.get_position());

	//Finds the change between the last encoder value and converts to inches traveled.
	//Multipled by 3.25" because we are using 3.25" wheels.
	double deltaL = (LEncoder - prevLE) * in_per_tick_mec;
	double deltaAux = (auxEncoder - prevAux) * in_per_tick_mec;

	prevLE = LEncoder; //Updates the previousEncoder value.
	prevAux = auxEncoder; //Updates the previousEncoder value.

	//Updates the current heading and converting to radians. 
	Heading = masterChassis.ChassisIMU.get_heading()*PI/180;

	//Finds the change in the heading, Local X, and local Y
	double deltaTheta = Heading - previousHeading;
	double deltaX = deltaL; //Local Coordinate System Delta X
	double deltaY = deltaAux; //Local Coordinate System Delta Y

	//Checks if the robot has not turned or barely turned.
	if (std::abs(deltaTheta) < 0.0001){
		deltaX = deltaL; //sets DeltaX to the left encoder value.
		deltaY = deltaAux; //sets DeltaY to the right encoder value.
	} else { //The robot has turned
		//Applies trigonometry to find how far the robot has traveled in the local coordinate system.
		deltaX = 2.0 * std::sin(deltaTheta/2) * ((deltaL / deltaTheta) + leftOffset);
		deltaY = 2.0 * std::sin(deltaTheta/2) * ((deltaAux / deltaTheta) + AuxOffset);
	}

	//Average of the previous heading and current heading.
	double averageHeading = previousHeading + deltaTheta/2;

	//Updates the previous X and Y variables.
	prevX = X;
	prevY = Y;

	//Applies a rotation matrix to find the global X and Y changes and adds to the current X and Y.
	X -= (cos(-averageHeading) * deltaX - sin(-averageHeading) * deltaY);
	Y += (sin(-averageHeading) * deltaX + cos(-averageHeading) * deltaY);

	previousHeading = Heading; //Sets the previous heading to the current heading.
}

/**
 * Runs during initialization.
 * Sets up several variables and resets encoders.
 * 
 * @return Nothing
 * 
 */
void odometry::initilize(){
	resetPosition(); //Calibrates the position to (0, 0)

	//Sets the 2 tracking wheels' values to 0 degrees.
    masterChassis.auxTracker.reset();
    masterChassis.leftTracker.reset();
	masterChassis.auxTracker.reset_position();
	masterChassis.leftTracker.reset_position();

	//Defines the previous values that are necessary for the first update call.
	double prevAux = 0.0;
	double prevLE = 0.0;
	double previousHeading = 0.0;
}

odometry masterOdometry; //Global main Odometry object to use the Odometry in other files.