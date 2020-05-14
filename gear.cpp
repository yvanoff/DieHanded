#include <iostream>
#include "gear.h"

Gear::Gear(std::string name, std::vector<std::string> weaponScaling, std::string initGearType,
    std::vector<std::string> initRequires, std::vector<std::string> initEnables, std::vector<std::string> initFlags)
{
    internalName = name;
	for each (std::string s in weaponScaling)
	{
		scaling.push_back(s);
	}
	gearType = initGearType;
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
	gearString += (", " + gearType);
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

std::string Gear::getName()
{
	return internalName;
}

std::vector<std::string> Gear::getScaling()
{
	std::vector<std::string> resReq;
	for each (std::string stat in scaling)
	{
		resReq.push_back(stat);
	}
	return resReq;
}

std::string Gear::getType()
{
	return gearType;
}

std::vector<std::string> Gear::getRequired()
{
	std::vector<std::string> resReq;
	for each (std::string req in requires)
	{
		resReq.push_back(req);
	}
	return resReq;
}

std::vector<std::string> Gear::getEnabled()
{
	std::vector<std::string> resReq;
	for each (std::string en in enables)
	{
		resReq.push_back(en);
	}
	return resReq;
}

std::vector<std::string> Gear::getFlags()
{
	std::vector<std::string> resReq;
	for each (std::string flag in gameplayFlags)
	{
		resReq.push_back(flag);
	}
	return resReq;
}