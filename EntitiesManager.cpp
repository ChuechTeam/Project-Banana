//
// Created by natha on 22/08/2026.
//

#include "EntitiesManager.hpp"

void EntitiesManager::addEntity(std::unique_ptr<Entity> entity) {
    entities.push_back(std::move(entity));
}
const std::vector<std::unique_ptr<Entity> >& EntitiesManager::getEntities() { return entities; }