#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entities.h"
#include "world.h"
#include "game.h"



int main() {
    srand(time(NULL));

    int map_length = 3;
    int map_width = 3;


    World_stats world;
    world_init(&world, map_length, map_width, 10);


    fill_list(world.entities_list, 2, CREATURE);
    fill_list(world.entities_list, 2, FOOD);



    sort_entities_by_type(&world);



    random_position_list(world.map, world.entities_list);
    print_world_lists(world);
    game_loop(&world);

    return 0;
}