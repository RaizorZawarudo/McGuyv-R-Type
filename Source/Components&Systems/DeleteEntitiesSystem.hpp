/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** DeleteEntitiesSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../AssetManager.hpp"

const int MAXPOSSIBLEZ = 70;
const int MINPOSSIBLEZ = -10;

class DeleteEntitiesSystem : public ISystem  {
    public:
        DeleteEntitiesSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager);
        ~DeleteEntitiesSystem();

        void update(std::vector<EntityID> &allEntities) override;

    protected:
    private:
    std::shared_ptr<AssetManager> _assetManager;
};


