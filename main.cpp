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
#include "basicData.h"
#include "biomes.h"


// A function to load data from an XML file
// The data is called basic for one reason: it consists of simply 2 elements: an internal name and a displayed name (used for iteraction with the user)
// Such data consists, for example, of the diets, outfits, runes or stats, which are pretty simple data
// The three required parameters are:
//      - the path to the xml file to load
//      - a name used internally for the nodes of the xml file (the structure of the xml files used could gain to be explained more I guess)
//      - a string for the language used for localization
std::vector<basicData> loadXML_basic(std::string const& xml_path, std::string const& data_loaded, std::string const& lang_choice)
{
    pugi::xml_document xml_data;
    std::vector<basicData> data_vector;
    pugi::xml_parse_result load_result = xml_data.load_file(xml_path.c_str());

    for (pugi::xml_node node = xml_data.child((data_loaded+"_list").c_str()).child(data_loaded.c_str()); node; node = node.next_sibling(data_loaded.c_str()))
    {
        data_vector.push_back(basicData(node.child_value("internal_name"), node.child_value(lang_choice.c_str())));
    }

    return data_vector;
}

// A special function used to load the biomes.xml file
// How biomes are represented is explained in the biomes.h file.
// The function is vastly hardcoded because it is not supposed to load anything else and the biome structure is too peculiar to have a more generic function
// Only parameter is a string to know which languages to load localizations for
std::unordered_map<std::string, Biome> loadXML_biomes(std::string const& lang_choice)
{
    const std::string xml_path = "data/biomes.xml";
    pugi::xml_document xml_data;
    std::unordered_map<std::string, Biome> data_collection;
    pugi::xml_parse_result load_result = xml_data.load_file(xml_path.c_str());
    Transition* tmp_trans;

    int min_bc;

    for (pugi::xml_node node = xml_data.child("biome_list").child("biome"); node; node = node.next_sibling("biome"))
    {
        data_collection[node.child_value("internal_name")] = Biome(node.child_value("internal_name"), node.child_value(lang_choice.c_str()));
        for (pugi::xml_node node_exit = node.child("exits_list").child("exit"); node_exit; node_exit = node_exit.next_sibling("exit"))
        {
            tmp_trans = new Transition;
            min_bc = std::stoi(std::string(node_exit.child_value("min_bc")));
            *tmp_trans = Transition(node_exit.child_value("to"), min_bc , (std::strcmp(node_exit.child_value("vine_rune"), "True") == 0), 
                (std::strcmp(node_exit.child_value("tp_rune"), "True") == 0),
                (std::strcmp(node_exit.child_value("ram_rune"), "True") == 0),
                (std::strcmp(node_exit.child_value("spider_rune"), "True") == 0),
                (std::strcmp(node_exit.child_value("challenge_biome"), "True") == 0),
                (std::strcmp(node_exit.child_value("rotg"), "True") == 0),
                (std::strcmp(node_exit.child_value("bad_seeds"), "True") == 0));
            data_collection.find(node.child_value("internal_name"))->second.setExit(*tmp_trans);
        }
    }

    return data_collection;
}

// There's a problem
// The biomes are supposed to point to one another, so that if you have one Biome object, you can use his exit attribute to access the following biomes
// Problem is, since Biome and Transition are dependent on one another we set up the Biomes but not the Transitions inside them (specifically, not the pointers to other biomes)
// So we have to go through the table again and set up the connection
// The returned table has all biomes pointing to the following biomes via the Transitions
std::unordered_map<std::string, Biome> setup_connections(std::unordered_map<std::string, Biome> const& biomes_table)
{
    std::unordered_map<std::string, Biome> final_table;
    std::unordered_map<std::string, Biome>::iterator itr;
    final_table = biomes_table;

    for (itr = final_table.begin(); itr != final_table.end(); itr++)
    {
        for each (Transition* trans in itr->second.getExits())
        {
            trans->setBiome(final_table.find(trans->getName())->second);
        }
    }

    return final_table;
}


int main() {

    // Starter biome is hardcoded because it's not supposed to change
    std::string const STARTING_BIOME = "pq";


    // We then load the parameters of the run
    // Those parameters are stored in a JSON file and describe which in game abilities the player has access to
    // In game abilities and the difficulty settings affect the existence of some transitions
    // It would be bad to generate a run the player can't complete because he doesn't have the abilities to do so !

    int bc_lvl (0);
    bool has_vine(true),has_tp(true),has_ram(true),has_spider(true),challenge_biomes_enabled (true), has_rotg (true), has_bad_seeds (true);
    std::string lang = "lang_en";

    // Initiating the RNG
    std::random_device dev;
    std::mt19937 rng(dev());
    int nb_stats (0), nb_diets (0);


    // Loading the diets and setting the variables to pick one at random
    std::vector<basicData> diet_vector;

    diet_vector = loadXML_basic("data/diets.xml", "diet", "lang_en");
    nb_diets = diet_vector.size();


    // Idem for stats
    std::vector<basicData> stat_vector;

    stat_vector = loadXML_basic("data/stats.xml", "stat", "lang_en");
    nb_stats = stat_vector.size();


    // Loading the Biome list
    std::unordered_map<std::string, Biome> biomes_collection;

    biomes_collection = loadXML_biomes("lang_en");
    biomes_collection = setup_connections(biomes_collection);


    std::uniform_int_distribution<std::mt19937::result_type> rngDiets(1, nb_diets);
    std::uniform_int_distribution<std::mt19937::result_type> rngStats(1, nb_stats);
    return 0;
}