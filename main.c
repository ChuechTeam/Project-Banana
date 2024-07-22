#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "entities.h"
#include "world.h"
#include "game.h"
#include "macro.h"
#include "terminal.h"



int main() {
    srand(time(NULL));

    setlocale(LC_ALL, "");

    // Initialiser ncurses
    initscr();                // Commence une session ncurses
    cbreak();                 // Désactiver la mise en mémoire tampon de ligne
    noecho();                 // Ne pas afficher les caractères saisis
    keypad(stdscr, TRUE);     // Activer les touches spéciales comme F1, F2, flèches, etc.

    // Vérifier si le terminal supporte les couleurs
    if (has_colors() == FALSE) {
        endwin();             // Restaurer le terminal à son état normal
        printf("Votre terminal ne supporte pas les couleurs.\n");
        exit(1);
    }

    // Initialiser les couleurs
    start_color();
    
    // Définir les paires de couleurs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);


    int map_length = 10;
    int map_width = 10;


    World_stats world;
    Cursor cursor;
    cursor_init(&cursor);
    world_init(&world, map_length, map_width, 10);
    fill_list(&world, world.creatures, 2, CREATURE);
    fill_list(&world, world.entities_list, 7, FOOD);
    random_position_list(world.map, world.entities_list);

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




    
    // Terminer ncurses
    endwin();
    return 0;
}