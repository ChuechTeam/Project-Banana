//
// Created by natha on 22/08/2026.
//

#include "EntitiesManager.hpp"

#include <unordered_map>
#include <algorithm>

void EntitiesManager::addEntity(std::unique_ptr<Entity> _entity) {
    entities.push_back(std::move(_entity));
    auto entity = entities.back().get(); // Get the raw pointer to the newly added entity
    spatialHash[entity->getPosition()].push_back(entities.back().get()); // Add the raw pointer to the spatial hash
}

const std::vector<std::unique_ptr<Entity> > &EntitiesManager::getEntities() { return entities; }

/**
 * @brief Removes an entity from the spatial hash based on its position. It finds the entity in the corresponding bucket
 * and removes it efficiently by swapping it with the last element and popping the back.
 * @param entity the entity you want to erase from the Hash
 * @param old_position the position of the entity before it moved, used to locate the correct bucket in the spatial hash
 */
void EntitiesManager::removeEntityFromHash(Entity *entity, Vec2 old_position) {
    auto &bucket = spatialHash.at(old_position);
    auto it = std::ranges::find(bucket, entity);
    if (it != bucket.end()) {
        *it = bucket.back();
        bucket.pop_back();
    }
    if (bucket.empty()) {
        spatialHash.erase(old_position);
    }
}

void EntitiesManager::removeEntityFromHash(Entity *entity) {
    auto old_position = entity->getPosition();
    removeEntityFromHash(entity, old_position);
}
void EntitiesManager::findFoodForCreature(Creature *creature) {
    Vision vision = creature->getVision();
    auto it = visionCache.find(vision);

    if (it == visionCache.end()) {
        it = visionCache.emplace(
            vision,
            vision.getVisiblePositions()
        ).first;
    }
    for (auto &v : it->second) {
        for (auto &food_entity: spatialHash[creature->getPosition() + v]) {
            if (Food *food = dynamic_cast<Food *>(food_entity)) {
                return creature->setTargetFood(food);
            }
        }
    }
}
/**
 * @brief Iterates through all entities and for each to have a turn
 * @param world just the data/map
 */
void EntitiesManager::entitiesTurn(World &world) {
    for (auto &entity: entities) {
        //vision part:
        if (Creature *creature = dynamic_cast<Creature *>(entity.get())) {
            findFoodForCreature(creature);
        }




        //moving part
        auto old_position = entity->getPosition();
        auto new_position = entity->move(world);
        if (new_position != old_position) {
            removeEntityFromHash(entity.get(), old_position);
            spatialHash[new_position].push_back(entity.get());
        }
    }
}
