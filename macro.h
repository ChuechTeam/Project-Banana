//
// Created by cacac on 10/03/2024.
//

#ifndef PROJECT_BANANA_MACRO_H
#define PROJECT_BANANA_MACRO_H

#ifdef _WIN32
    #define _USE_MATH_DEFINES
#elif defined(__linux__)

#endif

enum error_type{SUCCESS, OUT_OF_RANGE, WRONG_TYPE};

#define FOR_LOOP(i, start, end, step) \
    for (int i = (start); i < (end); i+= (step))

#define SQUARE(a) ((a) * (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RAD_TO_DEG(radians) ((radians) * (180.0 / M_PI))
// Macro pour obtenir le nombre le plus proche entre floor et ceil
#define NEAREST_INT(x) (((x) - floor(x)) < (ceil(x) - (x)) ? floor(x) : ceil(x))

#define PING printf("ping \n")

#define NUM_PING(i) printf("ping %d\n", i)

static int counter = 0;

#define INC_PING \
        counter ++; \
        printf("ping %d\n", counter) \




//macro for graphisms

#define C_BLK "\033[30m" // Caractère noir
#define C_RED "\033[31m" // Caractère rouge
#define C_GRN "\033[32m" // Caractère vert
#define C_YEL "\033[33m" // Caractère jaune
#define C_BLU "\033[34m" // Caractère bleu
#define C_MAG "\033[35m" // Caractère magenta
#define C_CYN "\033[36m" // Caractère cyan
#define C_WHT "\033[37m" // Caractère blanc

#define B_BLK "\033[40m" // Fond noir
#define B_RED "\033[41m" // Fond rouge
#define B_GRN "\033[42m" // Fond vert
#define B_YEL "\033[43m" // Fond jaune
#define B_BLU "\033[44m" // Fond bleu
#define B_MAG "\033[45m" // Fond magenta
#define B_CYN "\033[46m" // Fond cyan
#define B_WHT "\033[47m" // Fond blanc


#endif //PROJECT_BANANA_MACRO_H
