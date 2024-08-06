#pragma once
#include <vector>
#include "headers/brain/auton.hpp"

class autonSelector {
public:
  std::vector<Auton> Autons;
  int currentAutonPage;
  int autonCount;
  autonSelector();
  void callSelectedAuton();
  void printSelectedAuton();
  void addAutons(std::vector<Auton> autons);
  void cycleAutons();
};

extern autonSelector masterAutonSelector;