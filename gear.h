#pragma once
#include <iostream>
#include <vector>
class Gear
{
public:
    Gear() = default;
    //Gear();
    ~Gear();

private:
    std::string internalName;
    std::string displayName;
    std::vector<std::string> requires;
    std::vector<std::string> enables;
    std::vector<std::string> gameplayFlags;
};