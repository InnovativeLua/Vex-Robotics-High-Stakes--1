#include "headers/mechs/PID.hpp"

//Typesafe Sign Function, found here:
//https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
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

/**
 * Constructs the PID given PID and the starting value for I.
 *
 * @param p(double) Proportional term constant.
 * @param i(double) Integral term constant.
 * @param d(double) Derivative term constant.
 * @param start_i(double) Value the integral value will start with.
 * @return Nothing
 * 
 */
PID::PID(double p, double i, double d, double start_i) {
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