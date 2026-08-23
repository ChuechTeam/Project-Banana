#include <iostream>
#include <vector>

#include "Entities.hpp"
#include "EntitiesManager.hpp"
using namespace std;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


class World {
    Vec2 map;

public:
    World(int map_x, int map_y) : map{.x = map_x, .y = map_y} {
    }

    World() : map{.x = 20, .y = 10} {
    }

    EntitiesManager entities_manager;


    void render() {
        std::vector<char> grid((map.x+2) * (map.y+2), ' ');
        for (auto &entity : entities_manager.getEntities()) {
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
                        std::cout << (char)('0' + (x - 1) % 10);
                    }
                } else if (x == 0 || x == map.x + 1) {
                    std::cout << (char)('0' + (y - 1) % 10);
                } else {
                    std::cout << grid[y * (map.x + 2) + x];
                }
            }
            std::cout << '\n';
        }

    }

};


int main() {
    auto world = World();
    world.entities_manager.addEntity(createEntity<Creature>(1, 2, 1.0, 5.0, 5.0, 0));
    world.render();
    while (true) {
        // Game loop logic here

    }

    return 0;
}
