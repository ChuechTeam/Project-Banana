#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "creature.h"


Creature *creature_init() {
    Creature *creature = malloc(sizeof(Creature)); // Allocating memory for a new Creature
    creature->x = 0; // Setting initial x coordinate to 0
    creature->y = 0; // Setting initial y coordinate to 0

    creature->speed = 1.0; // Setting the speed of the creature to 1.0
    creature->consumed_food = 0; // Setting initial consumed food to 0

    return creature; // Returning the initialized creature
}

CreatureList *add_creature(CreatureList *creature_list) {
    CreatureList *n1 = malloc(sizeof(CreatureList)); // Allocating memory for a new CreatureList node
    n1->creature = (creature_init()); // Initializing a new creature and assigning it to the node
    n1->next = creature_list; // Setting the next node to the current head of the list
    return n1; // Returning the updated list with the new creature added
}

CreatureList *create_x_entities(CreatureList *creature_list, int x) {
    for (int i = 0; i < x; i++) {
        creature_list = add_creature(creature_list); // Adding x number of creatures to the list
    }
    return creature_list; // Returning the updated list with x new creatures added
}

void print_creature(Creature *creature) {
    // Printing the details of a single creature - its x, y coordinates, speed, and consumed food
    printf("x : %d; y : %d ; speed : %.2f ; food : %d\n", creature->x, creature->y, creature->speed,
           creature->consumed_food);
}

void print_creature_list(CreatureList *creature_list) {
    if (creature_list->next == NULL) {
        // Printing the details of each creature in the list by recursively traversing the list
        print_creature(creature_list->creature);
        return;
    }
    print_creature_list(creature_list->next); // Recursively calling the function for the next creature
    print_creature(creature_list->creature); // Printing the details of the current creature
}

void delete_creature_list(CreatureList *creature_list) {
    if (creature_list->next == NULL) {
        free(creature_list->creature); // Freeing memory for the last creature in the list
        return;
    }
    free(creature_list->next); // Freeing memory for the next node in the list
    free(creature_list->creature); // Freeing memory for the current creature
}

void init_position_creature(CreatureList *creature_list, int x, int y) {
    if (creature_list->next == NULL) {
        // Setting the position of the last creature in the list randomly within the specified space (x, y)
        creature_list->creature->x = (rand() % (x - 0) + 0);
        creature_list->creature->y = (rand() % (y - 0) + 0);
        return;
    }
    init_position_creature(creature_list->next, x, y); // Recursively calling for the next creature
    // Setting the position of the current creature randomly within the specified space (x, y)
    creature_list->creature->x = (rand() % (x - 0) + 0);
    creature_list->creature->y = (rand() % (y - 0) + 0);
}

CreatureTreeX *createTreeX() {
    CreatureTreeX *tree = malloc(sizeof(CreatureTreeX));
    tree->left_subtree = NULL;
    tree->right_subtree = NULL;
    tree->creature = NULL;

    return tree;
}


void add_tree_x(CreatureTreeX *tree, Creature *creature) {
    if (tree->creature == NULL) {
        tree->creature = creature;
    } else if (creature->x == tree->creature->x) {
        CreatureTreeX *next = createTreeX();
        next->creature = creature;
        next->right_subtree = tree->right_subtree;
        tree->right_subtree = next;
    } else if (creature->x < tree->creature->x) {
        if (tree->left_subtree == NULL) {
            tree->left_subtree = createTreeX();
            tree->left_subtree->creature = creature;
        } else {
            add_tree_x(tree->left_subtree, creature);

        }
    } else if (creature->x > tree->creature->x) {
        if (tree->right_subtree == NULL) {
            tree->right_subtree = createTreeX();
            tree->right_subtree->creature = creature;
        } else {
            add_tree_x(tree->right_subtree, creature);
        }
    }
}

//TODO: renommer en parcours préfixe et faire les autres parcours pour vérifier que l'arbre est correct
void print_tree_x(CreatureTreeX *tree) {
    printf("%d - ", tree->creature->x);
    if (tree->left_subtree != NULL) {
        print_tree_x(tree->left_subtree);
    }
    if (tree->right_subtree != NULL) {
        print_tree_x(tree->right_subtree);
    }
}

CreatureTreeX *listeXToTree(CreatureTreeX *tree, CreatureList *list) {
    add_tree_x(tree, list->creature);
    if (list->next == NULL) {
        return tree;
    } else {
        listeXToTree(tree, list->next);
    }
}