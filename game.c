//
// Created by cacac on 03/07/2024.
//

#include "game.h"
#include "world.h"
#include "entities.h"
#include "macro.h"

void creatures_turn(World_stats* world){
    int n = world->creatures->last_index;
    FOR_LOOP(i, 0, n, 1){
        Entity *entity = world->creatures->entity_list[i];
        if (entity->alive) {
            entity->Creature.goal =
                    closest_entity(entity, world->foods);
            moving_to(entity, entity->Creature.goal->x, entity->Creature.goal->y);
            if (same_coordinates(entity, entity->Creature.goal)) {
                if (entity->Creature.goal->type == FOOD) {
                    entity->Creature.consumed_food++;
                    kill_entity(world, entity->Creature.goal);
                    i--;
                    n--;
                }
            }
        }
        if(entity->Creature.energy <=0){
            kill_entity(world, entity);
            i--;
            n--;
        }
    }
}


void game_loop(World_stats *world) {
    while (world->game) {
        print_world_lists(*world);

        creatures_turn(world);
        if (world->creatures->alive <=0 || world->foods->alive <= 0){
            world->game = 0;
        }
        print_world_lists(*world);
        
    }
}


