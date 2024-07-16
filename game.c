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
        if (i< 0){
            break;
        }
        Entity *entity = world->creatures->entity_list[i];
        if (entity->alive) {
            entity->Creature.goal = closest_entity(entity, world->foods);
            moving_to(entity, entity->Creature.goal->x, entity->Creature.goal->y);
            if (same_coordinates(entity, entity->Creature.goal)) {
                if (entity->Creature.goal->type == FOOD) {
                    entity->Creature.consumed_food++;
                    kill_entity(world, entity->Creature.goal);
                    i--;
                    n--;
                }
            }
        
            if(entity->Creature.energy <=0){
                kill_entity(world, entity);
                i--;
                n--;

            }
        }

        
    }
}


void game_loop(World_stats *world) {
    while (world->game) {
        printf("entities : %d\n", world->entities_list->alive);
        printf("creatures : %d\n", world->creatures->alive);
        printf("foods : %d\n", world->foods->alive);
        creatures_turn(world);
        if (world->creatures->alive <=0 || world->foods->alive <= 0){
            world->game = 0;
        }
        
    }
    //PING;
    //print_entity_value(*world->creatures->entity_list[0], CONSUMED_FOOD);
    //print_entity_value(*world->creatures->entity_list[1], CONSUMED_FOOD);
    //printf("%d\n", world->entities_list->alive);
}

//take the creatures who can reproduce (when they ate food) and place them into the list to reproduce for the next gen
void to_next_gen(World_stats* world){
    for (int i= 0;i<world->creatures->last_index;i++){
        if (world->creatures->entity_list[i]->Creature.consumed_food >0){
            world->reproduce->entity_list[world->reproduce->last_index] = world->creatures->entity_list[i];
        }
    }
}
