//
// Created by cacac on 12/05/2023.
//

#ifndef PROJECT_BANANA_TERMINAL_H
#define PROJECT_BANANA_TERMINAL_H
#include <stdio.h>

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

int setBlockingFD(int fileDescriptor, int blocking);
void discardInput(void);
void cursor_init(Cursor* cursor);
void clear_all(Cursor* cursor);
void clear_part(int line, int column);
void cursor_move(Cursor* cursor, char direction, int num);
void cursor_move_to(Cursor* cursor, int x, int y);
void flush_input_buffer();
int getint();
void commentary(char tab[]);
void waiting();
void set_color(Cursor *cursor, char* code);
void draw_rect(Cursor* cursor, int length, int width);
#endif //PROJECT_BANANA_TERMINAL_H
