cmake_minimum_required (VERSION 3.24)

project (royale LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 23)

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

#find_package(raylib REQUIRED)

add_executable(game
    main.cpp
 )

 #           START OF TEMP
#############################
#############################

add_executable(server src/royale/network/server.cpp)
add_executable(client src/royale/network/client.cpp)

target_sources(server PRIVATE
    src/royale/network/server.cpp
    src/royale/network/NetUtils.cpp
)

target_sources(client PRIVATE
    src/royale/network/client.cpp
    src/royale/network/NetUtils.cpp
)

target_include_directories(client PRIVATE
    include/royale/network
)

target_include_directories(server PRIVATE
    include/royale/network
)

target_link_libraries(server
    ws2_32
)

target_link_libraries(client
    ws2_32
)

#           END OF TEMP
#############################
#############################

 target_sources(game PRIVATE
    src/application.cpp
    src/royale/game.cpp
    src/royale/events/event.cpp
    src/royale/events/cardPlacedEvent.cpp
    src/gameRenderer.cpp
    src/applicationView.cpp
    src/royale/cardManager.cpp
    src/royale/elixirManager.cpp
    src/royale/clock.cpp
    src/royale/game/towerManager.cpp
    src/royale/game/tower.cpp
    src/royale/common/gameObject.cpp
    src/royale/network/client.cpp
    src/royale/network/server.cpp
    src/royale/network/NetUtils.cpp
 )

target_include_directories(game PRIVATE
    include
    include/royale
    include/royale/events
    include/royale/common
    include/royale/cards
    include/royale/ui
    include/royale/game
    include/royale/network
)

target_link_libraries(game
    raylib
    ws2_32
)

# Copy resources folder to build directory
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets  # Source directory
    ${CMAKE_BINARY_DIR}         # Destination directory
)

add_dependencies(game CopyResources)