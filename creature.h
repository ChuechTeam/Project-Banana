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

typedef struct CreatureTreeX{
    Creature* creature;
    struct CreatureTreeX *left_subtree;
    struct CreatureTreeX *right_subtree;
}CreatureTreeX;

typedef struct CreatureTreeY{
    Creature* creature;
    struct CreatureTreeY *left_subtree;
    struct CreatureTreeX *right_subtree;
}CreatureTreeY;

Creature *creature_init();
CreatureList *add_creature(CreatureList *creature_list);
CreatureList* create_x_entities(CreatureList *creature_list, int x);
void print_creature(Creature* creature);
void print_creature_list(CreatureList *creature_list);
void delete_creature_list(CreatureList *creature_list);
void init_position_creature(CreatureList *creature_list, int x, int y);
CreatureTreeX *createTreeX(Creature *creature);
void add_tree_x(CreatureTreeX *tree, Creature *creature);
void print_tree_x(CreatureTreeX *tree);
void listeXToTree(CreatureTreeX* tree, CreatureList* list);


#endif //PROJECT_BANANA_CREATURE_H
