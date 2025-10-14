//
// Created by cacac on 03/07/2024.
//

#ifndef PROJECT_BANANA_GAME_H
#define PROJECT_BANANA_GAME_H

#ifdef _WIN32
    #define windows
#elif defined(__linux__)
#endif

#include "world.h"
#include "entities.h"
#include "terminal.h"

void game_init(World_stats *world, int food, int creature);

void creatures_turn(World_stats *world, Cursor *cursor);

void reproduction(pWorld_stats world);

void to_next_gen(World_stats *world);

void game_tour(World_stats* world, Cursor* cursor);

void game_loop(World_stats *world, Cursor *cursor);



#endif //PROJECT_BANANA_GAME_H
