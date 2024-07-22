//
// Created by cacac on 12/05/2023.
//

#ifndef PROJECT_BANANA_TERMINAL_H
#define PROJECT_BANANA_TERMINAL_H
#include <stdio.h>
#include <ncurses.h>

typedef struct{
    short colors_pair[20][2];
    int color_num;
}Colors;

typedef struct{
    int x;
    int y;
    short foreground;
    short background;
    Colors colors;
}Cursor;


void cursor_init(Cursor* cursor);
void clear_all(Cursor* cursor);
void clear_part(int line, int column);
void cursor_move(char direction, int num);
void flush_input_buffer();
int getint();
void commentary(char tab[]);
void waiting();
void set_color(Cursor *cursor, char* code);
short get_color_pair(Cursor *cursor);
void clear_attributes();
void drawText(int x, int y, char* str, int color_pair);
void draw_printf(Cursor* cursor, const char *format, ...);
void print_rect(int length, int width, int color_pair);
#endif //PROJECT_BANANA_TERMINAL_H
