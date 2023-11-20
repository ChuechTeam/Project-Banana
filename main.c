#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "creature.h"
#include "food.h"


int main() {
    srand(time(NULL));
    CreatureList *creature_list = malloc(sizeof(CreatureList));
    creature_list->next = NULL;
    creature_list->creature = creature_init();

    creature_list = create_x_entities(creature_list, 4);

    print_creature_list(creature_list);

    init_position_creature(creature_list, 100,100);

    print_creature_list(creature_list);



    FoodList *food_list = malloc(sizeof(FoodList));
    food_list->next = NULL;
    food_list->food = food_init();

    food_list = create_x_foods(food_list, 4);

    print_food_list(food_list);

    init_position_food(food_list, 100, 100);

    print_food_list(food_list);


    delete_creature_list(creature_list);
    free(creature_list);
    delete_food_list(food_list);
    free(food_list);


    return 0;
}