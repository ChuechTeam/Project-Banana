#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
//#include <stdarg.h>
//#include <poll.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <errno.h>

#include "terminal.h"
#include "macro.h"

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)

#include <unistd.h>

#endif

///* 0: success -1: error */
//int setBlockingFD(int fileDescriptor, int blocking) {
//    int r = fcntl(fileDescriptor, F_GETFL);
//    if (r == -1) {
//        perror("fcntl(F_GETFL)");
//        return -1;
//    }
//    int flags = (blocking ? r & ~O_NONBLOCK : r | O_NONBLOCK);
//    r = fcntl(fileDescriptor, F_SETFL, flags);
//    if (r == -1) {
//        perror("fcntl(F_SETFL)");
//        return -1;
//    }
//    return 0;
//}
//
//void discardInput(void) {
//    setBlockingFD(STDIN_FILENO, 0);
//    for (;;) {
//        int c = fgetc(stdin);
//        if (c == EOF) {
//            if (errno == EAGAIN) {
//                //vide
//            }
//            break;
//        } else {
//            //pas vide
//        }
//    }
//    setBlockingFD(STDIN_FILENO, 1);
//}


void cursor_init(Cursor *cursor) {
    cursor->x = 1;
    cursor->y = 1;

    cursor->colors.color_num = 7;
    set_color(cursor, C_WHT);
    set_color(cursor, B_BLK);
}

// efface tout le terminal visible
void clear_all(Cursor *d) {
    printf("\033[0;0H\033[J");
    d->y = 1;
    d->x = 1;

}

//efface une partie du terminal
void clear_part(int line, int column) {
    printf("\033[%d;%dH\033[J", line, column); // code ANSI pour déplacer le curseur puis efface
}

//déplace le curseur dans la direction et la valeur indiquée
// N: up, S: down, E: forward, W: backward
void cursor_move(Cursor *cursor, char direction, int num) {
    printf("\033[%d%c", num, direction);
    switch (direction) {
        case 'N':
            cursor->y -= num;
            break;
        case 'S':
            cursor->y += num;
            break;
        case 'E':
            cursor->x += num;
            break;
        case 'W':
            cursor->x -= num;
    }
}

void cursor_move_to(Cursor *cursor, int x, int y) {
    printf("\033[%d;%dH", y, x);
    cursor->x = x;
    cursor->y = y;
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
void set_color(Cursor *cursor, char *code) {
    if ((code[0] == '\033'|| code[0] =='\x1b') && code[4] == 'm') {
        if (code[2] == '3') {
            cursor->foreground = code[3] - '0';
        } else if (code[2] == '4') {
            cursor->background = code[3] - '0';
        }
        printf("%s", code);
    }

}

void draw_rect(Cursor *cursor, int length, int width) {
    int num = 0;
    char tab[] = {'@', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int x = cursor->x;
    int y = cursor->y;
    //lines
    for (int i = 0; i < width; i++) {
        printf("%c", tab[num + num * i]);
        cursor_move(cursor, 'C', length - 2);
        printf("%c\n",  tab[num + num * i]);
    }

    //collumns
    cursor_move_to(cursor, x, y);
    for (int j = 0; j < length; j++) {
        printf("%c",  tab[num + num * j]);
    }
    cursor_move_to(cursor, x, y + width - 1);
    for (int j = 0; j < length; j++) {
        printf("%c",  tab[num + num * j]);
    }
}

void terminal_sleep(int ms) {
#ifdef _WIN32
    Sleep(ms);
#elif defined(__linux__)
    usleep(1000 * ms);
#endif
}