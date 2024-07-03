cmake_minimum_required(VERSION 3.16)
project(Project_Banana C)

set(CMAKE_C_STANDARD 11)



add_executable(Project_Banana
        main.c entities.h entities.c macro.h
        world.h
        world.c
        world.c)



# Détection du système d'exploitation
if (WIN32)
    # Options de compilation pour Windows
    add_compile_options(-Wall)
    set(LINK_LIBS ws2_32)
elseif (UNIX AND NOT APPLE)
    # Options de compilation pour Linux
    add_compile_options(-Wall -m)
    set(LINK_LIBS m)
endif()

target_link_libraries(Project_Banana ${LINK_LIBS})