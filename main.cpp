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
    world.entities_manager.addEntity(createEntity<Creature>(1, 2, 1.0, 5.0, 5.0, 0));
    world.render();
    while (true) {
        world.entities_manager.entitiesTurn(world);
        clearTerminal();
        world.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return 0;
}
