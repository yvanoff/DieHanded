#include "basicData.h"

basicData::basicData(std::string const& interName, std::string const& displayName)
{
    internal_name = interName;
    display_name = displayName;
}

basicData::~basicData()
{
}

std::string basicData::getDisplayName()
{
    return display_name;
}

std::string basicData::getInternName()
{
    return internal_name;
}