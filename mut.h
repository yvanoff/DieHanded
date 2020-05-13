#pragma once
#include <iostream>
#include <vector>
class Mutation
{
public:
    Mutation() = default;
    //Mutation();
    ~Mutation();

private:
    std::string internalName;
    std::string displayName;
    std::vector<std::string> requiredGameplay;
};