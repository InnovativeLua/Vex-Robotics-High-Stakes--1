#include "headers/mechs/chassis/profiling.hpp"
#include "headers/mechs/chassis/basechassis.hpp"
#include "main.h"

#define profileDebug

void motionProfile::profileTask(){
    while (true){
        if (!profileActive){
            pros::delay(20);
            continue;
        }
        double motorSpeed = calculateOutput();
        masterChassis.updateDrive(motorSpeed, motorSpeed);
        pros::delay(20);
        elapsedTime += 20;
        if (elapsedTime > finishTime){
            profileActive = false;
        }
    }
}

double motionProfile::calculateOutput(){
    if (activeProfileType == E_TRAPEZOIDAL){
        return trapezoidalProfile();
    }
    return 0;
}

double motionProfile::trapezoidalProfile(){

    #ifndef profileDebug
    if (accelTime * 2 > finishTime){
        print("Warning, profile accel time greater than finish.");
    }
    #endif

    if (elapsedTime < accelTime){
        return elapsedTime * maxSpeed/accelTime;
    } else if (finishTime - elapsedTime < accelTime){
        return (finishTime - elapsedTime) *  accelTime;
    } else {
        return maxSpeed;
    }

}

void motionProfile::updateProfile(double i_maxSpeed, double i_accelTime, double i_finishTime){
    maxSpeed = i_maxSpeed;
    accelTime = i_accelTime;
    i_finishTime = finishTime;
}

void motionProfile::disable(){
    profileActive = false;
}

motionProfile masterProfile;