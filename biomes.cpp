#include "biomes.h"

Transition::Transition(std::string const& exitC)
{
    exit = NULL;
    exit_name = exitC;
}

Transition::~Transition()
{
}

void Transition::setBiome(Biome& exit_set)
{
    exit = &exit_set;
}
Biome Transition::getBiome()
{
    return *exit;
}

std::string Transition::getName()
{
    return exit_name;
}

Biome::Biome(std::string const& interName)
{
    biomeData = basicData(interName);
}

Biome::~Biome()
{
}

void Biome::setExit(Transition& new_exit)
{
    exits.push_back(&new_exit);
}

void Biome::clearExits()
{
    exits.clear();
}

std::vector<Transition*> Biome::getExits()
{
    return exits;
}

std::string Biome::getInternName()
{
    return biomeData.getInternName();
}
