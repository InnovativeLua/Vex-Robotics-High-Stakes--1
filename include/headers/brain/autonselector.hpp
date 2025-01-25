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
  pros::adi::AnalogIn autonPot = pros::adi::AnalogIn(AUTON_POT);
  bool limitDebounce = false;
  autonSelector();
  void callSelectedAuton();
  void printSelectedAuton();
  void addAutons(std::vector<Auton> autons);
  void cycleAutons();
  void initilize();
  void compTask();
  int getAutonPage();
  std::string getSelectedAuton();
  const int potMax = 1000;
  Auton createAuton(std::function<void()> autoFunction, std::string autoName, bool colorRed);
  void updatePage();
};

extern autonSelector masterAutonSelector;