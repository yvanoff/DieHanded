cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(DieHanded VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the classes
add_library(BasicData basicData.cpp)
add_library(Biomes biomes.cpp)
add_library(Build build.cpp)
add_library(Gear gear.cpp)
add_library(Muts mut.cpp)
add_library(XML pugixml.cpp)

# add the executable
add_executable(DieHanded main.cpp)

target_link_libraries(DieHanded PUBLIC BasicData Biomes Build Gear Muts XML)
