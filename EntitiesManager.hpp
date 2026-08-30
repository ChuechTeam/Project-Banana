//
// Created by natha on 22/08/2026.
//

#ifndef PROJECT_BANANA_ENTITIESMANAGER_HPP
#define PROJECT_BANANA_ENTITIESMANAGER_HPP
#include <memory>
#include <unordered_map>
#include <vector>
#include "Entities.hpp"
class World;



class EntitiesManager {
    std::vector<std::unique_ptr<Entity> > entities;
    std::unordered_map<Vec2, std::vector<Entity *>, Vec2Hasher> spatialHash;
    std::unordered_map<Vision, std::vector<Vec2>, VisionHasher> visionCache;

public:
    void addEntity(std::unique_ptr<Entity> entity);

    std::vector<std::unique_ptr<Entity> > const &getEntities();

    void removeEntityFromHash(Entity *entity, Vec2 old_position);

    void removeEntityFromHash(Entity *entity);

    void findFoodForCreature(Creature *creature);

    /**
    * @brief Iterates through all entities and for each to have a turn, inform if life is still there. You might need another turn to detect false positives (entities that dies after being checked)
    * @param world just the data/map
    * @return true if there is at least one entity/creature alive, false if all entities are dead
    */
    bool entitiesTurn(World &world);

    /**
     * @brief this is the reproduction system, for the whole generation. It will deal with all of the lists linked to the entities to be ready to start a entire new generation.
     * @param world the map
     */
    void reproduction(World &world);
};
#endif //PROJECT_BANANA_ENTITIESMANAGER_HPP
