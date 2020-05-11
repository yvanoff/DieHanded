#include "biomes.h"

Transition::Transition(std::string const& exitC, int const& min_bcC,
    bool const& vineC, bool const& tpC, bool const& ramC, bool const& spiderC,
    bool const& challengeC, bool const& rotgC, bool const& badSeedsC)
{
    exit = NULL;
    exit_name = exitC;
    min_bc = min_bcC;
    vine = vineC;
    tp = tpC;
    ram = ramC;
    spider = spiderC;
    is_challenge_biome = challengeC;
    rotg = rotgC;
    bad_seeds = badSeedsC;
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
int Transition::getBC()
{
    return min_bc;
}

bool Transition::getVine()
{
    return vine;
}

bool Transition::getTP()
{
    return tp;
}

bool Transition::getRam()
{
    return ram;
}

bool Transition::getSpider()
{
    return spider;
}

bool Transition::getChallenge()
{
    return is_challenge_biome;
}
bool Transition::getROTG()
{
    return rotg;
}

bool Transition::getBadSeeds()
{
    return bad_seeds;
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
