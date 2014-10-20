project(Mihp_vcheck_plugin)
cmake_minimum_required(VERSION 2.8)

#on définit les variables pour pouvoir générer le fichier Doxyfile
set(PROGRAM_NAME "MIHP VCheck")
set(PROGRAM_VERSION "0.1.0")
set(PROGRAM_DESCRIPTION "Ce projet est composé d'une librairie qui permet d'utiliser des sondes sur un programme donné, et d'un plugin GCC qui permet d'insérer ces sondes dans le programme que l'on veut analyser. L'analyse consite à dire si les boucles les plus internes dans les fonctions spécifiées avec le pragma mihp vcheck sont vectorialisable ou non, et dans quelle mesure elles le sont.")

find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
	message(STATUS "Find Doxygen at ${DOXYGEN_DIR}")
	#si vous allez voir dans le dossier build, vous allez trouver le fichier Doxyfile
	configure_file(Doxyfile.cmake Doxyfile)
	exec_program(${DOXYGEN_EXECUTABLE}
		"${CMAKE_CURRENT_SOURCE_DIR}/build"
		ARGS "${CMAKE_CURRENT_SOURCE_DIR}/../build/doc/Doxyfile"
	)
	configure_file(index.html.cmake index.html)

	install(DIRECTORY doc/html DESTINATION share/Mihp_vcheck_plugin/doc)
	install(DIRECTORY doc/man DESTINATION share/Mihp_vcheck_plugin/doc)

	set(docDeBase ${CMAKE_CURRENT_BINARY_DIR}/index.html style.css)

	install(FILES ${docDeBase} DESTINATION share/Mihp_vcheck_plugin/doc)

else (DOXYGEN_FOUND)
	message(STATUS "Doxygen not found, I cannot generate the documentation")
endif (DOXYGEN_FOUND)



