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
    Build(int weapMax, int skillsMax, int mutsMax, std::string mainS);
    ~Build();
    void addWeapon(Gear mainToAdd);
    void addSkill(Gear skillToAdd);
    void addMut(Mutation mutToAdd);
    bool isWeaponCompatible(Gear gearToTest);
    bool isSkillCompatible(Gear gearToTest);
    bool isMutCompatible(Mutation mutToTest);
    std::vector<std::string> gearToVec();
    std::vector<std::string> mutsToVec();

private:
    int maxWeapons;
    int maxSkills;
    int maxMuts;
    std::string mainStat;
    std::vector<Gear> weapons;
    std::vector<Gear> skills;
    std::vector<Mutation> mutList;
    std::vector<std::vector<std::string>> gameplayRequired;
    std::vector<std::string> gameplayEnabled;
    std::vector<std::string> otherFlags;
    void clearFlags();
};