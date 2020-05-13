#pragma once
#include <iostream>
#include <vector>
#include "gear.h"
#include "mut.h"
class Build
{
    // max number of skills and weapons (not necessarily one/two of each)
    // weapons vectors to have more than 1
public:
    Build();
    Build(Build const& toCopy);
    ~Build();
    void addMain(Gear mainToAdd);
    void addOffHand(Gear offToAdd);
    void addSkill(Gear skillToAdd);
    void addMut(Mutation mutToAdd);
    bool isWeaponCompatible(Gear gearToTest);
    bool isMutCompatible(Mutation mutToTest);
    std::vector<std::string> gearToVec();
    std::vector<std::string> mutsToVec();

private:
    Gear* mainWeapon;
    Gear* offHand;
    std::vector<Gear> skills;
    std::vector<Mutation> mutList;
    std::vector<std::vector<std::string>> gameplayRequired;
    std::vector<std::string> gameplayEnabled;
    std::vector<std::string> otherFlags;
};