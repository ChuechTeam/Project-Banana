//
// Created by cacac on 22/04/2024.
//

#ifndef PROJECT_BANANA_WORLD_H
#define PROJECT_BANANA_WORLD_H
#include "entities.h"

typedef struct{
    int length;
    int width;
}Map;

typedef struct World_stats{
    //lists
    Entity_list entities_list;
    Entity_list creatures;
    Entity_list foods;


    //map
    Map map;


} World_stats;

void world_init(World_stats* world, int map_length, int map_width, int size_entity_list);


void sort_entities_by_type(World_stats* world);





#endif //PROJECT_BANANA_WORLD_H
