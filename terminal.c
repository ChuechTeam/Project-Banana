#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "terminal.h"
#include "macro.h"
#include <ncurses.h>




void cursor_init(Cursor* cursor){
    cursor->x = 0;
    cursor->y = 0;

    cursor->colors.color_num = 7;
    set_color(cursor, C_WHT);
    set_color(cursor, B_BLK);
}

// efface tout le terminal visible
void clear_all(Cursor *d) {
    erase();
    d->y = 0;
    d->x = 0;

}

//efface une partie du terminal
void clear_part(int line, int column) {
    printf("\033[%d;%dH\033[J", line, column); // code ANSI pour déplacer le curseur puis efface
}

//déplace le curseur dans la direction et la valeur indiquée
// A: up, B: down, C: forward, D: backward
void cursor_move(char direction, int num) {
    printf("\033[%d%c", num, direction);
}

// Va vider le "buffer" pour éviter les fuites de donnée quand on fait des getchar notamment
void flush_input_buffer() {
    int c;
    char *str = malloc(sizeof(char) * 10); //copie le contenu du buffer dans un tableau

    //vérifie que le buffer n'est pas vide
    if (strlen(str) != 0) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
    free(str);
}

// retourne un simple int d'un seul caractère, utile pour les cas de choix pour par exemple de 1 à 5, moins
// d'utilisations de ressources qu'un scanf
int getint() {
    return getchar() - '0'; // ascii du chiffre transformé en le chiffre lui meme en lui enlevant le code de 0
}

// permet d'écrire un "commentaire" d'une couleur differente et de remettre à la bonne couleur pour la suite
// exemple : appuyez sur entrée pour continuer
void commentary(char tab[]) { // tab est la chaine de caractère désiré en commentaire
    printf("%s%s%s\n", "\033[90m", tab, C_WHT); // le premier %s met la couleur en gris et le 3e la remet en blanc
}

// permet de faire un "entrer pour continuer", "presser une touche pour continuer"
void waiting() {
    commentary("(Press 'enter' to continue..)");
    getchar();
    flush_input_buffer(); // efface la mémoire tampon pour éviter les fuites de mémoire d'input
}


//it takes the ansi code for text color, which is the numbers part of an ANSI code, exemple \033[43 it takes "43"
void set_color(Cursor *cursor, char* code) {
    if (code[0]=='\033' && code[4] == 'm'){
        if (code[2] == '3') {
            cursor->foreground = code[3] - '0';
        } else if (code[2] == '4') {
            cursor->background = code[3] - '0';
        }
    }
}

short get_color_pair(Cursor *cursor) {
    if (cursor->colors.color_num == 0) {
        cursor->colors.colors_pair[0][0] = cursor->foreground;
        cursor->colors.colors_pair[0][1] = cursor->background;
        init_pair(8, cursor->foreground, cursor->background);

        cursor->colors.color_num++;
        return 8;
    }
    for (int i = 0; i < cursor->colors.color_num; i++) {
        if (cursor->colors.colors_pair[i][0] == cursor->foreground &&
            cursor->colors.colors_pair[i][1] == cursor->background) {
            return i + 8;
        }
    }
    cursor->colors.colors_pair[cursor->colors.color_num][0] = cursor->foreground;
    cursor->colors.colors_pair[cursor->colors.color_num][1] = cursor->background;
    init_pair(cursor->colors.color_num + 8, cursor->foreground, cursor->background);
    cursor->colors.color_num++;
    return cursor->colors.color_num + 8;

}

void clear_attributes() {
    // Get the current attributes and color pair at the cursor position
    attr_t attrs;  // Variable to store the current attributes
    short pair;    // Variable to store the current color pair
    attr_get(&attrs, &pair, NULL);  // Retrieve attributes and color pair

    // Turn off all attributes
    if (attrs != A_NORMAL) {  // If there are non-normal attributes
        attroff(attrs);        // Turn off those attributes
    }

    // Turn off the color pair if it's active
    if (pair != 0) {  // If a color pair is active
        attroff(COLOR_PAIR(pair));  // Turn off that color pair
    }
}


void drawText(int x, int y, char* str, int color_pair){
    clear_attributes();
    attron(COLOR_PAIR(color_pair));
    mvprintw(y,x,"%s", str);


}

void draw_printf(Cursor *cursor, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[200];
    char ansi[2];
    int j = 0;
    vsnprintf(buffer, sizeof(buffer), format, args);
    char *str = malloc(strlen(buffer));
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '\033') {
            drawText(cursor->x, cursor->y, str, get_color_pair(cursor));
            ansi[0] = buffer[i + 2];
            ansi[1] = buffer[i + 3];
            set_color(cursor, ansi);
            cursor->x += strlen(str);
            free(str);
            str = malloc(strlen(buffer));
            j = 0;
            i += 4;
        } else if (buffer[i] == '\n') {
            drawText(cursor->x, cursor->y, str, get_color_pair(cursor));
            free(str);
            str = malloc(strlen(buffer));
            j = 0;
            cursor->x = 0;
            cursor->y += 1;
        } else {
            str[j] = buffer[i];
            j++;
        }
    }
    drawText(cursor->x, cursor->y, str, get_color_pair(cursor));
    cursor->x += strlen(str);

    free(str);
    va_end(args);
}

void print_rect(int length, int width, int color_pair){
    int num = 1;
    for (int i = 0;i<length; i++){
        char c_i = '0' + i;
        //drawText(i, 1, &c_i, color_pair);
        for (int j = 0; j<width; j++){
            char c_j = '0' + j;
            if (j == 0 || j == width - 1){
                if(num){
                    drawText(i, j, &c_i, color_pair);
                }
                else{
                    drawText(i, j, "-", color_pair);
                }  
            }
            if (i == 0 || i == length - 1){
                if(num){
                    drawText(i, j, &c_j, color_pair);
                }
                else{
                    drawText(i, j, "|", color_pair);
                }   
            }
        
        }
    }
    getch();
}
