//
// Created by natha on 04/08/2026.
//
#include "Entities.hpp"
#include "World.hpp"



Entity::Entity(Vec2 position) : position{position}, is_alive{true} {
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
    return genome.vision;
}


void Entity::setPosition(const Vec2 &new_position) {
    position = new_position;
}

void Entity::setAlive(bool alive) {
    is_alive = alive;
}


Food::Food(Vec2 position, int nutrition_value) : Entity(position), nutrition_value(nutrition_value) {
}

char Food::getSymbol() const {
    return 'F';
}

int Food::beingConsumed() {
    setAlive(false);
    return nutrition_value;
}

std::vector<std::unique_ptr<Entity> > Food::reproduction(World &world) {
    std::vector<std::unique_ptr<Entity> > children;
    children.push_back(
        createEntity<Food>(
            world.getRandomWalkablePosition(),
            nutrition_value
        )
    );
    return children;
}

Creature::Creature(Vec2 position, float base_energy, Genome genome, int consumed_food) : Entity(position),
    genome(genome), energy(base_energy), consumed_food(consumed_food) {
}

Creature::Creature(Vec2 position, double speed, double base_energy, double energy, int consumed_food, Vision vision,
                   float metabolism)
    : Entity(position), genome(speed, base_energy, vision, metabolism), energy(energy), consumed_food(consumed_food) {
}

Creature::Creature(Vec2 position)
    : Creature(position, 1.0, 5.0, 5.0, 0, Vision{2, 360}) {
}

Creature::Creature()
    : Creature({0, 0}, 1.0, 5.0, 5.0, 0, Vision{2, 360}) {
}

Food *Creature::getTarget() const {
    return target_food;
}

int Creature::getConsumed() const {
    return consumed_food;
}

float Creature::getMetabolism() const {
    return genome.metabolism;
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
    float _speed = genome.speed; //speed for this turn
    Vec2 target = target_food
                      ? target_food->getPosition()
                      : Vec2{rand() % world.getMapSize().x, rand() % world.getMapSize().y};
    std::cout << target << std::endl;
    Vec2 new_position = selectPartMove(target, _speed);

    if (new_position.distanceto({0, 0}) <= std::min(energy, _speed)) {
        do {
            Vec2 potential_position = new_position + getPosition();
            if (!world.isWalkable(potential_position)) {
                if (target_food != nullptr) {
                    target_food = nullptr;
                    target = Vec2{rand() % world.getMapSize().x, rand() % world.getMapSize().y};
                }
                new_position = selectPartMove(target, _speed);
                continue;
            }
            setPosition(potential_position);
            float consommation = std::min({energy, _speed, new_position.distanceto({0, 0})});
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
        } while (new_position.distanceto({0, 0}) <= std::min(energy, _speed));
    }
    return getPosition();
    // std::cout << new_position << std::endl;
}

void Creature::consumeFood(Food *food) {
    if (food != nullptr && food->isAlive()) {
        consumed_food += food->beingConsumed();
        if (!food->isAlive()) {
            target_food = nullptr;
        }
    }
}

void Creature::setTargetFood(Food *food) {
    target_food = food;
}

void Creature::setEnergy(float new_energy) {
    energy = std::max(0.0f, new_energy);
    if (energy <= 0) {
        setAlive(false);
    }
}

void Creature::setSpeed(float new_speed) {
    genome.speed = std::max(0.0f, new_speed);
}


float Creature::getEnergy() const {
    return energy;
}

char Creature::getSymbol() const {
    return 'C';
}

std::vector<std::unique_ptr<Entity> > Creature::reproduction(World &world) {
    std::vector<std::unique_ptr<Entity> > children;
    while (consumed_food > 0) {
        auto child = createEntity<Creature>(
                world.getRandomWalkablePosition(),
                genome.speed,
                genome.base_energy,
                genome.base_energy,
                0,
                genome.vision,
                genome.metabolism
            );
        GeneticSystem::mutation(world.getRng(), child->genome, 1);
        child->setEnergy(child->genome.base_energy);
        children.push_back(std::move(child));
        consumed_food--;
    }
    return children;
}
