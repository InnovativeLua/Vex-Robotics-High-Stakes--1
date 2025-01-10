#pragma once
#include <vector>
#include "headers/brain/auton.hpp"
#include "main.h"
#include "headers/auton/autons.hpp"
#include <string>

class autonSelector {
public:
  std::vector<Auton> Autons;
  int currentAutonPage;
  int autonCount;
  pros::adi::DigitalIn limitSwitch = pros::adi::DigitalIn(AUTON_LIMIT);
  bool limitDebounce = false;
  autonSelector();
  void callSelectedAuton();
  void printSelectedAuton();
  void addAutons(std::vector<Auton> autons);
  void cycleAutons();
  void initilize();
  void compTask();
  std::string getSelectedAuton();
  Auton createAuton(std::function<void()> autoFunction, std::string autoName);
};

extern autonSelector masterAutonSelector;