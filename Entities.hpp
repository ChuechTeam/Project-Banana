//
// Created by natha on 04/08/2026.
//

#ifndef PROJECT_BANANA_ENTITIES_HPP
#define PROJECT_BANANA_ENTITIES_HPP
#include <memory>

#include "Vec2.hpp"
#include "Vision.hpp"
class World;




class Entity {
    Vec2 position;
    bool is_alive;

public:
    Entity(Vec2 position);

    Entity();

    virtual ~Entity() = default;
    virtual char getSymbol() const = 0;
    // virtual void turn(World& world) = 0;
    virtual Vec2 move(World& world) = 0;
    virtual std::vector<std::unique_ptr<Entity>> reproduction(World& world) = 0;

    Vec2 getPosition() const;
    bool isAlive() const;

    void setPosition(const Vec2& new_position);
    void setAlive(bool alive);
};

/**
 * @brief Creates a new entity of type T and returns a unique pointer to it. Can add the needed arguments for specific entity creation.
 *
 *
 *
 * @tparam T the entity's children you want to create
 * @return the unique pointer of the entity created
 */
template<class T, typename... Args>
    requires std::derived_from<T, Entity> // Ensure T is derived from Entity
std::unique_ptr<T> createEntity(Args &&... args) {
    return std::make_unique<T>(
        std::forward<Args>(args)...);
}

/**
 * @brief food, currently what creatures eat, arguments for constructor are Vec2{x, y}, nutrition_value (default is 1)
 */
class Food : public Entity {
    int nutrition_value; // Default nutrition value for food
public:
    Food(Vec2 position, int nutrition_value = 1);
    Vec2 move(World& world) override {
        return getPosition(); // Food doesn't move
    };

    char getSymbol() const override;
    int getNutritionValue() const {
        return nutrition_value;
    }

    int beingConsumed();

    /**
     * @brif currently, food will just respawn at a random position on the map. Later on, will probably reproduce for real
     * @param world the map
     * @return self but reset
     */
    std::vector<std::unique_ptr<Entity>> reproduction(World &world) override;

};

/**
 * @brief creature, arguments for constructor are Vec2{x, y}, speed, base_energy, energy, consumed_food
 */
class Creature : public Entity {
    float speed;
    float base_energy;
    float energy;
    int consumed_food;
    float metabolism = 0.1; // Energy consumed per turn

    Vision vision; // Default vision range and angle
    Food* target_food = nullptr; // Pointer to the food the creature is currently targeting
public:
    Creature(Vec2 position, double speed, double base_energy, double energy, int consumed_food, Vision vision, float metabolism = 0.1);
    Creature(Vec2 position);
    Creature();

    Vision getVision() const;
    float getEnergy() const;
    Food* getTarget() const;
    int getConsumed() const;
    float getMetabolism() const;

    void setTargetFood(Food* food);
    void setEnergy(float new_energy);
    void setSpeed(float new_speed);

    Vec2 selectPartMove(Vec2 target, float _speed);
    Vec2 move(World& world) override;
    void consumeFood(Food* food);

    char getSymbol() const override;
    std::vector<std::unique_ptr<Entity>> reproduction(World &world) override;
};


#endif //PROJECT_BANANA_ENTITIES_HPP
