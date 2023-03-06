/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** ShootingSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../AssetManager.hpp"
#include "../Renderer.hpp"

class ShootingSystem : public ISystem  {
    public:
        ShootingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager);
        ~ShootingSystem();

        void update(std::vector<EntityID> &allEntities) override;
        void switchWeapon(int weaponindex, Weaponset* weaponSet);
        void dropWeapon(Weaponset* weaponSet);

        void createProjectile(Position* entityPos, Weaponset* weaponSet, ModelDimensions* modelDimensions, EntityID ownerID, EntityModelType* ownerModelType);
    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
};

