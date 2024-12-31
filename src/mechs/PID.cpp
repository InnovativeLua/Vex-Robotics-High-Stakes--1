//Respective header file for the PID.
#include "headers/mechs/PID.hpp"

//Typesafe Sign Function, found here:
//https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/**
 * Resets all the timers and variables within the PID.
 *
 * @return Nothing
 * 
 */
void PID::resetVariables() {
  output = 0;
  target = 0;
  error = 0;
  prev_error = 0;
  integral = 0;
  k = 0;
  j = 0;
}

/**
* Constructs the PID given the p, i, and d constants and the starting value for I.
 *
 * @param p(double) Proportional term constant.
 * @param i(double) Integral term constant.
 * @param d(double) Derivative term constant.
 * @param start_i(double) Value the integral value will start with.
 * @return Nothing
 * 
 */
PID::PID(double p, double i, double d, double start_i) {
  resetVariables(); //Sets all variables to 0.
  setConstants(p, i, d, start_i);
} 

/**
 * A manual function to set the constants for the PID.
 *
 * @param p(double) Proportional term constant.
 * @param i(double) Integral term constant.
 * @param d(double) Derivative term constant.
 * @param start_i(double) Value the integral value will start with.
 * @return Nothing
 * 
 */
void PID::setConstants(double p, double i, double d, double p_start_i) {
  constants.kp = p;
  constants.ki = i;
  constants.kd = d;
  constants.start_i = p_start_i;
}

/**
 * Sets the parameters for when the PID will exit when checking the current exit conditions.
 *
 * @param smallExitError(double) Maximum error for the target to be considered within the target range.
 * @param largeExitError(double) Minimum error for the target to be considered out of the maximum range.
 * @param timeout(int) Time in ms until the PID will forcefully quit itself.
 * @param smallExitTimeout(int) Time in ms the error has to be within the smallExitError to exit.
 * @return Nothing
 * 
 */
void PID::setExitCondition(double smallExitError, double largeExitError, int timeout, int smallExitTimeout) {
  exit.smallExitError = smallExitError;
  exit.largeExitError = largeExitError;
  exit.timeout = timeout;
  exit.smallExitTimeout = smallExitTimeout;
}

/**
 * Changes the current PID's target.
 *
 * @param i_target(double) target for the PID to change to. 
 * @return Nothing
 * 
 */
void PID::setTarget(double i_target) { target = i_target; }

/**
 * Returns the current target of the PID
 *
 * @return target(double) the current target of the PID.
 * 
 */
double PID::getTarget() { return target; }

/**
 * Uses the PID implementation to compute the output of the system given the input value.
 *
 * @param current(double) The input of the PID system.
 * @return output(double) The output of the PID system.
 * 
 */
double PID::compute(double current) {
  error = target - current;
  derivative = error - prev_error; //Approximation of the derivative, time is constant so no need to divide by dt.

  if (constants.ki != 0) { //If the Integral term is being used.
    if (fabs(error) < constants.start_i) //Prevents it from going below the start 
      integral += error; //Approximation of the integral, time is constant so no need to divide by dt.

    if (sgn(error) != sgn(prev_error)) //Overshot the target.
      integral = 0; //Stops the integral from being used to prevent integral overshooting.
  }

  //Output of the PID based on the error, integral, and derivative.
  output = (error * constants.kp) + (integral * constants.ki) + (derivative * constants.kd);

  prev_error = error;

  return output;
}

/**
 * Uses the PID implementation to compute the output of the system given the input value.
 *
 * @return exitCondition(int) The type of exit enum that the PID has reached, or -1 when not exiting.
 * 
 */
int PID::checkExitCondition() {
  k += 10; //Adds 10 ms to the timeout timer.
  if (exit.smallExitError != 0) { //If the small exit error is being used.
    if (abs(error) < exit.smallExitError) { //Within the range to exit.
      j += 10; //Adds 10 ms to the timer for exiting the PID for being close to the target.
      if (j > exit.smallExitTimeout) { //The error has remained within the smallExitError for smallExitTimeout amount of time.
        reset_timers();
        return SMALL_EXIT;
      }
    } else {
      j = 0; //If it is not or no longer within the target, reset the small exit timer as it has to be continous.
    }
  }
  if (k > exit.timeout){ //The timeout timer has reached the set timeout time.
    return TIMEOUT;
  }
  return -1; //If nothing has returned, return -1 to indicate that the PID should not exit.
}

/**
 * Resets the two timers for the timeout and the smallExitTimeout.
 *
 * @return None
 * 
 */
void PID::reset_timers() {
  k = 0; //Resets the timeout timer.
  j = 0; //Resets the smallExit timer.
}