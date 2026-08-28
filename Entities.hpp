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
    bool isAlive() const;

    void setPosition(const Vec2& new_position);
    void setAlive(bool alive);
};

class Food : public Entity {
    int nutrition_value = 1; // Default nutrition value for food
public:
    Food(int x, int y);
    Vec2 move(World& world) override {
        return getPosition(); // Food doesn't move
    };

    char getSymbol() const override;
    int getNutritionValue() const {
        return nutrition_value;
    }

    int beingConsumed();

};

/**
 * @brief creature, arguments for constructor are x, y, speed, base_energy, energy, consumed_food
 */
class Creature : public Entity {
    float speed;
    float base_energy;
    float energy;
    int consumed_food;

    Vision vision; // Default vision range and angle
    Food* target_food = nullptr; // Pointer to the food the creature is currently targeting
public:
    Creature(int x, int y, double speed, double base_energy, double energy, int consumed_food, Vision vision);
    Creature(int x, int y);
    Creature();

    char getSymbol() const override;
    Vision getVision() const;
    float getEnergy() const;
    Food* getTarget() const;
    int getConsumed() const;

    void setTargetFood(Food* food);
    void setEnergy(float new_energy);
    void setSpeed(float new_speed);

    Vec2 selectPartMove(Vec2 target, float _speed);
    Vec2 move(World& world) override;
    void consumeFood(Food* food);
};


#endif //PROJECT_BANANA_ENTITIES_HPP
