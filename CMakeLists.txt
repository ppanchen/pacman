cmake_minimum_required(VERSION 3.8)
project(pacman)

set(CMAKE_CXX_STANDARD 14)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES
        main.cpp
        Player.hpp
        Player.cpp
        Enemy.cpp
        Enemy.hpp
        RealPlayer.cpp
        RealPlayer.hpp
        Playfield.cpp
        Playfield.hpp)
add_executable(pacman ${SOURCE_FILES})
target_link_libraries(pacman ${CURSES_LIBRARIES})