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

    if (elapsedTime < m_accelTime){
        return elapsedTime * m_maxSpeed/m_accelTime;
    } else if (finishTime - elapsedTime < m_accelTime){
        return (finishTime - elapsedTime) * m_accelTime;
    } else {
        return m_maxSpeed;
    }

}

void motionProfile::updateProfile(double a_maxSpeed, double a_accelTime, double a_finishTime){
    m_maxSpeed = a_maxSpeed;
    m_accelTime = a_accelTime;
    finishTime = a_finishTime;
}

void motionProfile::disable(){
    profileActive = false;
}

motionProfile masterProfile;