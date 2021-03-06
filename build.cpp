#include "build.h"
#include <algorithm>

Build::Build()
{
	maxWeapons = 2;
	maxSkills = 2;
	maxMuts = 3;
	mainStat = "colorless";
}

Build::Build(int weapMax, int skillsMax, int mutsMax, std::string mainS)
{
	maxWeapons = weapMax;
	maxSkills = skillsMax;
	maxMuts = mutsMax;
	mainStat = mainS;
}

Build::~Build()
{}

void Build::addWeapon(Gear mainToAdd)
{
	std::vector<std::string> weapReq;
	weapons.push_back(mainToAdd);
	// update enables/disables/flags
	for (std::string flag : mainToAdd.getFlags())
	{
		otherFlags.push_back(flag);
	}
	for (std::string en : mainToAdd.getEnabled())
	{
		gameplayEnabled.push_back(en);
	}
	for (std::string req : mainToAdd.getRequired())
	{
		weapReq.push_back(req);
	}
	gameplayRequired.push_back(weapReq);
	this->clearFlags();
}


void Build::addSkill(Gear skillToAdd)
{
	std::vector<std::string> weapReq;
	skills.push_back(skillToAdd);
	// update enables/disables/flags
	for (std::string flag : skillToAdd.getFlags())
	{
		otherFlags.push_back(flag);
	}
	for (std::string en : skillToAdd.getEnabled())
	{
		gameplayEnabled.push_back(en);
	}
	for (std::string req : skillToAdd.getRequired())
	{
		weapReq.push_back(req);
	}
	gameplayRequired.push_back(weapReq);
	this->clearFlags();
}

void Build::addMut(Mutation mutToAdd)
{
	std::vector<std::string> mutReq;
	mutList.push_back(mutToAdd);
	// updates flags
	for (std::vector<std::string> req : mutToAdd.getGameplay())
	{
		gameplayRequired.push_back(req);
	}
	this->clearFlags();
}

bool Build::isWeaponCompatible(Gear gearToTest)
{
	bool resTest, has_scaling;
	std::vector<std::string> weapScales;
	weapScales = gearToTest.getScaling();
	resTest = false;
	has_scaling = find(weapScales.begin(), weapScales.end(), mainStat) != weapScales.end();
	// differentiating between a weapon and a skill
	if (weapons.size() < maxWeapons)
	{
		if ((weapons.size() == 0) && (has_scaling || (mainStat == "colorless")))
		{
			resTest = true;
		}
		else
		{
			if ((weapons[weapons.size() - 1].getType() != gearToTest.getType()) && (has_scaling || (mainStat == "colorless")))
			{
				resTest = true;
			}
		}
	}
	if (gearToTest.getType() == "skill")
	{
		resTest = false;
	}
	return resTest;
}

bool Build::isSkillCompatible(Gear gearToTest)
{
	bool resTest, has_scaling;
	std::vector<std::string> weapScales;
	weapScales = gearToTest.getScaling();
	resTest = false;
	has_scaling = std::find(weapScales.begin(), weapScales.end(), mainStat) != weapScales.end();
	// differentiating between a weapon and a skill
	if (skills.size() < maxSkills)
	{
		if (has_scaling || (mainStat == "colorless"))
		{
			resTest = true;
		}
	}
	if (gearToTest.getType() != "skill")
	{
		resTest = false;
	}
	return resTest;
}

bool Build::isMutCompatible(Mutation mutToTest)
{
	bool resTest, has_scaling;
	resTest = false;
	// differentiating between a weapon and a skill
	if (mutList.size() < maxMuts)
	{
		if ((mutToTest.getScaling() == mainStat) || (mainStat == "colorless") || (mutToTest.getScaling() == "colorless"))
		{
			resTest = true;
		}
	}
	return resTest;
}

std::vector<std::string> Build::gearToVec()
{
	std::vector<std::string> vecGear;
	for (Gear mainW : weapons)
	{
		vecGear.push_back(mainW.getName());
	}
	for (Gear skill : skills)
	{
		vecGear.push_back(skill.getName());
	}
	return vecGear;
}

std::vector<std::string> Build::mutsToVec()
{
	std::vector<std::string> vecMuts;
	for (Mutation m : mutList)
	{
		vecMuts.push_back(m.getName());
	}
	return vecMuts;
}

void Build::clearFlags()
{
	std::vector<std::string>::iterator finder;
	int position=0;
	for (std::string flagEn : gameplayEnabled)
	{
		for (std::vector<std::string> flagsReqOr : gameplayRequired)
		{
			position++;
			finder = std::find(flagsReqOr.begin(), flagsReqOr.end(), flagEn);
			if (finder != flagsReqOr.end())
			{
				gameplayRequired.erase(gameplayRequired.begin()+position);
			}
		}
		position = 0;
	}
}
