//
// Created by cacac on 22/02/2025.
//

#include "graphic.h"
#include "world.h"
#include "macro.h"

void print_border(Map map, Cursor *cursor){
    set_color(cursor, C_YEL);
    int num = 1;
    char tab[] = {'@', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    int x = cursor->x;
    int y = cursor->y;
    printf("%d %d", map.x, map.y);
    cursor_move_to(cursor, map.x-1, map.y-1);

    for(int i = 0; i < map.height+2; i++){
        for(int j = 0; j < map.width+2; j++){
            if(j==0 || j == map.width+1){
                printf("%c", tab[num + num * i]);
            } else if(i == 0 || i == map.height+1){
                printf("%c", tab[num + num * j]);
            }
            else{
                printf(" ");
            }
        }
        cursor_move_to(cursor, map.x-1,map.y+i);
    }


    cursor_move_to(cursor, x, y);

}

void print_entities(pWorld_stats world, Cursor *cursor){

}

void print_board(pWorld_stats world, Cursor *cursor){
    clear_all(cursor);
    print_border(world->map, cursor);
    draw_world_entities(*world, cursor);
    cursor_move_to(cursor, 0,0);
}