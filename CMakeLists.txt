cmake_minimum_required(VERSION 3.16)
project(Project_Banana)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_Banana main.cpp
        Entities.cpp
        Entities.hpp
        EntitiesManager.cpp
        EntitiesManager.hpp
        World.cpp
        World.hpp
        Vec2.hpp)
