#include "build.h"

Build::Build()
{
	mainWeapon = nullptr;
	offHand = nullptr;
}

Build::Build(Build const& toCopy)
{

}

Build::~Build()
{}

void Build::addMain(Gear mainToAdd)
{
	mainWeapon = &mainToAdd;
	// update enables/disables/flags
}

void Build::addOffHand(Gear offToAdd)
{
	offHand = &offToAdd;
	// update enables/disables/flags
}

void Build::addSkill(Gear skillToAdd)
{
	skills.push_back(skillToAdd);
	// update enables/disables/flags
}

void Build::addMut(Mutation mutToAdd)
{
	mutList.push_back(mutToAdd);
	// updates flags
}

bool Build::isWeaponCompatible(Gear gearToTest)
{
	bool is_skill, resTest, is_main;
	resTest = false;
	is_skill = std::find(gearToTest.getType().begin(), gearToTest.getType().end(), "skill") != gearToTest.getType().end();
	is_skill = std::find(gearToTest.getType().begin(), gearToTest.getType().end(), "main") != gearToTest.getType().end();
	// differentiating between a weapon and a skill
	if (is_skill)
	{
		// skills are not full
		if (skills.size < 2)
		{

		}
	}
	else
	{
		// is it a main weapon and we don't already have one
		if (is_main && (mainWeapon == nullptr))
		{

		}
		// it is a secondary weapon, we have not already accepted it as a potential main and we don't have an offhand weaapon yet
		if ((!is_main) && (!resTest) && (offHand == nullptr))
		{

		}
	}
	return resTest;
}

bool Build::isMutCompatible(Mutation mutToTest)
{}

std::vector<std::string> Build::gearToVec()
{
	std::vector<std::string> vecGear;
	vecGear.push_back(mainWeapon->getName());
	vecGear.push_back(offHand->getName());
	for each (Gear skill in skills)
	{
		vecGear.push_back(skill.getName());
	}
	return vecGear;
}

std::vector<std::string> Build::mutsToVec()
{
	std::vector<std::string> vecMuts;
	for each (Mutation m in mutList)
	{
		vecMuts.push_back(m.getName());
	}
	return vecMuts;
}