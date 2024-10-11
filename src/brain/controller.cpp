//Respective header file.
#include "headers/brain/controller.hpp"

//A global unique pointer to be used by any file to access the main controller.
std::unique_ptr<pros::Controller> mainController = std::make_unique<pros::Controller>(CONTROLLER_MASTER); 