project (royale LANGUAGES CXX)

add_executable(game
    main.cpp
)

target_include_directories(game PRIVATE
    include
)

 target_sources(game PRIVATE
    src/application.cpp
 )

#add_subdirectory(game_core)
#add_subdirectory(game_ui)
target_link_libraries(game
    raylib
    ws2_32
    game_core
    game_ui
)