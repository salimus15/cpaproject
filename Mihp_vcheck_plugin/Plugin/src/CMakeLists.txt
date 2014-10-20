project(Mihp_vcheck_plugin)
cmake_minimum_required(VERSION 2.8)

# ceci sont les sources du plugin

#on compile les sources du plugin
add_library(mihpvcheckplugin SHARED mihp_vcheck_plugin.cpp)

#on permet l'installation du plugin (il faudra sûrement changer le dossier de destination)
install(TARGETS mihpvcheckplugin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

