//
// Created by natha on 04/08/2026.
//

#ifndef PROJECT_BANANA_ENTITIES_HPP
#define PROJECT_BANANA_ENTITIES_HPP
#include "Vec2.hpp"
#include "Vision.hpp"
class World;




class Entity {
    Vec2 position;
    bool is_alive;

public:
    Entity(int x, int y);

    Entity();

    virtual ~Entity() = default;
    virtual char getSymbol() const = 0;
    // virtual void turn(World& world) = 0;
    virtual Vec2 move(World& world) = 0;

    Vec2 getPosition() const;
    void setPosition(const Vec2& new_position);
};

class Food : public Entity {
public:
    Food(int x, int y);
    Vec2 move(World& world) override {
        return getPosition(); // Food doesn't move
    };
    char getSymbol() const override;
};

/**
 * @brief creature, arguments for constructor are x, y, speed, base_energy, energy, consumed_food
 */
class Creature : public Entity {
    double speed;
    double base_energy;
    double energy;
    int consumed_food;

    Vision vision; // Default vision range and angle
    Food* target_food = nullptr; // Pointer to the food the creature is currently targeting
public:
    Creature(int x, int y, double speed, double base_energy, double energy, int consumed_food, Vision vision);
    Creature();

    char getSymbol() const override;
    Vec2 move(World& world) override;
    Vision getVision() const;

    void setTargetFood(Food* food);
};


#endif //PROJECT_BANANA_ENTITIES_HPP
