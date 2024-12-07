cmake_minimum_required(VERSION 3.29)
project(UnitTests)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 20)

add_executable(UnitTests main.cpp
		Cell_Test.cpp
		File_Test.cpp
		Grid_Test.cpp
		Performance_Test.cpp
		../src/grid.cpp
		../src/grid.h
		../src/FileManager.h
		../src/FileManager.cpp
		../src/cell.cpp
		../src/cell.h
		../src/game.cpp
		../src/game.h
		../src/Interface.cpp
		../src/Interface.h

)

target_link_libraries(UnitTests sfml-graphics)
