// A run randomizer for the video game Dead Cells
// Generates a run randomly based on user criterias


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <vector>
#include <fstream>
#include "pugixml.hpp"
#include "json.hpp"
#include "basicData.h"
#include "biomes.h"
#include "build.h"
#include "gear.h"
#include "mut.h"


// A function to load data from an XML file
// The data is called basic for one reason: it consists of simply 2 elements: an internal name and a displayed name (used for iteraction with the user)
// Such data consists, for example, of the diets, outfits, runes or stats, which are pretty simple data
// The three required parameters are:
//      - the path to the xml file to load
//      - a name used internally for the nodes of the xml file (the structure of the xml files used could gain to be explained more I guess)
//      - a string for the language used for localization
std::vector<basicData> loadXML_basic(std::string const& xml_path, std::string const& data_loaded)
{
    pugi::xml_document xml_data;
    std::vector<basicData> data_vector;
    pugi::xml_parse_result load_result = xml_data.load_file(xml_path.c_str());

    for (pugi::xml_node node = xml_data.child((data_loaded+"_list").c_str()).child(data_loaded.c_str()); node; node = node.next_sibling(data_loaded.c_str()))
    {
        data_vector.push_back(basicData(node.child_value("internal_name")));
    }

    return data_vector;
}

// A special function used to load the biomes.xml file
// How biomes are represented is explained in the biomes.h file.
// The function is vastly hardcoded because it is not supposed to load anything else and the biome structure is too peculiar to have a more generic function
// Parameters are:
//      - the language used for localizations
//      - run parameters. Those are gameplay elements that enable or disable some transitions. We will load only the transitions the player has access to
//        based on those parameters
std::unordered_map<std::string, Biome> loadXML_biomes(int bc_setting, bool vine_rune, bool tp_rune, bool ram_rune,
    bool spider_rune, std::string challenge_biomes_enabled, bool rotg, bool bad_seeds)
{
    const std::string xml_path = "data/biomes.xml";
    pugi::xml_document xml_data;
    std::unordered_map<std::string, Biome> data_collection;
    pugi::xml_parse_result load_result = xml_data.load_file(xml_path.c_str());
    Transition* tmp_trans;

    int min_bc;
    bool vine_req, tp_req, ram_req, spider_req, is_challenge, rotg_req, bad_seeds_req, challenge_biomes_enabled_bool, challenge_biome_set, challenge_biomes_disabled;
    challenge_biomes_enabled_bool = (std::strcmp(challenge_biomes_enabled.c_str(), "True") == 0);
    challenge_biomes_disabled = (std::strcmp(challenge_biomes_enabled.c_str(), "False") == 0);

    for (pugi::xml_node node = xml_data.child("biome_list").child("biome"); node; node = node.next_sibling("biome"))
    {
        challenge_biome_set = false;
        data_collection[node.child_value("internal_name")] = Biome(node.child_value("internal_name"));
        for (pugi::xml_node node_exit = node.child("exits_list").child("exit"); node_exit; node_exit = node_exit.next_sibling("exit"))
        {
            tmp_trans = new Transition;
            min_bc = std::stoi(std::string(node_exit.child_value("min_bc")));
            vine_req = (std::strcmp(node_exit.child_value("vine_rune"), "True") == 0);
            tp_req = (std::strcmp(node_exit.child_value("tp_rune"), "True") == 0);
            ram_req = (std::strcmp(node_exit.child_value("ram_rune"), "True") == 0);
            spider_req = (std::strcmp(node_exit.child_value("spider_rune"), "True") == 0);
            is_challenge = (std::strcmp(node_exit.child_value("challenge_biome"), "True") == 0);
            rotg_req = (std::strcmp(node_exit.child_value("rotg"), "True") == 0);
            bad_seeds_req = (std::strcmp(node_exit.child_value("bad_seeds"), "True") == 0);
            *tmp_trans = Transition(node_exit.child_value("to"));
            if ((min_bc <= bc_setting) && (!(vine_req && (!vine_rune))) && (!(tp_req && (!tp_rune))) && (!(ram_req && (!ram_rune)))
                && (!(spider_req && (!spider_rune))) && (!(is_challenge && challenge_biomes_disabled) && (!challenge_biome_set))
                && (!(rotg_req && (!rotg))) && (!(bad_seeds_req && (!bad_seeds))))
            {
                challenge_biome_set = (is_challenge && challenge_biomes_enabled_bool);
                if (challenge_biome_set)
                {
                    data_collection.find(node.child_value("internal_name"))->second.clearExits();
                }
                data_collection.find(node.child_value("internal_name"))->second.setExit(*tmp_trans);
            }
        }
    }

    return data_collection;
}

std::vector<Gear> loadXML_gear(bool colorless_mode = false, bool no_constraints = false)
{
    const std::string xml_path = "data/gear.xml";
    pugi::xml_document xml_data;
    std::vector<Gear> data_vector;
    pugi::xml_parse_result load_result = xml_data.load_file(xml_path.c_str());
    std::vector<std::string> scaling, gearType, requires, enables, gameplayFlags;

    for (pugi::xml_node node = xml_data.child("gear_list").child("gear"); node; node = node.next_sibling("gear"))
    {
        if (!colorless_mode)
        {
            for (pugi::xml_node node_child = node.child("scaling"); node_child; node_child = node_child.next_sibling("scaling"))
            {
                scaling.push_back(node_child.child_value());
            }
        }
        if (!no_constraints)
        {
            for (pugi::xml_node node_child = node.child("type"); node_child; node_child = node_child.next_sibling("type"))
            {
                gearType.push_back(node_child.child_value());
            }
            for (pugi::xml_node node_child = node.child("requires"); node_child; node_child = node_child.next_sibling("requires"))
            {
                requires.push_back(node_child.child_value());
            }
            for (pugi::xml_node node_child = node.child("enables"); node_child; node_child = node_child.next_sibling("enables"))
            {
                enables.push_back(node_child.child_value());
            }
            for (pugi::xml_node node_child = node.child("special"); node_child; node_child = node_child.next_sibling("special"))
            {
                gameplayFlags.push_back(node_child.child_value());
            }
        }
        data_vector.push_back(Gear(node.child_value("internal_name"), scaling, gearType, requires, enables, gameplayFlags));
        scaling.clear();
        gearType.clear();
        requires.clear();
        enables.clear();
        gameplayFlags.clear();
    }

    return data_vector;
}

std::vector<Mutation> loadXML_muts(bool colorless_mode = false, bool no_constraints = false)
{
    const std::string xml_path = "data/muts.xml";
    pugi::xml_document xml_data;
    std::vector<Mutation> data_vector;
    pugi::xml_parse_result load_result = xml_data.load_file(xml_path.c_str());

    std::vector<std::vector<std::string>> gameplayFlags;
    std::vector<std::string> flagsLoader;
    std::string scaling;
    scaling = "colorless";

    for (pugi::xml_node node = xml_data.child("mut_list").child("mut"); node; node = node.next_sibling("mut"))
    {
        if (!colorless_mode)
        {
            scaling = node.child("scaling").child_value();
        }
        if (!no_constraints)
        {
            for (pugi::xml_node node_child = node.child("requires").child("and"); node_child; node_child = node_child.next_sibling("and"))
            {
                for (pugi::xml_node node_child2 = node_child.child("or"); node_child2; node_child2 = node_child2.next_sibling("or"))
                {
                    flagsLoader.push_back(node_child2.child_value());
                }
                gameplayFlags.push_back(flagsLoader);
                flagsLoader.clear();
            }
        }
        data_vector.push_back(Mutation(node.child_value("internal_name"), gameplayFlags, scaling));
        scaling = "colorless";
        gameplayFlags.clear();
    }

    return data_vector;
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


std::vector<std::string> stat_generator()
{
    // Initiating the RNG
    std::random_device dev;
    std::mt19937 rng(dev());
    std::default_random_engine generator;
    int nb_stats(0), chosen_stat(0);
    // Loading the stats and setting the variables to pick one at random
    std::vector<basicData> stat_vector;
    std::vector<std::string> stat_chosen;

    stat_vector = loadXML_basic("data/stats.xml", "stat");
    nb_stats = stat_vector.size();

    // Generating random diet and stat
    std::uniform_int_distribution<std::mt19937::result_type> rngStats(1, nb_stats);
    chosen_stat = rngStats(rng) - 1;

    stat_chosen.push_back(stat_vector[chosen_stat].getInternName());
    return stat_chosen;
}

std::vector<std::string> diet_generator()
{
    // Initiating the RNG
    std::random_device dev;
    std::mt19937 rng(dev());
    std::default_random_engine generator;
    int  nb_diets(0), chosen_diet(0);
    // Loading the diets and setting the variables to pick one at random
    std::vector<basicData> diet_vector;
    std::vector<std::string> diet_chosen;

    diet_vector = loadXML_basic("data/diets.xml", "diet");
    nb_diets = diet_vector.size();

    // Generating random diet and stat
    std::uniform_int_distribution<std::mt19937::result_type> rngDiets(1, nb_diets);
    chosen_diet = rngDiets(rng) - 1;
    diet_chosen.push_back(diet_vector[chosen_diet].getInternName());
    return diet_chosen;
}

std::vector<std::string> biome_generator(int bc_lvl, bool has_vine, bool has_tp, bool has_ram, bool has_spider, bool has_rotg, bool has_bad_seeds,
    std::string challenge_biomes_enabled, std::unordered_map<std::string, Biome> biomes_collection) {

    // Starter biome is hardcoded because it's not supposed to change
    std::string const STARTING_BIOME = "pq";

    // Maximum number of exits a biome have - used for rng generators later
    int const MAX_EXITS = 4;
    int exits_fact(1);
    for (size_t i = 1; i <= MAX_EXITS; i++)
    {
        exits_fact *= i;
    }

    // Initiating the RNG
    std::random_device dev;
    std::mt19937 rng(dev());
    std::default_random_engine generator;
    int chosen_biome(0);

    // Generating the run
    std::uniform_int_distribution<std::mt19937::result_type> rngBiome(0, (exits_fact-1));
    std::vector<std::string> biomes_run;
    Biome current_biome;

    current_biome = biomes_collection.find(STARTING_BIOME)->second;

    while (current_biome.getExits().size() > 0)
    {
        biomes_run.push_back(current_biome.getInternName());
        chosen_biome = rngBiome(rng) / (exits_fact/current_biome.getExits().size());
        current_biome = current_biome.getExits()[chosen_biome]->getBiome();
    }
    biomes_run.push_back(current_biome.getInternName());
    
    return biomes_run;
}

std::vector<std::string> loadLocalisations(std::vector<std::string>& dataToLocalize, std::string category, std::string& localization_xml)
{
    std::vector<std::string> localized_data;
    for each (std::string s in dataToLocalize)
    {
        localized_data.push_back("");
    }

    pugi::xml_document xml_data;
    pugi::xml_parse_result load_result = xml_data.load_file(localization_xml.c_str());
    int index;
    std::vector<std::string>::iterator finder;

    for (pugi::xml_node node = xml_data.child("lang").child(category.c_str()).first_child(); node; node = node.next_sibling())
    {
        finder = std::find(dataToLocalize.begin(), dataToLocalize.end(), node.name());
        if (finder != dataToLocalize.end())
        {
            index = std::distance(dataToLocalize.begin(), finder);
            localized_data[index] = node.child_value();
        }
    }

    return localized_data;
}

Build gear_generator(Build startingBuild)
{
    Build resultBuild;
    std::vector<Gear> gearTable;
    gearTable = loadXML_gear();
    return resultBuild;
}

Build muts_generator(Build startingBuild)
{
    Build resultBuild;
    std::vector<Mutation> mutsTable;
    mutsTable = loadXML_muts();
    return resultBuild;
}

int main() {
    std::unordered_map<std::string, int> bench_results;
    int bc_lvl(0), nb_iter(0);
    bool has_vine(true), has_tp(true), has_ram(true), has_spider(true), has_rotg(true), has_bad_seeds(true), benchmark_mode(false);
    std::string lang = "en", challenge_biomes_enabled, output_file, loc_file;
    std::vector<std::string> diet_chosen, stat_chosen, run_generated;
    std::vector<std::string> loc_diet, loc_stat, loc_run, loc_benchmark, index_benchmark, loc_gear, loc_muts;
    Build build = Build();

    std::unordered_map<std::string, int>::iterator itr;
    std::unordered_map<std::string, Biome>::iterator other_itr;

    std::string json_path = "params.json";
    std::ifstream json_stream(json_path);
    nlohmann::json j;
    json_stream >> j;
    bc_lvl = j["settings"]["bc"];
    j["settings"]["lang"].get_to(lang);
    loc_file = "lang/" + lang + ".xml";
    j["settings"]["challenge_biomes"].get_to(challenge_biomes_enabled);
    j["settings"]["output_file"].get_to(output_file);
    nb_iter = j["settings"]["nb_tests_benchmark"];
    benchmark_mode = j["settings"]["benchmarking_mode"];
    has_vine = j["settings"]["vine_rune"];
    has_tp = j["settings"]["tp_rune"];
    has_ram = j["settings"]["ram_rune"];
    has_spider = j["settings"]["spider_rune"];
    has_rotg = j["settings"]["rotg"];
    has_bad_seeds = j["settings"]["bad_seeds"];

    // Loading the Biome list
    std::unordered_map<std::string, Biome> biomes_collection;

    biomes_collection = loadXML_biomes(bc_lvl, has_vine, has_tp, has_ram, has_spider, challenge_biomes_enabled, has_rotg, has_bad_seeds);
    biomes_collection = setup_connections(biomes_collection);

    if (benchmark_mode)
    {
        for (other_itr = biomes_collection.begin(); other_itr != biomes_collection.end(); other_itr++)
        {
            bench_results[other_itr->second.getInternName()] = 0;
            index_benchmark.push_back(other_itr->second.getInternName());
        }
        for (size_t i = 0; i < nb_iter; i++)
        {
            run_generated = biome_generator(bc_lvl, has_vine, has_tp, has_ram, has_spider, has_rotg, has_bad_seeds, challenge_biomes_enabled, biomes_collection);
            for each (std::string biome in run_generated)
            {
                bench_results[biome]++;
            }
        }
    }
    else
    {
        diet_chosen = diet_generator();
        stat_chosen = stat_generator();
        build = gear_generator(build);
        build = muts_generator(build);
        run_generated = biome_generator(bc_lvl, has_vine, has_tp, has_ram, has_spider, has_rotg, has_bad_seeds, challenge_biomes_enabled, biomes_collection);
    }

    std::ofstream output_stream(output_file);
    if (benchmark_mode)
    {
        loc_benchmark = loadLocalisations(index_benchmark, "biomes", loc_file);
        for (size_t i = 0; i < index_benchmark.size(); i++)
        {
            output_stream << loc_benchmark[i] << ": " << bench_results[index_benchmark[i]] * 1.0 / nb_iter << std::endl;
        }
    }
    else
    {
        loc_diet = loadLocalisations(diet_chosen, "diets", loc_file);
        loc_stat = loadLocalisations(stat_chosen, "stats", loc_file);
        loc_run = loadLocalisations(run_generated, "biomes", loc_file);
        loc_gear = loadLocalisations(build.gearToVec(), "items", loc_file);
        loc_muts = loadLocalisations(build.mutsToVec(), "muts", loc_file);
        for each (std::string d in loc_diet)
        {
            output_stream << "Diet: " << d << std::endl;
        }
        for each (std::string s in loc_stat)
        {
            output_stream << "Statistic chosen: " << s << std::endl;
        }
        output_stream << "Run:" << std::endl;
        for each (std::string b in loc_run)
        {
            output_stream << b << std::endl;
        }
    }
    //while(true) {}
    return 0;
}

int main_checkerGearMutsList()
{
    std::string const output_file = "list_tests.txt";
    std::ofstream output_stream(output_file);
    std::vector<Gear> listGear;
    std::vector<Mutation> listMuts;
    listGear = loadXML_gear();
    listMuts = loadXML_muts();
    for each (Gear g in listGear)
    {
        output_stream << g.gearToString() << std::endl;
    }
    for each (Mutation m in listMuts)
    {
        output_stream << m.mutToString() << std::endl;
    }
    //while(true) {}
    return 0;
}