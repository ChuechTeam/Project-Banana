//
// Created by cacac on 25/06/2024.
//

#include "world.h"
#include <stdio.h>
#include <stdlib.h>


#include "entities.h"
#include "terminal.h"



void world_init(World_stats* world, int map_length, int map_width, int size_entity_list){
    world->entities_list = malloc(sizeof(Entity_list));
    world->creatures = malloc(sizeof(Entity_list));
    world->foods = malloc(sizeof(Entity_list));
    world->reproduce = malloc(sizeof(Entity_list));
    list_init(world->entities_list, size_entity_list);
    list_init(world->creatures, size_entity_list);
    world->creatures->type = CREATURE;
    list_init(world->foods, size_entity_list);
    world->foods->type = FOOD;
    list_init(world->reproduce, size_entity_list);
    world->reproduce->type = CREATURE;

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



void print_world_entities(World_stats world, Cursor* cursor){
    print_rect(world.map.length+2, world.map.width+2, 3);
    for (int i = 0; i< world.entities_list->last_index;i++){
        Entity* entity = world.entities_list->entity_list[i];
        if (entity->alive){
            drawText(entity->x + 1, entity->y + 1, "\u25CF", entity->type);
        }
    }
    cursor->x = 0;
    cursor->y = world.map.width + 3;
    
}
