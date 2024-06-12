#include "headers/brain/autonselector.hpp"

autonSelector::autonSelector() {
  autonCount = 0;
  currentAutonPage = 0;
  Autons = {};
}

void autonSelector::callSelectedAuton() {
  if (autonCount == 0) return;
  void (*Autons[currentAutonPage])();
}

void autonSelector::addAutons(std::vector<Auton> autons) {
  autonCount = autons.size();
  currentAutonPage = 0;
  Autons.assign(autons.begin(), autons.end());
}

void autonSelector::cycleAutons(){
  if (autonCount==0) return;

  if (currentAutonPage + 1 >= autonCount){
    currentAutonPage = 0;
  } else {
    currentAutonPage += 1;
  }
}