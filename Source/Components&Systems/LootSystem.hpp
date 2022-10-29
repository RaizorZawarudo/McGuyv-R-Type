/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** LootSystem
*/

#pragma once

#include "ISystem.hpp"
#include "InputSystem.hpp"
#include "../AssetManager.hpp"

class LootSystem : public ISystem {
    public:
        LootSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager);
        ~LootSystem();

        void update(std::vector<EntityID> &allEntities) override;

        void create_loot(Vector3 pos, std::string lootName);

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
};

