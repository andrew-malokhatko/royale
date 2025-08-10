cmake_minimum_required (VERSION 3.24)

project(royale)

set (CMAKE_CXX_STANDARD 23)

add_subdirectory(game_core)
add_subdirectory(game_ui)
add_subdirectory(app_game)
add_subdirectory(app_server)