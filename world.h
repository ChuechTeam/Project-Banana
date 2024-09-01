//
// Created by cacac on 22/04/2024.
//

#ifndef PROJECT_BANANA_WORLD_H
#define PROJECT_BANANA_WORLD_H

#include "terminal.h"


typedef struct{
    int length;
    int width;
}Map;

struct Entity_list;

typedef struct World_stats{
    //lists
    struct Entity_list* entities_list;
    struct Entity_list* creatures;
    struct Entity_list* foods;


    //map
    Map map;

    int game;

    //next gen
    struct Entity_list* reproduce;


} World_stats;

void world_init(World_stats* world, int map_length, int map_width, int size_entity_list);

void sort_entities_by_type(World_stats* world);

void print_world_lists(World_stats world);

void draw_entity(int type);

void draw_world_entities(World_stats world, Cursor* cursor);

#endif //PROJECT_BANANA_WORLD_H
