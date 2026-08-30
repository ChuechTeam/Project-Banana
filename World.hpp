//
// Created by natha on 24/08/2026.
//

#ifndef PROJECT_BANANA_WORLD_HPP
#define PROJECT_BANANA_WORLD_HPP
#include "Vec2.hpp"
#include "EntitiesManager.hpp"

class World {
    Vec2 map;
    std::mt19937 rng{1234};//{std::random_device{}()}; // Random number generator for the world

public:
    World(int map_x, int map_y) : map{.x = map_x, .y = map_y} {
    }

    World() : map{.x = 20, .y = 10} {
    }

    EntitiesManager entities_manager;

    Vec2 getRandomWalkablePosition();
    std::mt19937& getRng() { return rng; }

    Vec2 getMapSize() const;


    void render();

    bool isWalkable(Vec2 position);


};
#endif //PROJECT_BANANA_WORLD_HPP
