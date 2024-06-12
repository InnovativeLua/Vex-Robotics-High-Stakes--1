#pragma once

#include "main.h"

class PID {
 public:

  PID();


  PID(double p, double i = 0, double d = 0, double pStart_i = 0, std::string name = "");


  void setConstants(double p, double i = 0, double d = 0, double pStart_i = 0);


  struct Constants {
    double kp;
    double ki;
    double kd;
    double start_i;
  };


  struct exitCondition {
    double exitError = 0;
    int timeout = 0;
  };


  void setExitCondition(double exitError, int timeout);


  void setTarget(double input);


  double compute(double current);


  double getTarget();


  Constants getConstants();

  void resetVariables();

  Constants constants;

  exitCondition exit;

  void setName(std::string name);

  /**
   * PID variables. 
   */
  double output;
  double cur;
  double error;
  double target;
  double prev_error;
  double integral;
  double derivative;
  long time;
  long prev_time;

 private:
  int i = 0, j = 0, k = 0, l = 0;
  void reset_timers();
  std::string name;
};