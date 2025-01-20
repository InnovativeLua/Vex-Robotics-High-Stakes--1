#include "headers/brain/autonselector.hpp"

autonSelector::autonSelector() {
  autonCount = 0;
  currentAutonPage = 0;
  Autons = {};
}

void autonSelector::callSelectedAuton() {
  if (autonCount == 0) return;
  Autons[currentAutonPage].autonFunction();
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

void autonSelector::compTask(){
  if (limitSwitch.get_value() == false){
    limitDebounce = false;
  } else {
    if (limitDebounce == false){
      limitDebounce = true;
      cycleAutons();
    }
  }
}

Auton autonSelector::createAuton(std::function<void()> autoFunction, std::string autoName){
  Auton newAuto = Auton();
  newAuto.autonFunction = autoFunction;
  newAuto.Name = autoName;
  return newAuto;
}

void autonSelector::initilize(){
  std::vector<Auton> autonsToSelectFrom = {};
  autonsToSelectFrom.push_back(createAuton(redAWP,"redAWP"));
    autonsToSelectFrom.push_back(createAuton(blueAWP,"blueAWP"));
  autonsToSelectFrom.push_back(createAuton(skills,"skills"));
  autonsToSelectFrom.push_back(createAuton(redElimination,"redElimination"));
  autonsToSelectFrom.push_back(createAuton(blueElimination,"blueElimination"));
  addAutons(autonsToSelectFrom);
}


std::string autonSelector::getSelectedAuton(){
  return Autons[currentAutonPage].Name;
}

autonSelector masterAutonSelector;