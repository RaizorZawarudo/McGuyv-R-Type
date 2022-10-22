/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** CollisionSystem
*/

#pragma once

#include "ISystem.hpp"
#include "InputSystem.hpp"
#include "../AssetManager.hpp"

class CollisionSystem : public ISystem {
    public:
        CollisionSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager);
        ~CollisionSystem();

        void update(std::vector<EntityID> &allEntities) override;
        void bullet_collisions(EntityID ent, EntityID other);
        void powerUp_collisons(EntityID ent, EntityID other);
        void body_collisions(EntityID ent, EntityID other);

        void create_explosion(Vector3 pos, std::string exploName);

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
};

