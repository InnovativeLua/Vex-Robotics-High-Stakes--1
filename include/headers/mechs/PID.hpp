#pragma once

//Required vex library.
#include "main.h"

class PID {
 public:

  struct Constants { //Struct to hold the constants for the PID.
    double kp; //Proportional term constant.
    double ki; //Integral term constant.
    double kd; //Derivative term constant.
    double start_i; //Value the integral value will start with.
  };

  struct exitCondition { //Struct to hold the conditions for when the PID should exit.
    double smallExitError = 0; //Maximum error for the target to be considered within the target range.
    double largeExitError = 0; //Minimum error for the target to be considered out of the maximum range.
    int smallExitTimeout = 0; //Time in ms until the PID will forcefully quit itself.
    int timeout = 0; //Time in ms the error has to be within the smallExitError to exit.
  };

  enum E_exitResult {SMALL_EXIT, LARGE_EXIT, TIMEOUT}; //Different ways the PID can exit.

  Constants constants; //Set of constants for the current PID.
  exitCondition exit; //Set of exit conditions for the current PID.

  /**
   * Resets all the timers and variables within the PID.
   *
   * @return Nothing
   * 
   */
  void resetVariables();

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
  PID(double p, double i = 0, double d = 0, double pStart_i = 0);

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
  void setConstants(double p, double i = 0, double d = 0, double pStart_i = 0);

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
  void setExitCondition(double smallExitError, double largeExitError, int timeout, int smallExitTimeout);

  /**
   * Changes the current PID's target.
   *
   * @param i_target(double) target for the PID to change to. 
   * @return Nothing
   * 
   */
  void setTarget(double input);

  /**
   * Returns the current target of the PID
   *
   * @return target(double) the current target of the PID.
   * 
   */
  double getTarget();

  /**
   * Uses the PID implementation to compute the output of the system given the input value.
   *
   * @param current(double) The input of the PID system.
   * @return output(double) The output of the PID system.
   * 
   */
  double compute(double current);

  /**
   * Uses the PID implementation to compute the output of the system given the input value.
   *
   * @return exitCondition(int) The type of exit enum that the PID has reached, or -1 when not exiting.
   * 
   */
  int checkExitCondition();


  /**
   * PID variables. 
   */
  double output; //Output of the last compute.
  double cur; //Last input into the compute.
  double error; //Error of the last compute.
  double target; //Current target value for the PID.
  double prev_error; //Previous error of the last compute.
  double integral; //Integral of the last compute.
  double derivative; //Derivative of the last compute.


 private:
  int i = 0, j = 0, k = 0, l = 0; //Various timer variables to be used for different timers.

  /**
   * Resets the two timers for the timeout and the smallExitTimeout.
   *
   * @return None
   * 
   */
  void reset_timers();
};