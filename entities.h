//
// Created by cacac on 18/12/2023.
//

#ifndef PROJECT_BANANA_ENTITIES_H
#define PROJECT_BANANA_ENTITIES_H

#include <stdio.h>
#include <stdlib.h>

enum entity_type {
    DEFAULT, CREATURE, FOOD
};

typedef struct Entity {
    int type; // 0 = none/null ; 1 = creature ; 2 = food
    union {
        struct {
            int x;
            int y;

            double speed;
            int energy;
            int consumed_food;
        } Creature;


        struct {
            int x;
            int y;
        } Food;
    };
} Entity;

typedef struct Entity_list {
    Entity *entity_list;
    int last_index; //last empty index (aka index(last_element)+1)
    int capacity;
} Entity_list;




void creature_init(Entity *entity);

void food_init(Entity *entity);

Entity *create_entity(int type);

void list_init(Entity_list* list, int size);

int fill_list(Entity_list* list, int number, int type);

void print_list(Entity_list* list);

#endif //PROJECT_BANANA_ENTITIES_H
