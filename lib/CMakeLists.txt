set(SRC_LIBMAZES ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(SRCS
    Generators/generators.cpp
    Generators/random.cpp
    Generators/rdfs.cpp
    Generators/recDiv.cpp
    maze.cpp
    )
add_library(mazes ${SRCS})
target_include_directories(mazes PUBLIC ${SRC_LIBMAZES})
