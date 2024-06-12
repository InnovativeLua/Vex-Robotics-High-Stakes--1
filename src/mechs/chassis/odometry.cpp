void odometry(){
	while (IMUSensor.is_calibrating()){
		pros::delay(20); //Waits for the odometry to calibrate
	}
	double X = 0; //Sets x to zero
	double Y = 0; //Sets the y to zero
	double prevLE = leftEncoder.get_value(); //Sets the previous encoder value to the current value.
	double prevRE = rightEncoder.get_value(); //Sets the previous encoder value to the current value.
	double previousHeading = IMUSensor.get_heading()*PI/180; //Sets the previous heading to the current heading in radians.
	while (true){ //Goes on forever.
		double LEncoder = leftEncoder.get_value(); //Sets a variable composed of the left encoder value.
		double REncoder = rightEncoder.get_value(); //Sets a variable composed of the right encoder value.

		double distL = (LEncoder - prevLE) * in_per_tick; //Calculates the left distance by finding the change in encoder value and changing to inches.
		double distR = (REncoder - prevRE) * in_per_tick; //Calculates the right distance by finding the change in encoder value and changing to inches.

		prevLE = LEncoder; //Updates the previousEncoder Value
		prevRE = REncoder; //Updates the previousEncoder Value

		double Heading = IMUSensor.get_heading()*PI/180; //Updates the heading variable.

		double deltaTheta = Heading - previousHeading;
		
		double deltaX; //Local Coordinate System Delta X
		double deltaY; //Local Coordinate System Delta Y

		if (Heading == previousHeading){ //if the robot has not turned.
			deltaX = LEncoder; //sets DeltaX to the left encoder value.
			deltaY = REncoder; //sets DeltaY to the right encoder value.
		} else { //The robot has turned
			deltaX = 2 * sin(Heading/2) * ((LEncoder / deltaTheta) + L); //Triangles + Mathematics to determine local coordinate delta X.
			deltaY = 2 * sin(Heading/2) * ((REncoder / deltaTheta) + R); //Triangles + Mathematics to determine local coordinate delta Y.
		}

		double averageHeading = previousHeading + deltaTheta/2; //Takes the averge of the previous heading and the new heading.

		X += (deltaY * sin(averageHeading)) + (deltaX * cos(averageHeading)); //Adds a rotation matrix to deltaX+Y and adds it to the X.
		Y += (deltaY * cos(averageHeading)) - (deltaX * sin(averageHeading)); //Adds a rotation matrix to deltaX+Y and adds it to the Y.

		pros::delay(10); //Waits 10 seconds.
	}
}