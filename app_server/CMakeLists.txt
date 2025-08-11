project (server)

add_executable(server
    main.cpp
)

target_link_libraries(server
    ws2_32
    game_core
)
