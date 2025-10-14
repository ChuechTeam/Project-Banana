#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "entities.h"
#include "world.h"
#include "game.h"
#include "macro.h"
#include "terminal.h"
#include "graphic.h"


int main() {
    printf("\n\n\n\n\n\n\n\n\n");
    srand(time(NULL));

    setlocale(LC_ALL, "");

    
    int map_height = 10;
    int map_width = 10;


    World_stats world;
    Cursor cursor;
    cursor_init(&cursor);
    clear_all(&cursor);
    
    world_init(&world, map_height, map_width, 10);

    game_init(&world, 10, 1);

    print_list(world.reproduce);
    waiting();




    game_loop(&world, &cursor);

    /*
    while(1){
        world_init(&world, map_length, map_width, 10);
        fill_list(&world, world.creatures, 2, CREATURE);
        fill_list(&world, world.entities_list, 7, FOOD);
        
        random_position_list(world.map, world.entities_list);
        //print_entities_list(world.creatures);
        
        /*
        int alive = world.creatures->alive;
        FOR_LOOP(i, 0, alive, 1){
            kill_entity(&world, world.creatures->entity_list[i]);
            i --;
            alive --;
        }*//*
        //print_entities_list(world.creatures);
        

        sort_entities_by_type(&world);



        
        game_loop(&world);
        free_world_list(&world);
    }

    */



    print_board(&world, &cursor);
    waiting();
    PING;
    print_entitites_list_value(world.creatures, &cursor, CONSUMED_FOOD);
    print_list(world.reproduce);
    waiting();
    // Terminer ncurses
    return 0;
}