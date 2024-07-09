//
// Created by cacac on 25/06/2024.
//

#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include "entities.h"

void world_init(World_stats* world, int map_length, int map_width, int size_entity_list){
    world->entities_list = malloc(sizeof(Entity_list));
    world->creatures = malloc(sizeof(Entity_list));
    world->foods = malloc(sizeof(Entity_list));
    list_init(world->entities_list, size_entity_list);
    list_init(world->creatures, size_entity_list);
    world->creatures->type = CREATURE;
    list_init(world->foods, size_entity_list);
    world->foods->type = FOOD;

    world->map.length=map_length;
    world->map.width = map_width;


    world->game = 1;
}

void sort_entities_by_type(World_stats* world){
    for (int i = 0; i < world->entities_list->last_index; i++){
        if (world->entities_list->entity_list[i]->sub_index == -1){
            switch (world->entities_list->entity_list[i]->type) {
                case CREATURE:
                    insert_Entity_to_list(world->creatures,
                                        world->entities_list->entity_list[i]);
                    break;
                case FOOD:
                    insert_Entity_to_list(world->foods, world->entities_list->entity_list[i]);
                    break;
            }
        }
    }
}

void print_world_lists(World_stats world){
    print_list(world.entities_list);
    print_list(world.creatures);
    print_list(world.foods);
}



