cmake_minimum_required(VERSION 3.8)
project(pacman)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Player.hpp Enemy.cpp Enemy.hpp RealPlayer.cpp RealPlayer.hpp)
add_executable(pacman ${SOURCE_FILES})