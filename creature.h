//
// Created by cacac on 21/11/2023.
//

#ifndef PROJECT_BANANA_CREATURE_H
#define PROJECT_BANANA_CREATURE_H
typedef struct {
    int x;
    int y;

    double speed;
    int energy;
    int consumed_food;
} Creature;

typedef struct CreatureList{
    Creature* creature;
    struct CreatureList *next;
} CreatureList;

Creature *creature_init();
CreatureList *add_creature(CreatureList *creature_list);
CreatureList* create_x_entities(CreatureList *creature_list, int x);
void print_creature(Creature* creature);
void print_creature_list(CreatureList *creature_list);
void delete_creature_list(CreatureList *creature_list);
void init_position_creature(CreatureList *creature_list, int x, int y);

#endif //PROJECT_BANANA_CREATURE_H
