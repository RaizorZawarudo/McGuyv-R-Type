/*
** EPITECH PROJECT, 2022
** McGuyverType
** File description:
** AISystem
*/

#pragma once

#include "ISystem.hpp"
#include "Components.hpp"
#include "../AssetManager.hpp"

const float MOVEBUFFER = 0.1f;

const float SIMPLEAIMOVECOOLDOWN = 3.0;
const float SIMPLEAIMOVEDETECTRANGE = 10.0;
const int SIMPLEMOVERANGE = 7.0;

const float SIMPLEAISHOOTCOOLDOWN = 2.0;
const float SIMPLEAISHOOTDETECTRANGE = 20;

class BotSystem : public ISystem {
    public:
        BotSystem(std::shared_ptr<EntityManager> em , std::shared_ptr<AssetManager> assetManager);
        ~BotSystem();
        void update(std::vector<EntityID> &allEntities) override;
        void doAI_simple(EntityID ennemy);


        void dodge_bullets(EntityID ennemy);
        Vector3 findSafeSpotfromProjectile(EntityID ennemy);
        void applyAIInputDodgeProjectile(EntityID ennemy);
        bool is_in_range(EntityID ennemy);


        void fire_weapon_ennemy(EntityID ennemy);

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
};