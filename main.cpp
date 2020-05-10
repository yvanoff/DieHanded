// A run randomizer for the video game Dead Cells
// Generates a run randomly based on user criterias


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>
#include "pugixml.hpp"
#include "json.hpp"

class Biome
{
public:
	Biome();
	~Biome();

private:

};

Biome::Biome()
{
}

Biome::~Biome()
{
}

class Transition
{
public:
	Transition();
	~Transition();

private:

};

Transition::Transition()
{
}

Transition::~Transition()
{
}

int main() {
    // parser les datas pour construire la base de données

    // parser les paramètres de la run (à remplacer par le GUI plus tard)

    // tirer une stat: roll entre 1 et 3

    // tirer un outfit dans la liste

    // tirer un diet mode dans la liste

    // construire la liste des biomes avec une boucle

    std::random_device dev;
    std::mt19937 rng(dev());
    int nb_stats (0), nb_diets (0);

    pugi::xml_document diet_xml;
    std::vector<std::string> diet_vector;

    pugi::xml_parse_result result_diet_load = diet_xml.load_file("data/diets.xml");

    for (pugi::xml_node diet = diet_xml.child("diet_list").child("diet"); diet; diet = diet.next_sibling("diet"))
    {
        nb_diets++;
        diet_vector.push_back(diet.child_value("lang_en"));
    }
    for each (std::string diet_txt in diet_vector)
    {
        std::cout << diet_txt << std::endl;
    }
    std::cout << diet_vector.size() << std::endl;

    pugi::xml_document stats_xml;
    std::vector<std::string> stat_vector;

    pugi::xml_parse_result result_stats_load = stats_xml.load_file("data/stats.xml");

    for (pugi::xml_node stat = stats_xml.child("stat_list").child("stat"); stat; stat = stat.next_sibling("stat"))
    {
        nb_stats++;
        stat_vector.push_back(stat.child_value("lang_en"));
    }
    for each (std::string stat_txt in stat_vector)
    {
        std::cout << stat_txt << std::endl;
    }
    std::cout << stat_vector.size() << std::endl;
    while (true) {}


    std::uniform_int_distribution<std::mt19937::result_type> rngDiets(1, nb_diets);
    std::uniform_int_distribution<std::mt19937::result_type> rngStats(1, nb_stats);
    return 0;
}