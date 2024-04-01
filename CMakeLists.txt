cmake_minimum_required(VERSION 3.16)
project(Project_Banana C)

set(CMAKE_C_STANDARD 11)

add_executable(Project_Banana
        main.c entities.h entities.c macro.h)
