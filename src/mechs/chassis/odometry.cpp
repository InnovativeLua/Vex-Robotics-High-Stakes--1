#include "mechs/chassis/odometry.hpp"
#include "mechs/chassis/basechassis.hpp"
#define PI std::numbers::pi
#define in_per_tick 2 * PI * (1/360)
#define AuxOffset 0
#define leftOffset 0

void odometry::resetPosition(){
	double X = 0; //Sets x to zero
	double Y = 0; //Sets the y to zero
}
void odometry::initilize(){
	resetPosition();
	double prevAux = masterChassis.auxTracker.get_value(); //Sets the previous encoder value to the current value.
	double prevLE = masterChassis.leftTracker.get_value(); //Sets the previous encoder value to the current value.
	double previousHeading = masterChassis.ChassisIMU.get_heading()*PI/180; //Sets the previous heading to the current heading in radians.
}

std::vector<double> odometry::getPosition(){
	return {X, Y, Heading};
}

std::vector<double> odometry::getPreviousPosition(){
	return {prevX, prevY, previousHeading};
}

std::vector<double> odometry::getEstimatedVelocity(){
	return {estimatedVelocityX, estimatedVelocityY, estimatedAngularVelocity};
}

void odometry::update(){
	double LEncoder = masterChassis.leftTracker.get_value(); //Sets a variable composed of the left encoder value.
	double auxEncoder = masterChassis.auxTracker.get_value(); //Sets a variable composed of the right encoder value.

	double deltaL = (LEncoder - prevLE) * in_per_tick; //Calculates the left distance by finding the change in encoder value and changing to inches.
	double deltaAux = (auxEncoder - prevAux) * in_per_tick; //Calculates the right distance by finding the change in encoder value and changing to inches.

	prevLE = LEncoder; //Updates the previousEncoder Value
	prevAux = auxEncoder; //Updates the previousEncoder Value

	Heading = masterChassis.ChassisIMU.get_heading()*PI/180; //Updates the heading variable.

	double deltaTheta = Heading - previousHeading;
		
	double deltaX; //Local Coordinate System Delta X
	double deltaY; //Local Coordinate System Delta Y

	if (Heading == previousHeading){ //if the robot has not turned.
		deltaX = LEncoder; //sets DeltaX to the left encoder value.
		deltaY = auxEncoder; //sets DeltaY to the right encoder value.
	} else { //The robot has turned
		deltaX = 2 * sin(Heading/2) * ((LEncoder / deltaTheta) + leftOffset); //Triangles + Mathematics to determine local coordinate delta X.
		deltaY = 2 * sin(Heading/2) * ((auxEncoder / deltaTheta) + AuxOffset); //Triangles + Mathematics to determine local coordinate delta Y.
	}

	double averageHeading = previousHeading + deltaTheta/2; //Takes the averge of the previous heading and the new heading.

	prevX = X;
	prevY = Y;
	X += (cos(-averageHeading) * deltaX - sin(-averageHeading) * deltaY);
	Y += (sin(-averageHeading) * deltaX + cos(-averageHeading) * deltaY);

	estimatedVelocityX = (X - prevX)/0.01; //inches / 0.01 seconds - Time between updates.
	estimatedVelocityY = (Y - prevY)/0.01; //inches / 0.01 seconds - Time between updates.

	estimatedAngularVelocity = (Heading - previousHeading)/0.01;

	previousHeading = Heading;
}

//Old Code:
/*
void odometry2(){
	while (masterChassis.ChassisIMU.is_calibrating()){
		pros::delay(20); //Waits for the odometry to calibrate
	}
	while (true){ //Goes on forever.
		double LEncoder = masterChassis.leftTracker.get_value(); //Sets a variable composed of the left encoder value.
		double auxEncoder = masterChassis.auxTracker.get_value(); //Sets a variable composed of the right encoder value.

		double deltaL = (LEncoder - prevLE) * in_per_tick; //Calculates the left distance by finding the change in encoder value and changing to inches.
		double deltaAux = (auxEncoder - prevAux) * in_per_tick; //Calculates the right distance by finding the change in encoder value and changing to inches.

		prevLE = LEncoder; //Updates the previousEncoder Value
		prevAux = auxEncoder; //Updates the previousEncoder Value

		double Heading = masterChassis.ChassisIMU.get_heading()*PI/180; //Updates the heading variable.

		double deltaTheta = Heading - previousHeading;
		
		double deltaX; //Local Coordinate System Delta X
		double deltaY; //Local Coordinate System Delta Y

		if (Heading == previousHeading){ //if the robot has not turned.
			deltaX = LEncoder; //sets DeltaX to the left encoder value.
			deltaY = auxEncoder; //sets DeltaY to the right encoder value.
		} else { //The robot has turned
			deltaX = 2 * sin(Heading/2) * ((LEncoder / deltaTheta) + leftOffset); //Triangles + Mathematics to determine local coordinate delta X.
			deltaY = 2 * sin(Heading/2) * ((auxEncoder / deltaTheta) + AuxOffset); //Triangles + Mathematics to determine local coordinate delta Y.
		}

		double averageHeading = previousHeading + deltaTheta/2; //Takes the averge of the previous heading and the new heading.

		X += (cos(-averageHeading) * deltaX - sin(-averageHeading) * deltaY);
		Y += (sin(-averageHeading) * deltaX + cos(-averageHeading) * deltaY);

		previousHeading = Heading;
		
		pros::delay(10); //Waits 10 seconds.
	}
}
*/