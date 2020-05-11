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

Biome::Biome(std::string const& interName, std::string const& displayName)
{
    biomeData = basicData(interName, displayName);
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

std::string Biome::getDisplayName()
{
    return biomeData.getDisplayName();
}

std::string Biome::getInternName()
{
    return biomeData.getInternName();
}
