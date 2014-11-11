project(Mihp_vcheck_plugin)
cmake_minimum_required(VERSION 2.8)

# ceci sont les sources du plugin
# add_definitions(-O0)
add_compile_options(-fno-rtti)
# set(COMPILE_FLAGS )
#on compile les sources du plugin
add_library(mihpvcheckplugin SHARED mihp_debug_plugin.cpp mihp_loop_analysis.cpp mihp_vcheck_plugin.cpp)
# set(otherFlags -fPIC )
# set_target_properties(mihpvcheckplugin PROPERTIES COMPILE_FLAGS -fno-rtti)
# set_target_properties(mihpvcheckplugin PROPERTIES COMPILE_FLAGS -fPIC)

#on permet l'installation du plugin (il faudra sûrement changer le dossier de destination)
install(TARGETS mihpvcheckplugin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

