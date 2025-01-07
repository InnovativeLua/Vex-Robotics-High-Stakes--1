#pragma once
#include <vector>
#include "headers/brain/auton.hpp"
#include "main.h"
#include "headers/auton/autons.hpp"

class autonSelector {
public:
  std::vector<Auton> Autons;
  int currentAutonPage;
  int autonCount;
  pros::adi::DigitalIn limitSwitch = pros::adi::DigitalIn('H');
  bool limitDebounce = false;
  autonSelector();
  void callSelectedAuton();
  void printSelectedAuton();
  void addAutons(std::vector<Auton> autons);
  void cycleAutons();
  void initilize();
  void compTask();
  Auton createAuton(std::function<void()> autoFunction, std::string autoName);
};

extern autonSelector masterAutonSelector;