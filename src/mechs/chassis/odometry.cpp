//Respective header file for the odometry.
#include "headers/mechs/chassis/odometry.hpp"

#define PI std::numbers::pi //Replaces PI with the number pi.
#define in_per_tick 2 * PI //Replaces in_per_tick with tau.

void odometry::resetPosition(){
	double X = 0.0;
	double Y = 0.0;
}

void odometry::initilize(){
	resetPosition(); //Calibrates the position to (0, 0)

	//Sets the 2 tracking wheels' values to 0 degrees.
    masterChassis.auxTracker.reset();
    masterChassis.leftTracker.reset();

	//Sets the previous encoder/heading values to the current values.
	double prevAux = (double)masterChassis.auxTracker.get_value();
	double prevLE = (double)masterChassis.leftTracker.get_value();
	double previousHeading = masterChassis.ChassisIMU.get_heading()*PI/180;
}

std::vector<double> odometry::getPosition(){
	return {X, Y, Heading}; //Returns a vector of the X Position, Y Position, and Heading.
}

std::vector<double> odometry::getPreviousPosition(){
	return {prevX, prevY, previousHeading}; //Returns a vector of the previous X, Y, and Heading.
}

void odometry::update(){
	//Sets variables composed of the encoder values. Casts to double to keep types consistent.
	double LEncoder = (double)(masterChassis.leftTracker.get_value());
	double auxEncoder = (double)(masterChassis.auxTracker.get_value());

	//Finds the change between the last encoder value and converts to inches traveled.
	//Multipled by 3.25" because we are using 3.25" wheels.
	double deltaL = (LEncoder - prevLE) * in_per_tick * 3.25;
	double deltaAux = (auxEncoder - prevAux) * in_per_tick * 3.25;

	prevLE = LEncoder; //Updates the previousEncoder value.
	prevAux = auxEncoder; //Updates the previousEncoder value.

	//Updates the current heading and converting to radians. 
	Heading = masterChassis.ChassisIMU.get_heading()*PI/180;

	//Finds the change in the heading, Local X, and local Y
	double deltaTheta = Heading - previousHeading;
	double deltaX = deltaL; //Local Coordinate System Delta X
	double deltaY = deltaAux; //Local Coordinate System Delta Y

	//Checks if the robot has not turned or barely turned.
	if (std::abs(deltaTheta) < 0.001){
		deltaX = deltaL; //sets DeltaX to the left encoder value.
		deltaY = deltaAux; //sets DeltaY to the right encoder value.
	} else { //The robot has turned
		//Applies trigonometry to find how far the robot has traveled in the local coordinate system.
		deltaX = 2 * std::sin(deltaTheta/2) * ((deltaL / deltaTheta) + leftOffset);
		deltaY = 2 * std::sin(deltaTheta/2) * ((deltaAux / deltaTheta) + AuxOffset);
	}

	//Average of the previous heading and current heading.
	double averageHeading = previousHeading + deltaTheta/2;

	//Updates the previous X and Y variables.
	prevX = X;
	prevY = Y;

	//Applies a rotation matrix to find the global X and Y changes and adds to the current X and Y.
	X += (cos(-averageHeading) * deltaX - sin(-averageHeading) * deltaY);
	Y += (sin(-averageHeading) * deltaX + cos(-averageHeading) * deltaY);

	previousHeading = Heading; //Sets the previous heading to the current heading.
}

odometry masterOdometry;