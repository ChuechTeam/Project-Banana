//
// Created by cacac on 03/07/2024.
//

#include "game.h"
#include "world.h"
#include "entities.h"  
#include "macro.h"
#include "terminal.h"

void creatures_turn(World_stats* world, Cursor* cursor){
    for (int i =0; i<world->creatures->last_index;){
        clear_all(cursor);
        draw_rect(cursor, world->map.length+2, world->map.width+2);
        draw_world_entities(*world, cursor);
        

        cursor_move_to(cursor, 0, world->map.width + 4);
        print_entity_value(*world->creatures->entity_list[0], COORDINATES);
        waiting();

        if (world->foods->alive <= 0){
            return;
        }

        Entity *entity = world->creatures->entity_list[i];
        if (entity->alive) {
            entity->Creature.goal = closest_entity(entity, world->foods);
            moving_to(entity, entity->Creature.goal->x, entity->Creature.goal->y);
            if (same_coordinates(entity, entity->Creature.goal)) {
                if (entity->Creature.goal->type == FOOD && entity->Creature.goal->alive) {
                    entity->Creature.consumed_food++;
                    entity->Creature.goal->alive = 0;
                    world->foods->alive --;
                    world->entities_list->alive --;
                }
            }
        
            if(entity->Creature.energy <=0){
                entity->alive = 0;
                world->creatures->alive --;
                world->entities_list->alive --;
            }
        }   
    }
}


void game_loop(World_stats *world, Cursor* cursor) {
    while (world->game) {
        
        creatures_turn(world, cursor);
        waiting();
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
