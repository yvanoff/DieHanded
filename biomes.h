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
// But we need to have the exit Biome as attribute, to be able to set it or to get it
// And we need the name of the target biome for linking issues

class Transition
{
public:
    Transition() = default;
    Transition(std::string const& exitC);
    ~Transition();
    void setBiome(Biome& exit_set);
    Biome getBiome();
    std::string getName();

private:
    Biome* exit;
    std::string exit_name;
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
    void clearExits();
    std::vector<Transition*> getExits();
    std::string getDisplayName();
    std::string getInternName();

private:
    basicData biomeData;
    std::vector<Transition*> exits;
};