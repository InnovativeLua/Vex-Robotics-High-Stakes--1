#include <string>
#include <functional>
struct Auton{
    std::function<void()> autonFunction;
    std::string Name;
    bool colorRed;
};