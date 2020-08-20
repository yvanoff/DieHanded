#include "mut.h"
#include <iostream>

Mutation::Mutation(std::string name, std::vector<std::vector<std::string>> gameplayMod)
{
	internalName = name;
	for (std::vector<std::string> flag : gameplayMod)
	{
		requiredGameplay.push_back(flag);
	}
	scaling = "colorless";
}

Mutation::Mutation(std::string name, std::vector<std::vector<std::string>> gameplayMod, std::string mutScales)
{
	internalName = name;
	for (std::vector<std::string> flag : gameplayMod)
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
	for (std::vector<std::string> flag : requiredGameplay)
	{
		mutString += " and: ";
		for (std::string f : flag)
		{
			mutString += (" | " + f);
		}
		
	}
	return mutString;
}

std::string Mutation::getName()
{
	return internalName;
}

std::string Mutation::getScaling()
{
	return scaling;
}

std::vector<std::vector<std::string>> Mutation::getGameplay()
{
	std::vector<std::vector<std::string>> resReq;
	std::vector<std::string> tmpStore;
	for (std::vector<std::string> condition : requiredGameplay)
	{
		for (std::string modifier : condition)
		{
			tmpStore.push_back(modifier);
		}
		resReq.push_back(tmpStore);
		tmpStore.clear();
	}
	return resReq;
}
