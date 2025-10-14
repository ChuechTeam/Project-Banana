//
// Created by cacac on 25/06/2024.
//

#include "world.h"
#include <stdio.h>
#include <stdlib.h>


#include "entities.h"
#include "terminal.h"
#include "macro.h"



void world_init(World_stats* world, int map_height, int map_width, int size_entity_list){
    world->entities_list = malloc(sizeof(Entity_list));
    list_init(world->entities_list, size_entity_list);

    world->creatures = malloc(sizeof(Entity_list));
    list_init(world->creatures, size_entity_list);
    world->creatures->type = CREATURE;

    world->foods = malloc(sizeof(Entity_list));
    list_init(world->foods, size_entity_list);
    world->foods->type = FOOD;

    world->reproduce = malloc(sizeof(Entity_list));
    list_init(world->reproduce, size_entity_list);
    world->reproduce->type = CREATURE;


    world->map.x=10;
    world->map.y=10;
    world->map.height=map_height;
    world->map.width = map_width;
    world->food=0;


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

void draw_entity(int type){
    switch (type)
    {
    case CREATURE:
        printf("%s%s%s", C_RED, "\u25CF", C_WHT);
        break;
    case FOOD:
        printf("%s%s%s", C_GRN, "\u25CF", C_WHT);
        break;
    default:
        break;
    }
}

void draw_world_entities(World_stats world, Cursor* cursor){
    for (int i = 0; i< world.entities_list->last_index;i++){
        Entity* entity = world.entities_list->entity_list[i];
        if (entity->alive){
            cursor_move_to(cursor, entity->x+world.map.x, entity->y+world.map.y);
            draw_entity(entity->type);
        }
    }
    cursor->x = 0;
    cursor->y = world.map.width + 3;
    
}
