//
// Created by cacac on 18/12/2023.
//

#include "entities.h"
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"


void creature_init(Entity *entity) {
    entity->Creature.x = 0; // Setting initial x coordinate to 0
    entity->Creature.y = 0; // Setting initial y coordinate to 0

    entity->Creature.speed = 1.0; // Setting the speed of the creature to 1.0
    entity->Creature.consumed_food = 0; // Setting initial consumed food to 0
}

void food_init(Entity *entity) {
    entity->Food.x = 0;
    entity->Food.y = 0;
}

Entity *create_entity(int type) {
    Entity *entity = malloc(sizeof(Entity));
    entity->type = type;
    switch (type) {
        case CREATURE:
            creature_init(entity);
            break;
        case FOOD:
            food_init(entity);
            break;
        default:
            entity->type=0;
            break;
    }
    return entity;
}

/*Init the entity list with chosen size. The size is the number of elements in the list.
 *Choose 0 for the default size, which is 100 elements.*/
void list_init(Entity_list* list, int size) {
    if(size==0){
        list->capacity = 100;
    }
    else{
        list->capacity=size;
    }
    list->entity_list = malloc(sizeof(Entity) * list->capacity);
    list->last_index = 0;
}


/*Fill a list with n number of one type of entities.
 * For exemple, number 6 et entity FOOD will add 6 FOOD entities in the list*/
int fill_list(Entity_list* list, int number, int type){
    if(number>list->capacity-list->last_index){
        return OUT_OF_RANGE;
    }
    for (int i = 0 ;i<number; i++){
        list->entity_list[list->last_index +i] = *create_entity(type); //add the new entity at the last index
    }
    list->last_index += number;
    return SUCCESS;
}

/*list all the entities by telling the type*/
void print_list(Entity_list* list){
    int a;
    for(int i =0;i < list->last_index;i++){
        //a = list->entity_list[i].type;
        printf("%d , ", list->entity_list[i].type);
    }
    printf("\n");
}