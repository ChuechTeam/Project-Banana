//
// Created by cacac on 25/06/2024.
//

#include "world.h"
#include <stdio.h>
#include <stdlib.h>


#include "entities.h"
#include "terminal.h"

void world_map_init(World_stats* world, int map_length, int map_width){
    world->world = malloc(sizeof(int *) * map_length);
    for (int i = 0; i<map_length;i++){
        world->world[i] = malloc (sizeof(int) * map_width);
    }
}

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
    
    world_map_init(world, map_length, map_width);


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


void fill_world_map(World_stats* world){
    for(int i =0;i<world->entities_list->last_index;i++){
        Entity* entity = world->entities_list->entity_list[i];
        if(entity->alive){
            world->world[entity->x][entity->y] = entity->type;
        }
    }
}


void free_world_list(World_stats* world){
    for (int i =0 ; i< world->entities_list->last_index;i++){
        free(world->entities_list->entity_list[i]);
    }
    free(world->entities_list);
    free(world->creatures);
    free(world->foods);
}

void free_world_map(World_stats* world){
    for (int i =0;i<world->map.length;i++){
        free(world->world[i]);
    }
    free(world->world);
}

void print_world_map(World_stats world, Cursor* cursor){
    print_rect(world.map.length+3, world.map.width+3, 3);
    for (int j = 0; j< world.map.width;j++){
        for (int i = 0;i<world.map.length;i++){
            switch (world.world[i][j])
            {
            case 0:
                break;
            case 1:
                drawText(i+1, j+1, "\u25CF", 1);
                break;
            case 2:
                drawText(i+1, j+1, "\u25CF", 2);
            
            default:
                break;
            }
        }
    }
    cursor->x = 0;
    cursor->y = world.map.width + 3;
    
}
