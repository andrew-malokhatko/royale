project (game_core)


add_library(game_core

    src/game.cpp
    src/clock.cpp
    src/elixirManager.cpp
    src/cardManager.cpp

    src/common/gameObject.cpp

    src/events/event.cpp
    src/events/cardPlacedEvent.cpp

    src/game/towerManager.cpp
    src/game/tower.cpp

    src/network/client.cpp
    src/network/server.cpp
    src/network/NetUtils.cpp
    src/network/packets/CardPlacedPacket.cpp
 "src/network/packets/PacketHandlerRegistry.cpp" "src/network/packets/CardPlacedPacketHandler.cpp")

target_include_directories(game_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/cards
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/events
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/maps
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/network
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/network/packets
)