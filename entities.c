//
// Created by cacac on 18/12/2023.
//

#include "entities.h"
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "world.h"
#include <math.h>


void entity_init(Entity *entity) {
    entity->x = 0;
    entity->y = 0;
    switch (entity->type) {
        case CREATURE:
            entity->Creature.speed = 1.0; // Setting the speed of the creature to 1.0
            entity->Creature.energy = 5.0;
            entity->Creature.consumed_food = 0; // Setting initial consumed food to 0
            break;
        case FOOD:

            break;
    }
}

Entity *create_entity(int type) {
    Entity *entity = malloc(sizeof(Entity));
    entity->type = type;
    return entity;
}


/*Init the entity list with chosen size. The size is the number of elements in the list.
 *Choose 0 for the default size, which is 100 elements.*/
void list_init(Entity_list *list, int size) {
    if (size == 0) {
        list->capacity = 100;
    } else {
        list->capacity = size;
    }
    list->entity_list = malloc(sizeof(Entity) * list->capacity);
    list->last_index = 0;
}


/*Fill a list with n number of one type of entities.
 * For exemple, number 6 et entity FOOD will add 6 FOOD entities in the list*/
int fill_list(Entity_list *list, int number, int type) {
    if (number > list->capacity - list->last_index) {
        return OUT_OF_RANGE;
    }
    for (int i = 0; i < number; i++) {
        list->entity_list[list->last_index + i] = *create_entity(type); //add the new entity at the last index
    }
    list->last_index += number;
    return SUCCESS;
}


int insert_Entity_to_list(Entity_list* list, Entity entity){
    if (list->last_index >= list->capacity){
        return OUT_OF_RANGE;
    }

    list->entity_list[list->last_index] = entity;
    list->last_index ++;
    return SUCCESS;
}

/*list all the entities by telling the type*/
void print_list(Entity_list *list) {
    int a;
    for (int i = 0; i < list->last_index; i++) {
        //a = list->entity_list[i].type;
        printf("%d , ", list->entity_list[i].type);
    }
    printf("\n");
}


int moving_to(Entity *entity, int x, int y) {
    // Check if the entity has enough energy to move
    if (entity->Creature.energy > 0) {
        // Calculate the angle towards the target position (x, y)
        double theta = atan2(y - entity->y, x - entity->x);

        // Determine the maximum distance the entity can move
        int range = MIN(entity->Creature.energy, entity->Creature.speed);

        // Update the entity's position
        entity->x = (int) (range * cos(theta));
        entity->y = (int) (range * sin(theta));

        // Reduce the entity's energy by its speed
        entity->Creature.energy -= entity->Creature.speed;
    }
}

float distance_to(Entity* entity, int x, int y){
    return (sqrtf(SQUARE(x - entity->x)+SQUARE(y-entity->y)));
}


//search in the list the closest entity and return its pointer
Entity* closest_entity(Entity* entity, Entity_list* list){
    float closest = distance_to(entity, list->entity_list[0].x, list->entity_list[0].y);
    int index = 0;
    for (int i = 1; i < list->last_index;i++){
        if(closest < distance_to(entity, list->entity_list[i].x, list->entity_list[i].y)){
            closest = distance_to(entity, list->entity_list[i].x, list->entity_list[i].y);
            index = i;
        }
    }
    return &list->entity_list[index];
}

/*
void random_position_entity(Map map, Entity* entity){
    entity->x = rand()% (map.length-1);
    entity->y = rand()% (map.width-1);
}*/
/*
void random_position_list(Map map, Entity_list* list){
    for (int i = 0;i <list->last_index;i++){
        random_position_entity(map, &list->entity_list[i]);
    }
}*/


