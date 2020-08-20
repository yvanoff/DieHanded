#include <iostream>
#include "gear.h"

Gear::Gear(std::string name, std::vector<std::string> weaponScaling, std::string initGearType,
    std::vector<std::string> initRequires, std::vector<std::string> initEnables, std::vector<std::string> initFlags)
{
    internalName = name;
	for (std::string s : weaponScaling)
	{
		scaling.push_back(s);
	}
	gearType = initGearType;
	for (std::string r : initRequires)
	{
		requires.push_back(r);
	}
	for (std::string e : initEnables)
	{
		enables.push_back(e);
	}
	for (std::string f : initFlags)
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
	for (std::string s : scaling)
	{
		gearString += (", " + s);
	}
	gearString += (", " + gearType);
	for (std::string s : requires)
	{
		gearString += (", " + s);
	}
	for (std::string s : enables)
	{
		gearString += (", " + s);
	}
	for (std::string s : gameplayFlags)
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
	for (std::string stat : scaling)
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
	for (std::string req : requires)
	{
		resReq.push_back(req);
	}
	return resReq;
}

std::vector<std::string> Gear::getEnabled()
{
	std::vector<std::string> resReq;
	for (std::string en : enables)
	{
		resReq.push_back(en);
	}
	return resReq;
}

std::vector<std::string> Gear::getFlags()
{
	std::vector<std::string> resReq;
	for (std::string flag : gameplayFlags)
	{
		resReq.push_back(flag);
	}
	return resReq;
}
