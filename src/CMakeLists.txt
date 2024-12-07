cmake_minimum_required(VERSION 3.29)
project(Project_POO_VF)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_POO_VF main.cpp
        grid.cpp
        grid.h
        FileManager.h
        FileManager.cpp
       	cell.cpp
        cell.h
        game.cpp
        game.h
        Interface.cpp
        Interface.h
)

target_link_libraries(Project_POO_VF sfml-graphics)
