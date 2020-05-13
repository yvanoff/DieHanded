#include "mut.h"
#include <iostream>

Mutation::Mutation(std::string name, std::vector<std::vector<std::string>> gameplayMod)
{
	internalName = name;
	for each (std::vector<std::string> flag in gameplayMod)
	{
		requiredGameplay.push_back(flag);
	}
	scaling = "colorless";
}

Mutation::Mutation(std::string name, std::vector<std::vector<std::string>> gameplayMod, std::string mutScales)
{
	internalName = name;
	for each (std::vector<std::string> flag in gameplayMod)
	{
		requiredGameplay.push_back(flag);
	}
	scaling = mutScales;
}

Mutation::~Mutation()
{

}

std::string Mutation::mutToString()
{
	std::string mutString;
	mutString = internalName;
	mutString += (", " + scaling);
	for each (std::vector<std::string> flag in requiredGameplay)
	{
		mutString += " and: ";
		for each (std::string f in flag)
		{
			mutString += (" | " + f);
		}
		
	}
	return mutString;
}