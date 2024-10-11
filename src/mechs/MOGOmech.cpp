#include "headers/mechs/MOGOmech.hpp"
#include "headers/brain/controller.hpp"


void mogoMech::opControl(){
    if (mainController->get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        extend();
    } else {
        retract();
    }
}

void mogoMech::extend(){
    mogoMechCylinder.set_value(true);
}

void mogoMech::retract(){
    mogoMechCylinder.set_value(false);
}

void mogoMech::initialize(){

}

mogoMech masterMogo;