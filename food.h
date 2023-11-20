
#ifndef PROJECT_BANANA_FOOD_H
#define PROJECT_BANANA_FOOD_H

typedef struct {
    int x;
    int y;
}Food;

typedef struct FoodList{
    Food* food;
    struct FoodList *next;
} FoodList;


Food *food_init();
FoodList *add_food(FoodList *food_list);
FoodList* create_x_foods(FoodList *food_list, int x);
void print_food(Food* food);
void print_food_list(FoodList *food_list);
void delete_food_list(FoodList *food_list);
void init_position_food(FoodList *food_list, int x, int y);

#endif //PROJECT_BANANA_FOOD_H
