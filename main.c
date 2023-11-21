#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "creature.h"
#include "food.h"

typedef struct{
    int length;
    int width;
}Map;

void move_creature(Creature creature){

}

int main() {
    srand(time(NULL));

    Map map;
    map.length = 100;
    map.width = 100;

    CreatureList *creature_list = malloc(sizeof(CreatureList));
    creature_list->next = NULL;
    creature_list->creature = creature_init();

    creature_list = create_x_entities(creature_list, 4);

    print_creature_list(creature_list);

    init_position_creature(creature_list, map.length,map.width);

    print_creature_list(creature_list);



    FoodList *food_list = malloc(sizeof(FoodList));
    food_list->next = NULL;
    food_list->food = food_init();

    food_list = create_x_foods(food_list, 4);

    print_food_list(food_list);

    init_position_food(food_list, map.length,map.width);

    print_food_list(food_list);

    CreatureTreeX* creatureTreeX = createTreeX(creature_list->creature);
    listeXToTree(creatureTreeX, creature_list->next);
    print_tree_x(creatureTreeX);

    delete_creature_list(creature_list);
    free(creature_list);
    delete_food_list(food_list);
    free(food_list);


    return 0;
}