//
// Created by natha on 22/08/2026.
//

#ifndef PROJECT_BANANA_ENTITIESMANAGER_HPP
#define PROJECT_BANANA_ENTITIESMANAGER_HPP
#include <memory>
#include <vector>
#include "Entities.hpp"
class World;

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

class EntitiesManager {
    std::vector<std::unique_ptr<Entity> > entities;

public:
    void addEntity(std::unique_ptr<Entity> entity);
    std::vector<std::unique_ptr<Entity> > const&  getEntities();

    void entitiesTurn(World& world) const;
};
#endif //PROJECT_BANANA_ENTITIESMANAGER_HPP
