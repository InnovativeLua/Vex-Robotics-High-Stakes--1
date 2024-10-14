#include "headers/mechs/MOGOmech.hpp"
#include "headers/brain/controller.hpp"


void mogoMech::opControl(){
    if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        if (mogoMechState == E_ENABLED){
            extend();
        } else {
            retract();
        }
    } 
}

void mogoMech::extend(){
    mogoMechCylinder.set_value(true);
    mogoMechState = E_DISABLED;
}

void mogoMech::retract(){
    mogoMechCylinder.set_value(false);
    mogoMechState = E_ENABLED;
}

void mogoMech::initialize(){

}

mogoMech masterMogo;