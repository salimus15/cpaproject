project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

include_directories(../Mihp_vcheck_lib)

#Test qui utilise les sondes de la librairie Mihp_vcheck sans passer par l'utilisation du plugin
add_subdirectory(TEST_WITHOUT_PLUGIN)


