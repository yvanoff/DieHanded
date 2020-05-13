#include <iostream>
#include "gear.h"

Gear::Gear(std::string name, std::vector<std::string> weaponScaling, std::vector<std::string> initGearType,
    std::vector<std::string> initRequires, std::vector<std::string> initEnables, std::vector<std::string> initFlags)
{
    internalName = name;
	for each (std::string s in weaponScaling)
	{
		scaling.push_back(s);
	}
	for each (std::string t in initGearType)
	{
		gearType.push_back(t);
	}
	for each (std::string r in initRequires)
	{
		requires.push_back(r);
	}
	for each (std::string e in initEnables)
	{
		enables.push_back(e);
	}
	for each (std::string f in initFlags)
	{
		gameplayFlags.push_back(f);
	}
}

Gear::~Gear()
{

}

std::string Gear::gearToString()
{
	std::string gearString;
	gearString = internalName;
	for each (std::string s in scaling)
	{
		gearString += (", " + s);
	}
	for each (std::string s in gearType)
	{
		gearString += (", " + s);
	}
	for each (std::string s in requires)
	{
		gearString += (", " + s);
	}
	for each (std::string s in enables)
	{
		gearString += (", " + s);
	}
	for each (std::string s in gameplayFlags)
	{
		gearString += (", " + s);
	}
	return gearString;
}