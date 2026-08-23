//
// Created by natha on 04/08/2026.
//

#ifndef PROJECT_BANANA_ENTITIES_HPP
#define PROJECT_BANANA_ENTITIES_HPP

struct Vec2 {
    int x, y;
};


class Entity {
    Vec2 position;
    bool is_alive;

public:
    Entity(int x, int y);

    Entity();

    virtual ~Entity() = default;
    virtual char getSymbol() const = 0;

    Vec2 getPosition() const;
};

/**
 * @brief creature, arguments for constructor are x, y, speed, base_energy, energy, consumed_food
 */
class Creature : public Entity {
    double speed;
    double base_energy;
    double energy;
    int consumed_food;

public:
    Creature(int x, int y, double speed, double base_energy, double energy, int consumed_food);
    Creature();

    char getSymbol() const override;
};

class Food : public Entity {
public:
    Food(int x, int y);
};


#endif //PROJECT_BANANA_ENTITIES_HPP
