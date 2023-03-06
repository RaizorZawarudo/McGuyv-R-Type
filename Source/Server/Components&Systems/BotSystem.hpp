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
const float RANGEBUFFER = 1.0;

const float SIMPLEAIMOVECOOLDOWN = 2.5;
const float SIMPLEAIMOVEDETECTRANGE = 10.0;
const float SIMPLEAITARGETPLAYERDETECTRANGE = 60;
const int SIMPLEMOVERANGE = 7.0;

const float SIMPLEAISHOOTCOOLDOWN = 3;
const float SIMPLEAISHOOTDETECTRANGE = 30;

class BotSystem : public ISystem {
    public:
        BotSystem(std::shared_ptr<EntityManager> em , std::shared_ptr<AssetManager> assetManager);
        ~BotSystem();
        void update(std::vector<EntityID> &allEntities) override;
        void doAI_simple(EntityID ennemy);


        void dodge_bullets(EntityID ennemy);
        Vector3 findSafeSpotfromProjectile(EntityID ennemy, float ennemyPosX, float ennemyPosY);
        void applyAIKeystrokes(EntityID ennemy);
        bool is_in_range_of_target(EntityID ennemy);
        bool check_for_vicinity(float x, float y);

        void dodge_obstacles(EntityID ennemy);

        void find_player_target(EntityID ennemy);


        void fire_weapon_ennemy(EntityID ennemy);

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
};
