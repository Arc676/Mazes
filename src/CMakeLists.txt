set(SRCS
    maze.cpp
    player.cpp
    render.cpp
    settings.cpp
    main.cpp
    )
add_executable(mazes-bin ${SRCS})
target_include_directories(mazes-bin PUBLIC
    ${SRC_LIBMAZES}/..
    ${imgui_SRC}
    ${imgui_SRC}/backends)
target_link_libraries(mazes-bin PUBLIC imgui SDL2 mazes)
set_target_properties(mazes-bin PROPERTIES OUTPUT_NAME mazes)
