#include "headers/mechs/PID.hpp"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


void PID::resetVariables() {
  output = 0;
  target = 0;
  error = 0;
  prev_error = 0;
  integral = 0;
  time = 0;
  prev_time = 0;
  k = 0;
  j = 0;
}

PID::PID() {
  resetVariables();
  setConstants(0, 0, 0, 0);
}

PID::Constants PID::getConstants() { return constants; }

// PID constructor with constants
PID::PID(double p, double i, double d, double start_i, std::string name) {
  resetVariables();
  setConstants(p, i, d, start_i);
} 

// Set PID constants
void PID::setConstants(double p, double i, double d, double p_start_i) {
  constants.kp = p;
  constants.ki = i;
  constants.kd = d;
  constants.start_i = p_start_i;
}

// Set exit condition timeouts
void PID::setExitCondition(double smallExitError, double largeExitError, int timeout, int smallExitTimeout) {
  exit.smallExitError = smallExitError;
  exit.largeExitError = largeExitError;
  exit.timeout = timeout;
  exit.smallExitTimeout = smallExitTimeout;
}

void PID::setTarget(double input) { target = input; }

double PID::getTarget() { return target; }

double PID::compute(double current) {
  error = target - current;
  derivative = error - prev_error;

  if (constants.ki != 0) {
    if (fabs(error) < constants.start_i)
      integral += error;

    if (sgn(error) != sgn(prev_error))
      integral = 0;
  }

  output = (error * constants.kp) + (integral * constants.ki) + (derivative * constants.kd);

  prev_error = error;

  return output;
}

void PID::reset_timers() {
  k = 0;
  j = 0;
}

int PID::checkExitCondition() {
  k += 20;
  // If the robot gets within the target, make sure it's there for small_timeout amount of time
  if (exit.smallExitError != 0) {
    if (abs(error) < exit.smallExitError) {
      j += 10;
      if (j > exit.smallExitTimeout) {
        reset_timers();
        return SMALL_EXIT;
      }
    } else {
      j = 0;
    }
  }
  if (k > exit.timeout){
    return TIMEOUT;
  }
  return -1;
}