cmake_minimum_required(VERSION 3.20)
project(EraForge)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.2.0
)

FetchContent_MakeAvailable(fmt)

add_executable(EraForge main.cpp
        Game.cpp
        Game.h
        Unit.cpp
        Unit.h
        Civilization.cpp
        Civilization.h
        City.cpp
        City.h
        Citystate.cpp
        Citystate.h
        Tile.cpp
        Tile.h
        Building.cpp
        Building.h
        Globals.h)

target_link_libraries(EraForge PRIVATE fmt::fmt)