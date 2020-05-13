#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Simple class holding an internal name for use by the program and a display name to be used for localization
// Used to represent a variety of simple data
// Initiated from two strings which can be accessed with get methods

class basicData
{
public:
    basicData() = default;
    basicData(std::string const& interName);
    ~basicData();
    std::string getInternName();

private:
    std::string internal_name;
};

