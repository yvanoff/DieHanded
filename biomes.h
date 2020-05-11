#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "basicData.h"

// A file for two classes
// The problem is thus: a Biome has a number of exits, exits represented by the Transition classes
// A Traansition points to an exit Biome
// So the two classes are interdependent
// So I put them both in the same file because I don't know how to do otherwise

class Biome;

// A transition goes from one Biome to the other
// Here Transitions will never be used on their own but always as an attribute of a Biome: that Biome will be the starting one
// But we need to have the exit Biome as arribute, to be able to set it or to get it
// All the other attributes are linked to variables in game: some transitions can only be accessed with some abilities or at some difficulty settings, so we need to account for that
// And of course we need to access tgem (but no need to modifiy them, the characteristics of a transition are fixed and never change)

class Transition
{
public:
    Transition() = default;
    Transition(std::string const& exitC, int const& min_bcC, bool const& vineC,
        bool const& tpC, bool const& ramC, bool const& spiderC, bool const& challengeC,
        bool const& rotgC, bool const& badSeedsC);
    ~Transition();
    void setBiome(Biome& exit_set);
    Biome getBiome();
    std::string getName();
    int getBC();
    bool getVine();
    bool getTP();
    bool getRam();
    bool getSpider();
    bool getChallenge();
    bool getROTG();
    bool getBadSeeds();

private:
    Biome* exit;
    std::string exit_name;
    int min_bc;
    bool vine;
    bool tp;
    bool ram;
    bool spider;
    bool is_challenge_biome;
    bool rotg;
    bool bad_seeds;
};

// A biome has an internal name, a displayed name (that's basicData) and a list of exits (vector of Transition, the number of Transitions ranges from 0 to 4 depending on the biome)
// We need to be able to access to both internal and displayed names
// We also need to be able to access the exit list, or to add exits
// There's no need for further modification because the list of exits a biome has never changes

class Biome
{
public:
    Biome() = default;
    Biome(std::string const& interName, std::string const& displayName);
    ~Biome();
    void setExit(Transition& new_exit);
    std::vector<Transition*> getExits();
    std::string getDisplayName();
    std::string getInternName();

private:
    basicData biomeData;
    std::vector<Transition*> exits;
};