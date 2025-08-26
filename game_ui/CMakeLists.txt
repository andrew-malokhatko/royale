project (game_ui)


add_library(game_ui
    src/applicationView.cpp
    src/TextureManager.cpp
    src/EntityTextureManager.cpp
    src/EntityTexture.cpp

    src/nodes/Node.cpp
    src/nodes/Card.cpp
    src/nodes/CardHolder.cpp
    src/nodes/ElixirBar.cpp
    src/nodes/GameNode.cpp

    src/scenes/Scene.cpp
    src/scenes/GameScene.cpp

    src/events/MouseEvent.cpp
)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

target_link_libraries(game_ui
    game_core
    raylib
)

target_include_directories(game_ui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/events
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/nodes
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/scenes
)
