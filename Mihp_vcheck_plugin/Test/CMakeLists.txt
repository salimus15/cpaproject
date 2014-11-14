project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

#Test qui utilise les sondes de la librairie Mihp_vcheck sans passer par l'utilisation du plugin
add_subdirectory(TEST_WITHOUT_PLUGIN)
#test qui utilise le plugin pour la compilation
add_subdirectory(TEST_WITH_SIMPLE_MAIN)
#test du plugin sur un fichier cpp
add_subdirectory(TEST_WITH_MAIN_CPP)
#test du plugin avec des pragma
add_subdirectory(TEST_PRAGMA_VCHECK)
#test du plugin sans plugin avec une fonction ayant une boucle vectorisable et une autre non
add_subdirectory(TEST_WITH_NO_PLUGIN)
#test du plugin sans plugin avec deux fonction ayant des boucles vectorisables mais pour des taille de vecteur specifiques
add_subdirectory(TEST_WITHOUT_PLUGIN_VECTOR_SIZE)
