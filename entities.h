//
// Created by cacac on 18/12/2023.
//

#ifndef PROJECT_BANANA_ENTITIES_H
#define PROJECT_BANANA_ENTITIES_H

#include <stdio.h>
#include <stdlib.h>
#include "world.h"

enum entity_type {
    DEFAULT, CREATURE, FOOD
};



typedef struct Entity {
    int type; // 0 = none/null ; 1 = creature ; 2 = food
    int index; //index in entities_list

    //commun
    int x;
    int y;

    union {
        struct {
            //struct Entity* goal;
            double speed;
            double energy;
            int consumed_food;
        } Creature;


        struct {

        } Food;
    };
} Entity;


typedef struct Entity_list {
    Entity *entity_list;
    int last_index; //last empty index (aka index(last_element)+1)
    int capacity;
} Entity_list;





void entity_init(Entity *entity);

Entity *create_entity(int type);

void list_init(Entity_list* list, int size);

int fill_list(Entity_list* list, int number, int type);

int insert_Entity_to_list(Entity_list* list, Entity entity);

void print_list(Entity_list* list);

float distance_to(Entity* entity, int x, int y);

Entity* closest_entity(Entity* entity, Entity_list* list);

//void random_position_entity(Map map, Entity* entity);

//void random_position_list(Map map, Entity_list* list);

#endif //PROJECT_BANANA_ENTITIES_H
