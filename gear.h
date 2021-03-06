#pragma once
#include <iostream>
#include <vector>
class Gear
{
public:
    Gear() = default;
    Gear(std::string name, std::vector<std::string> weaponScaling, std::string initGearType,
        std::vector<std::string> initRequires, std::vector<std::string> initEnables, std::vector<std::string> initFlags);
    ~Gear();
    std::string gearToString();
    std::string getName();
    std::vector<std::string> getScaling();
    std::string getType();
    std::vector<std::string> getRequired();
    std::vector<std::string> getEnabled();
    std::vector<std::string> getFlags();

private:
    std::string internalName; // name
    std::vector<std::string> scaling; // stat scaling
    std::string gearType; // main weapon/offhand/shield/skill. Vector 'cause one weapon is both main and offhand
    std::vector<std::string> requires; // effects the weapons requires to be really effective (ex: some weapons crit on bleeding enemies => it requires bleed)
    std::vector<std::string> enables; // effects the weapon give (ex: some weapons burn the enemies => it enables burn)
    std::vector<std::string> gameplayFlags; // tags such as: melee damage, shortrange/longrange, deoplyed skill, has ammo, can crit, etc...
};