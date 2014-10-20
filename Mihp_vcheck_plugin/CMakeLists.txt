project(Mihp_vcheck_plugin)
cmake_minimum_required(VERSION 2.8)

#Si on veut compiler en mode optimisé
set(RELEASE_MODE no CACHE BOOL "Install mode")
#Si on veut activer la génération de la documentation
set(DOC_MODE no CACHE BOOL "Doc mode")
#si on veut activer les tests
set(TESTS yes CACHE BOOL "Active Tests")


exec_program(gcc
		"${CMAKE_CURRENT_SOURCE_DIR}/build"
		ARGS -print-file-name=plugin
		OUTPUT_VARIABLE INCLUDE_PLUGIN_GCC
)

include_directories(${INCLUDE_PLUGIN_GCC}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Mihp_vcheck_lib/src)

if(RELEASE_MODE)
	#le -DNOCHECKS permet d'enlever les if au début des fonctions pour vérifier si un pointeur est NULL our des choses comme ça.
	#C'est un peut un mode super optimisé sans filet
	add_definitions(-O3 -DNDEBUG)
	message(STATUS "MIHP VCheck Install mode")
else(RELEASE_MODE)
	#on passe aussi les warning en erreurs
	add_definitions(-O0 -Wall -Werror)
	message(STATUS "MIHP VCheck Debug mode")
endif(RELEASE_MODE)

add_subdirectory(Mihp_vcheck_lib)
add_subdirectory(Plugin)

#On ajoute la compilation des tests sur demande
if(TESTS)
	add_subdirectory(Test)
endif(TESTS)

#On ajoute la génération de la doc sur demande
if(DOC_MODE)
	add_subdirectory(doc)
else(DOC_MODE)
	message(STATUS "No documentation")
endif(DOC_MODE)



