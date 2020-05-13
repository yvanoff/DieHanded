#pragma once
#include <iostream>
#include <vector>
#include "gear.h"
#include "mut.h"
class Build
{
public:
    Build() = default;
    //Build();
    ~Build();
    void addGear(Gear gearToAdd);
    void addMut(Mutation mutToAdd);
    bool isWeaponCompatible(Gear gearToTest);
    bool isMutCompatible(Mutation mutToTest);

private:
    int nbWeapons;
    int nbSkills;
    std::vector<Gear> gearList;
    std::vector<Mutation> mutList;
    std::vector<std::string> gameplayRequired;
    std::vector<std::string> gameplayEnabled;
    std::vector<std::string> otherFlags;
};