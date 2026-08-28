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

bool Entity::isAlive() const {
    return is_alive;
}

Vision Creature::getVision() const {
    return vision;
}


void Entity::setPosition(const Vec2 &new_position) {
    position = new_position;
}

void Entity::setAlive(bool alive) {
    is_alive = alive;
}


int Food::beingConsumed() {
    setAlive(false);
    return nutrition_value;
}


Creature::Creature(int x, int y, double speed, double base_energy, double energy, int consumed_food, Vision vision, float metabolism)
    : Entity(x, y), speed(speed), base_energy(base_energy), energy(energy), consumed_food(consumed_food) , vision(vision) , metabolism(metabolism) {
}
Creature::Creature(int x, int y)
    : Creature(x, y, 1.0, 5.0, 5.0, 0, Vision{2, 360}) {
}

Creature::Creature()
    : Creature(0, 0, 1.0, 5.0, 5.0, 0, Vision{2, 360}) {
}

char Creature::getSymbol() const {
    return 'C';
}

Food* Creature::getTarget() const {
    return target_food;
}

int Creature::getConsumed() const {
    return consumed_food;
}

float Creature::getMetabolism() const {
    return metabolism;
}

Vec2 Creature::selectPartMove(Vec2 target, float _speed) {
    Vec2 new_position = target - getPosition();
    new_position.x = std::clamp(new_position.x, -1, 1);
    new_position.y = std::clamp(new_position.y, -1, 1);
    float min = std::min(energy, _speed);
    if (min * min < 2 && new_position.x != 0 && new_position.y != 0) {
        if (target.distanceto({new_position.x, 0}) < target.distanceto({0, new_position.y})) {
            new_position.y = 0;
        } else {
            new_position.x = 0;
        }
    }
    return new_position;
}

Vec2 Creature::move(World &world) {
    float _speed = speed; //speed for this turn
    Vec2 target = target_food ? target_food->getPosition() : Vec2{rand()%world.getMapSize().x, rand()%world.getMapSize().y};
    std::cout << target << std::endl;
    Vec2 new_position = selectPartMove(target, _speed);

    if (new_position.distanceto({0,0}) <= std::min(energy, _speed)) {
        do {
            Vec2 potential_position = new_position + getPosition();
            if (!world.isWalkable(potential_position)) {
                if (target_food != nullptr) {
                    target_food = nullptr;
                    target = Vec2{rand()%world.getMapSize().x, rand()%world.getMapSize().y};
                }
                new_position = selectPartMove(target, _speed);
                continue;
            }
            setPosition(potential_position);
            float consommation = std::min({energy, _speed, new_position.distanceto({0,0})});
            _speed -= consommation;
            setEnergy(energy - consommation);
            if (target_food == nullptr) {
                world.entities_manager.findFoodForCreature(this);
                if (target_food != nullptr) {
                    target = target_food->getPosition();
                }
            }
            new_position = selectPartMove(target, _speed);
            if (new_position == Vec2{0, 0}) {
                break;
            }
        } while (new_position.distanceto({0,0}) <= std::min(energy, _speed));
    }
    return getPosition();
    // std::cout << new_position << std::endl;
}

void Creature::consumeFood(Food *food) {
    if (food != nullptr && food->isAlive()) {
        consumed_food+= food->beingConsumed();
        if (!food->isAlive()) {
            target_food = nullptr;
        }
    }
}

void Creature::setTargetFood(Food *food) {
    target_food = food;
}
void Creature::setEnergy(float new_energy) {
    energy = std::max(0.0f,new_energy);
    if (energy <= 0) {
        setAlive(false);
    }
}
void Creature::setSpeed(float new_speed) {
    speed = std::max(0.0f,new_speed);
}


float Creature::getEnergy() const {
    return energy;
}

Food::Food(int x, int y) : Entity(x, y) {
}

char Food::getSymbol() const {
    return 'F';
}
