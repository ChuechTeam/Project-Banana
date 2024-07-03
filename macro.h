//
// Created by cacac on 10/03/2024.
//

#ifndef PROJECT_BANANA_MACRO_H
#define PROJECT_BANANA_MACRO_H

#ifdef _WIN32
    #define _USE_MATH_DEFINES
#elif defined(__linux__)
    ...
#endif
enum error_type{SUCCESS, OUT_OF_RANGE};

#define SQUARE(a) ((a) * (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RAD_TO_DEG(radians) ((radians) * (180.0 / M_PI))
// Macro pour obtenir le nombre le plus proche entre floor et ceil
#define NEAREST_INT(x) (((x) - floor(x)) < (ceil(x) - (x)) ? floor(x) : ceil(x))
#endif //PROJECT_BANANA_MACRO_H
