#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entities.h"
#include "world.h"



int main() {
    srand(time(NULL));

    int map_length = 10;
    int map_width = 10;


    World_stats world;
    world_init(&world, 10, map_length, map_width);



    fill_list(world.entities_list, 2, FOOD);
    fill_list(world.entities_list, 2, CREATURE);


    sort_entities_by_type(&world);



    random_position_list(world.map, world.entities_list);

    print_entities_list(*world.creatures);
    print_entities_list(*world.foods);

    for(int i = 0; i < world.creatures->last_index;i++){
        world.creatures->entity_list[i]->Creature.goal = closest_entity(world.creatures->entity_list[i],world.foods);
    }

    print_entities_list(*world.creatures);

    for(int i = 0; i < world.creatures->last_index;i++){
        int x = world.creatures->entity_list[i]->Creature.goal->x;
        int y = world.creatures->entity_list[i]->Creature.goal->y;
        moving_to(world.creatures->entity_list[i], x, y);
    }
    print_entities_list(*world.creatures);


    return 0;
}