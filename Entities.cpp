//
// Created by natha on 04/08/2026.
//
#include "Entities.hpp"
#include "World.hpp"


Entity::Entity(int x, int y) : position{.x = x, .y = y}, is_alive{true} {
}

Entity::Entity() : position{.x = 0, .y = 0}, is_alive{true} {
}


Vec2 Entity::getPosition() const {
    return position;
}


void Entity::setPosition(const Vec2 &new_position) {
    position = new_position;
}

Creature::Creature(int x, int y, double speed, double base_energy, double energy, int consumed_food)
    : Entity(x, y), speed(speed), base_energy(base_energy), energy(energy), consumed_food(consumed_food) {
}

Creature::Creature()
    : Creature(0, 0, 1.0, 5.0, 5.0, 0) {
}

char Creature::getSymbol() const {
    return 'C';
}

void Creature::turn(World &world) {
    // Implement the logic for the creature's turn here
    std::vector<Vec2> directions = {
        {-1, -1}, {0, -1},
        {1, -1}, {-1, 0},
        {1, 0}, {-1, 1},
        {0, 1}, {1, 1}
    };
    Vec2 new_position;
    do {
        int random_index = rand() % directions.size();
        new_position = directions[random_index] + getPosition();
        directions[random_index] = directions.back();
        directions.pop_back();
    } while (world.isWalkable(new_position) == false);
    setPosition(new_position);
    // std::cout << new_position << std::endl;
}

Food::Food(int x, int y) : Entity(x, y) {
}
