#pragma once
#include <iostream>
#include <vector>
class Mutation
{
public:
    Mutation() = default;
    Mutation(std::string name, std::vector<std::vector<std::string>> gameplayMod);
    Mutation(std::string name, std::vector<std::vector<std::string>> gameplayMod, std::string mutScales);
    ~Mutation();
    std::string mutToString();

private:
    std::string internalName;
    std::string scaling;
    std::vector<std::vector<std::string>> requiredGameplay;
};