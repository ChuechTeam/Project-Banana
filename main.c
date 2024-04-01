#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entities.h"

typedef struct{
    int length;
    int width;
}Map;



int main() {
    srand(time(NULL));

    Map map;
    map.length = 100;
    map.width = 100;

    Entity_list entity_list;
    int size = 11;
    list_init(&entity_list, size);
    printf("%d\n", fill_list(&entity_list, 3, FOOD));
    print_list(&entity_list);
    printf("%d\n", fill_list(&entity_list, 4, CREATURE));
    print_list(&entity_list);
    printf("%d\n", fill_list(&entity_list, 3, FOOD));
    print_list(&entity_list);




    return 0;
}