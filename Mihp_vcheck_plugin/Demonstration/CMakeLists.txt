project(Mihp_vcheck_Test)
cmake_minimum_required(VERSION 2.8)

#Démonstration qui utilise les sondes de la librairie Mihp_vcheck sans passer par l'utilisation du plugin

#demo completement vectorisable
add_subdirectory(DEMO_VECTORISABLE)
#demo avec une dependance avant (vectorisable)
add_subdirectory(DEMO_FWD_DEPEND)
#demo avec une dependance arrière (non-vectorisable)
add_subdirectory(DEMO_BACK_DEPEND)


