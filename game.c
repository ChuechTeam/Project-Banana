//
// Created by cacac on 03/07/2024.
//

#ifdef _WIN32
#define windows
#elif defined(__linux__)
#endif

#include "game.h"
#include "world.h"
#include "entities.h"
#include "macro.h"
#include "terminal.h"
#include "graphic.h"

// Init the game with the number of food and creatures
void game_init(World_stats *world, int food, int creature) {
    fill_list(world, world->reproduce, creature, CREATURE);
    world->food = food;
}

//Creature turns, which means they will fond the closest food and move towards it
void creatures_turn(World_stats *world, Cursor *cursor) {
    for (int i = 0; i < world->creatures->last_index; i++) {

        if (world->foods->alive <= 0) {
            return;
        }

        Entity *entity = world->creatures->entity_list[i];
        if (entity->alive) {
            entity->Creature.goal = closest_entity(entity, world->foods);
            if (same_coordinates(entity, entity->Creature.goal)) {
                if (entity->Creature.goal->type == FOOD && entity->Creature.goal->alive) {
                    entity->Creature.consumed_food++;
                    entity->Creature.goal->alive = 0;
                    world->foods->alive--;
                    world->entities_list->alive--;
                }
            } else {
                moving_to(entity, entity->Creature.goal->x, entity->Creature.goal->y);
                if (same_coordinates(entity, entity->Creature.goal)) {
                    if (entity->Creature.goal->type == FOOD && entity->Creature.goal->alive) {
                        entity->Creature.consumed_food++;
                        entity->Creature.goal->alive = 0;
                        world->foods->alive--;
                        world->entities_list->alive--;
                    }
                }

            }

            if (entity->Creature.energy <= 0) {
                entity->alive = 0;
                world->creatures->alive--;
                world->entities_list->alive--;
            }
        }
    }
}
//take the entities from the reproduction list and "put them into the world" (add them to the entities list)
void reproduction(pWorld_stats world) {
    for (int i = 0; i < world->reproduce->last_index; i++) {
        insert_Entity_to_list(world->entities_list, world->reproduce->entity_list[i]);
        insert_Entity_to_list(world->creatures, world->reproduce->entity_list[i]);
        world->reproduce->entity_list[i]=NULL;
    }
    world->reproduce->last_index = 0;
    world->reproduce->alive = 0;

}

//take the creatures who can reproduce and put their offspring in the reproduction list, for now, the ratio is one offspring per food consumed
void to_next_gen(World_stats *world) {
    for (int i = 0; i < world->creatures->last_index; i++) {
        if (world->creatures->entity_list[i]->Creature.consumed_food > 0) {
            for (int j = 0; j < world->creatures->entity_list[i]->Creature.consumed_food; j++) {
                Entity *entity = create_entity(CREATURE);
                entity->Creature.base_energy = world->creatures->entity_list[i]->Creature.base_energy;
                entity->Creature.energy = entity->Creature.base_energy;
                entity->Creature.speed = world->creatures->entity_list[i]->Creature.speed;

                mutation(entity);
                insert_Entity_to_list(world->reproduce, entity);
            }
        }
    }
}

//a game tour, or a generation, that means the creatures will move and eat until there is no more food or creatures
void game_tour(World_stats *world, Cursor *cursor) {

    //setup the environment
    if (world->reproduce->last_index > 0) {
        empty_list(world->entities_list);
        world->creatures->alive = 0;
        world->creatures->last_index = 0;
        world->foods->alive = 0;
        world->foods->last_index = 0;

        reproduction(world);


        fill_list(world, world->foods, world->food, FOOD);
        random_position_list(world->map, world->entities_list);
    }
    while (world->creatures->alive > 0 && world->foods->alive > 0) {

        print_entitites_list_value(world->creatures, cursor, ALIVE);
        print_board(world, cursor);
        creatures_turn(world, cursor);
        waiting();
    }
    to_next_gen(world);
}


void game_loop(World_stats *world, Cursor *cursor) {
    int i = 0;
    while (world->game && world->reproduce->last_index > 0 && i < 10) {
        game_tour(world, cursor);
        i++;
    }
    //PING;
    //print_entity_value(*world->creatures->entity_list[0], CONSUMED_FOOD);
    //print_entity_value(*world->creatures->entity_list[1], CONSUMED_FOOD);
    //printf("%d\n", world->entities_list->alive);
}


