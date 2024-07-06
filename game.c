//
// Created by cacac on 03/07/2024.
//

#include "game.h"
#include "world.h"
#include "entities.h"

void creatures_turn(World_stats* world){
    int alive = world->creatures->last_index;
    for (int i = 0; i < world->creatures->last_index; i++) {
        Entity *entity = world->creatures->entity_list[i];
        if (entity->alive) {
            entity->Creature.goal =
                    closest_entity(entity, world->foods);
            moving_to(entity, entity->Creature.goal->x, entity->Creature.goal->y);
            if (same_coordinates(entity, entity->Creature.goal)) {
                if (entity->Creature.goal->type == FOOD) {
                    entity->Creature.consumed_food++;
                    kill_entity(world, entity->Creature.goal);
                }
            }
        }
        if(entity->Creature.energy <=0){
            kill_entity(world, entity);
            alive --;
        }
    }
}


void game_loop(World_stats *world) {
    while (world->game) {
        print_world_lists(*world);

        creatures_turn(world);

        print_world_lists(*world);
        
    }
}


