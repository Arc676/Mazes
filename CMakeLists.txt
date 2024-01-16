cmake_minimum_required(VERSION 3.28)

project(
    "Mazes"
    VERSION 1.0.0
    LANGUAGES C;CXX
    )

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies)
add_subdirectory(lib)
add_subdirectory(src)
