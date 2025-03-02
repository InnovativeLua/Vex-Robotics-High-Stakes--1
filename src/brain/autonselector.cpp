#include "headers/brain/autonselector.hpp"

autonSelector::autonSelector() {
  autonCount = 0;
  currentAutonPage = 0;
  Autons = {};
}

void autonSelector::updatePage(){
  currentAutonPage = abs((autonCount)*(autonPot.get_value() % potMax)/potMax);
}

void autonSelector::callSelectedAuton() {
  if (autonCount == 0) return;
  currentAutonPage = abs((autonCount)*(autonPot.get_value() % potMax)/potMax);
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
  /*
  if (limitSwitch.get_value() == false){
    limitDebounce = false;
  } else {
    if (limitDebounce == false){
      limitDebounce = true;
      cycleAutons();
    }
  }
  */
}

Auton autonSelector::createAuton(std::function<void()> autoFunction, std::string autoName, bool colorRed){
  Auton newAuto = Auton();
  newAuto.autonFunction = autoFunction;
  newAuto.Name = autoName;
  newAuto.colorRed = colorRed;
  return newAuto;
}

void autonSelector::initilize(){
  //autonPot.calibrate();
  std::vector<Auton> autonsToSelectFrom = {};
  autonsToSelectFrom.push_back(createAuton(skills,"skills", true));
  autonsToSelectFrom.push_back(createAuton(redGoalSide,"redGoalSide", true));
  autonsToSelectFrom.push_back(createAuton(redRingSide,"redRingSide", true));
  autonsToSelectFrom.push_back(createAuton(wRedGoalSide,"wRedGoalSide", true));
  autonsToSelectFrom.push_back(createAuton(wRedRingSide,"wRedRingSide", true));
  autonsToSelectFrom.push_back(createAuton(blueGoalSide,"blueGoalSide", false));
  autonsToSelectFrom.push_back(createAuton(blueRingSide,"blueRingSide", false));
  autonsToSelectFrom.push_back(createAuton(wBlueGoalSide,"wBlueGoalSide", false));
  autonsToSelectFrom.push_back(createAuton(wBlueRingSide,"wBlueRingSide", false));

  addAutons(autonsToSelectFrom);
}


std::string autonSelector::getSelectedAuton(){
  currentAutonPage = abs((autonCount)*(autonPot.get_value() % potMax)/potMax);
  return Autons[currentAutonPage].Name;
}

int autonSelector::getAutonPage(){
  return abs((autonCount)*(autonPot.get_value() % potMax)/potMax);
}

autonSelector masterAutonSelector;