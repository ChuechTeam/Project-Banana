//
// Created by cacac on 18/12/2023.
//

#include "entities.h"
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include <math.h>
#include "world.h"


void entity_init(Entity *entity) {
    entity->x = 0;
    entity->y = 0;
    entity->alive = 1;
    entity->index = -1;
    entity->sub_index = -1;
    switch (entity->type) {
        case CREATURE:
            entity->Creature.goal=NULL;
            entity->Creature.speed = 1.0; // Setting the speed of the creature to 1.0
            entity->Creature.base_energy = 5.0;
            entity->Creature.energy = entity->Creature.base_energy; // Setting the energy of the creature to 5.0
            entity->Creature.consumed_food = 0; // Setting initial consumed food to 0
            break;
        case FOOD:

            break;
    }
}

Entity *create_entity(int type) {
    Entity *entity = malloc(sizeof(Entity));
    entity->type = type;
    entity_init(entity);
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
    list->type = DEFAULT;
    list->entity_list = malloc(sizeof(Entity) * list->capacity);
    list->last_index = 0;
    list->alive = 0;
}


/*Fill a list with n number of one type of entities.
 * For exemple, number 6 et entity FOOD will add 6 FOOD entities in the list*/
int fill_list(World_stats* world, Entity_list* list, int number, int type) {
    if (number > list->capacity - list->last_index) {
        return OUT_OF_RANGE;
    }
    if (type != list->type){
        return WRONG_TYPE;
    }
    for (int i = 0; i < number; i++) {
        Entity* entity = create_entity(type);
        insert_Entity_to_list(list, entity);
        if(list->type != DEFAULT && list != world->reproduce){
            world->entities_list->entity_list[world->entities_list->last_index] = entity;
            entity->index = world->entities_list->last_index;
            world->entities_list->alive++;
            world->entities_list->last_index++;
        }
    }
    return SUCCESS;
}


int insert_Entity_to_list(Entity_list* list, Entity* entity){
    if (list->last_index >= list->capacity){
        return OUT_OF_RANGE;
    }
    
    if (list->type == DEFAULT){
        entity->index = list->last_index;
        list->entity_list[list->last_index] = entity;
    }
    else if (list->type == entity->type){
            entity->sub_index = list->last_index;
            list->entity_list[list->last_index] = entity;
    }
    else {
        return WRONG_TYPE;
    }
    list->alive ++;
    list->last_index ++;
    return SUCCESS;
}

/*list all the entities by telling the type*/
void print_list(Entity_list *list) {
    printf("list:%d|", list->type);
    //int a;
    for (int i = 0; i < list->last_index; i++) {
        //a = list->entity_list[i].type;
        printf("%d , ",list->entity_list[i]->type);
    }
    printf("\n");
}


void moving_to(Entity *entity, int x, int y) {
    /*//debug
    entity->Creature.speed = 3;
    entity->Creature.energy = 5;
    entity->x=5;
    entity->y=3;
    x = entity->x-2;
    y = entity->y+1;*/

    // Check if the entity has enough energy to move
    if (entity->Creature.energy > 0) {
        // Calculate the angle towards the target position (x, y)
        double theta = atan2(y - entity->y, x - entity->x);
        if (theta<0){
            theta+=2*M_PI;
        }

        // Determine the maximum distance the entity can move
        int norm = (int) sqrt(SQUARE(y - entity->y)+SQUARE(x - entity->x));
        int range = MIN(norm,MIN(entity->Creature.energy, entity->Creature.speed));

        // Update the entity's position
        entity->x += (int) NEAREST_INT(range * (cos(theta)));
        entity->y += (int) NEAREST_INT(range * (sin(theta)));

        // Reduce the entity's energy by its speed
        entity->Creature.energy -= entity->Creature.speed;
    }
}

float distance_to(Entity* entity, int x, int y){
    return (sqrtf(SQUARE(x - entity->x)+SQUARE(y-entity->y)));
}


//search in the list the closest entity and return its pointer
Entity* closest_entity(Entity* entity, Entity_list* list){
    if (list->alive == 0){
        return entity;
    }
    float closest = 0;
    int index = 0;
    for(int i = 0; i < list->last_index;i++){
        if(list->entity_list[i]->alive){
            closest = distance_to(entity, list->entity_list[i]->x, list->entity_list[i]->y);
            index = i;
            break;
        }
    }

    for (int i = index+1; i < list->last_index;i++){
        if(list->entity_list[i]->alive){
            if(closest > distance_to(entity, list->entity_list[i]->x, list->entity_list[i]->y)){
                closest = distance_to(entity, list->entity_list[i]->x, list->entity_list[i]->y);
                index = i;
            }
        }
    }
    return list->entity_list[index];
}

//print the value you want, see the enum entity_value to know what to write for type
//exemple : print_entity_value(entity, COORDINATES) => print x and y coordinates
void print_entity_value(Entity entity, int type) {
    int show_type = 0;
    switch (type) {
        case TYPE:
            printf("%s%d\n", (show_type ? "TYPE: " : ""), entity.type);
            break;
        case INDEX:
            printf("%s%d\n", (show_type ? "INDEX: " : ""), entity.index);
            break;
        case SUB_INDEX:
            printf("%s%d\n", (show_type ? "SUB_INDEX: " : ""), entity.sub_index);
            break;
        case ALIVE:
            printf("%s%d\n", (show_type ? "ALIVE: " : ""), entity.alive);
            break;
        case COORDINATES:
            printf("%sx:%d y:%d\n", (show_type ? "COORDINATES: " : ""), entity.x, entity.y);
            break;
        case GOAL:
            if (entity.Creature.goal == NULL) {
                break;
            }
            printf("%sx:%d y:%d\n", (show_type ? "GOAL COORDINATES: " : ""), entity.Creature.goal->x, entity.Creature.goal->y);
            break;
        case SPEED:
            printf("%s%0.2f\n", (show_type ? "SPEED: " : ""), entity.Creature.speed);
            break;
        case ENERGY:
            printf("%s%0.2f\n", (show_type ? "ENERGY: " : ""), entity.Creature.energy);
            break;
        case CONSUMED_FOOD:
            printf("%s%d\n", (show_type ? "CONSUMED_FOOD: " : ""), entity.Creature.consumed_food);
            break;
    }
}


void print_entity(Entity entity){
    printf("----------------------\n");
    print_entity_value(entity, TYPE);
    print_entity_value(entity, ALIVE);
    print_entity_value(entity, COORDINATES);
    print_entity_value(entity, INDEX);
    print_entity_value(entity, SUB_INDEX);
    switch (entity.type) {
        case CREATURE:
            print_entity_value(entity, GOAL);
            print_entity_value(entity, SPEED);
            print_entity_value(entity, ENERGY);
            print_entity_value(entity, CONSUMED_FOOD);
            break;
        case FOOD:
            break;
        default:
            break;
    }
    printf("----------------------\n");
}

void random_position_entity(Map map, Entity* entity){
    entity->x = rand()% (map.width);
    entity->y = rand()% (map.height);
}

void random_position_list(Map map, Entity_list* list){
    for (int i = 0;i <list->last_index;i++){
        random_position_entity(map, list->entity_list[i]);
    }
}

void print_entities_list(Entity_list* list){
    for (int i =0;i<list->last_index;i++){
        print_entity(*list->entity_list[i]);
    }
}

void print_entitites_list_value(Entity_list* list, Cursor* cursor, int type){
    cursor_move_to(cursor, cursor->x, cursor->y);
    for (int i = 0;i<list->last_index;i++){
        printf("%d : ", i);
        print_entity_value(*list->entity_list[i], type);
    }
}

int same_coordinates(Entity* a, Entity* b){
    return (a->x == b->x && a->y ==b->y);
}

void move_to_end(World_stats* world, Entity* entity){
    
}

void kill_entity(World_stats* world, Entity* entity){
    if(entity->alive == 0){
        return;
    }
    int index = entity->index;
    entity->alive = 0;
    world->entities_list->entity_list[index] = world->entities_list->entity_list[world->entities_list->alive-1];
    world->entities_list->entity_list[index]->index = index;
    world->entities_list->entity_list[world->entities_list->alive-1] = entity;
    world->entities_list->entity_list[world->entities_list->alive-1]->index = world->entities_list->alive -1;
    world->entities_list->alive --;

    switch (entity->type) {
        case(CREATURE):
            world->creatures->entity_list[entity->sub_index] = world->creatures->entity_list[world->creatures->alive-1];
            world->creatures->entity_list[entity->sub_index]->sub_index = entity->sub_index;
            world->creatures->entity_list[world->creatures->alive-1] = entity;
            world->creatures->entity_list[world->creatures->alive-1]->sub_index = world->creatures->alive -1;
            world->creatures->alive --;
            break;
        case(FOOD):
            world->foods->entity_list[entity->sub_index] = world->foods->entity_list[world->foods->alive-1];
            world->foods->entity_list[entity->sub_index]->sub_index = entity->sub_index;
            world->foods->entity_list[world->foods->alive-1] = entity;
            world->foods->entity_list[world->foods->alive-1]->sub_index = world->foods->alive -1;
            world->foods->alive --;
            break;
    }
}

void free_entity(World_stats* world, Entity* entity){
    if(entity->alive){
        world->entities_list->alive --;
    } 
    kill_entity(world, entity);
    free(world->entities_list->entity_list[entity->index]);
}

void empty_list(Entity_list* list){
    for (int i = 0; i<list->last_index;i++){
        free(list->entity_list[i]);
    }
    list->last_index = 0;
    list->alive = 0;
}

void mutation(Entity* entity){
    entity->Creature.speed += (rand()%3-1);
    entity->Creature.base_energy += (rand()%3-1);
}