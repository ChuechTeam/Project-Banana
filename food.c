#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "food.h"


Food *food_init() {
    Food *food = malloc(sizeof(Food)); // Allocating memory for a new Food entity
    food->x = 0; // Setting initial x coordinate to 0
    food->y = 0; // Setting initial y coordinate to 0
    return food; // Returning the initialized food entity
}

FoodList *add_food(FoodList *food_list) {
    FoodList *new_node = malloc(sizeof(FoodList)); // Allocating memory for a new FoodList node
    new_node->food = food_init(); // Initializing a new food entity and assigning it to the node
    new_node->next = food_list; // Setting the next node to the current head of the list
    return new_node; // Returning the updated list with the new food added
}

FoodList* create_x_foods(FoodList *food_list, int x) {
    for (int i = 0; i < x; i++) {
        food_list = add_food(food_list); // Adding x number of food entities to the list
    }
    return food_list; // Returning the updated list with x new food entities added
}

void print_food(Food* food) {
    // Printing the details of a single food entity - its x, y coordinates
    printf("x : %d; y : %d\n", food->x, food->y);
}

void print_food_list(FoodList *food_list) {
    if (food_list->next == NULL) {
        // Printing the details of each food entity in the list by recursively traversing the list
        print_food(food_list->food);
        return;
    }
    print_food_list(food_list->next); // Recursively calling the function for the next food entity
    print_food(food_list->food); // Printing the details of the current food entity
}

void delete_food_list(FoodList *food_list){
    if (food_list->next == NULL){
        free(food_list->food); // Freeing memory for the last food entity in the list
        return;
    }
    free(food_list->next); // Freeing memory for the next node in the list
    free(food_list->food); // Freeing memory for the current food entity
}


void init_position_food(FoodList *food_list, int x, int y) { //Init the position (random) of all entities in an L*l space
    if (food_list->next == NULL){
        food_list->food->x = (rand() % (x - 0)+ 0);
        food_list->food->y = (rand() % (y-0)+0);
        return;
    }
    init_position_food(food_list->next, x, y);
    food_list->food->x = (rand() % (x - 0)+ 0);
    food_list->food->y = (rand() % (y-0)+0);
}





