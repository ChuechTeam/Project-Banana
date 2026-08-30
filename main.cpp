#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "Entities.hpp"
#include "EntitiesManager.hpp"
#include "World.hpp"
using namespace std;


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


void clearTerminal()
{
    std::system("cls");
}


int main() {
    auto world = World();
    world.entities_manager.addEntity(createEntity<Creature>(Vec2{3,3}, 1, 15, 15, 0, Vision{10, 360}));
    world.entities_manager.addEntity(createEntity<Food>(Vec2{1, 1}));
    world.entities_manager.addEntity(createEntity<Food>(Vec2{5, 5}));
    // world.entities_manager.addEntity(createEntity<Food>(3, 2));
    world.render();
    bool alive = true;
    while (true) {
        if (!alive) {
            std::cout << "All creatures are dead. Simulation ended." << std::endl;
            world.entities_manager.reproduction(world);
            clearTerminal();
            world.render();
        }
        alive = world.entities_manager.entitiesTurn(world);
        clearTerminal();
        world.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return 0;
}
