//
// Created by natha on 24/08/2026.
//

#include "World.hpp"

#include <iostream>

Vec2 World::getMapSize() const {
    return map;
}

void World::render() {
    std::vector<char> grid((map.x + 2) * (map.y + 2), ' ');
    for (auto &entity: entities_manager.getEntities()) {
        if (!entity->isAlive()) {
            continue;
        }
        int x = entity->getPosition().x;
        int y = entity->getPosition().y;
        grid[(y + 1) * (map.x + 2) + (x + 1)] = entity->getSymbol();
    }
    // draw the borders but after the first and last row and column, the caracters are numbers than letters, exemple %0123456789abcd% :
    for (int y = 0; y < map.y + 2; ++y) {
        for (int x = 0; x < map.x + 2; ++x) {
            if (y == 0 || y == map.y + 1) {
                if (x == 0 || x == map.x + 1) {
                    std::cout << '%';
                } else {
                    std::cout << (char) ('0' + (x - 1) % 10);
                }
            } else if (x == 0 || x == map.x + 1) {
                std::cout << (char) ('0' + (y - 1) % 10);
            } else {
                std::cout << grid[y * (map.x + 2) + x];
            }
        }
        std::cout << '\n';
    }
}

bool World::isWalkable(Vec2 position) {
    // Check if the position is within the map boundaries
    if (position.x < 0 || position.x >= map.x || position.y < 0 || position.y >= map.y) {
        return false;
    }
    return true;
}
