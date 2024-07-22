//
// Created by cacac on 03/07/2024.
//

#ifndef PROJECT_BANANA_GAME_H
#define PROJECT_BANANA_GAME_H
#include "world.h"
#include "entities.h"
#include "terminal.h"

void creatures_turn(World_stats* world, Cursor* cursor);

void game_loop(World_stats * world, Cursor* cursor);

void to_next_gen(World_stats* world);

#endif //PROJECT_BANANA_GAME_H
