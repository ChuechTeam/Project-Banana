//
// Created by natha on 24/08/2026.
//

#ifndef PROJECT_BANANA_WORLD_HPP
#define PROJECT_BANANA_WORLD_HPP
#include "Vec2.hpp"
#include "EntitiesManager.hpp"

class World {
    Vec2 map;

public:
    World(int map_x, int map_y) : map{.x = map_x, .y = map_y} {
    }

    World() : map{.x = 20, .y = 10} {
    }

    EntitiesManager entities_manager;

    Vec2 getMapSize() const;


    void render();

    bool isWalkable(Vec2 position);
};
#endif //PROJECT_BANANA_WORLD_HPP
