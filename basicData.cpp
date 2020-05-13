#include "basicData.h"

basicData::basicData(std::string const& interName)
{
    internal_name = interName;
}

basicData::~basicData()
{
}


std::string basicData::getInternName()
{
    return internal_name;
}