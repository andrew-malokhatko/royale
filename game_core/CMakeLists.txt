project (game_core)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(game_core

    src/game.cpp

    src/cards/Card.cpp

    src/game/clock.cpp
    src/game/elixirManager.cpp
    src/game/cardManager.cpp

    src/common/gameObject.cpp

    src/events/event.cpp
    src/events/cardPlacedEvent.cpp

    src/game/towerManager.cpp
    

    src/network/client.cpp
    src/network/server.cpp
    src/network/NetUtils.cpp

    src/network/packets/CardPlacedPacket.cpp
    src/network/packets/PacketHandlerRegistry.cpp
    src/network/packets/CardPlacedPacketHandler.cpp
    src/common/components/AttackComponent.cpp
    src/common/components/HealthComponent.cpp
    src/common/components/MovementComponent.cpp
    src/game/tower.cpp
    src/common/entities/entity.cpp
    src/common/entities/EntityData.cpp
    src/cards/CardData.cpp
  )

target_include_directories(game_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/common/components
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/common/strategies
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/common/entities
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/cards
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/events
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/network
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/network/packets
)

#target_link_libraries(game_core json)
target_link_libraries(game_core PUBLIC nlohmann_json::nlohmann_json)


# Copy resources folder to build directory
add_custom_target(CopyResourcesServer ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources  # Source directory
    $<TARGET_FILE_DIR:server>
)

# Copy resources folder to build directory
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources  # Source directory
    $<TARGET_FILE_DIR:game>
)

add_dependencies(game_core CopyResources)
add_dependencies(game_core CopyResourcesServer)