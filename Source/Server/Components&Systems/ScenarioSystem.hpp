/*
** EPITECH PROJECT, 2023
** MCGUYVER-TYPE_EPITECH
** File description:
** ScenarioSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../AssetManager.hpp"
#include "DeleteEntitiesSystem.hpp"
#include "BotSystem.hpp"

class ScenarioSystem : public ISystem {
    public:
        ScenarioSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager);
        ~ScenarioSystem();

        void update(std::vector<EntityID> &allEntities) override;

        void createObstacleWave(std::string waveName);
        void createObstacle(std::string modelName, Vector3 position);

        void createEnnemyWave(std::string waveName);
        void createEnnemy(std::string modelName, Vector3 position);

        std::vector<ProjectileWeapon> generateStartWeaponsetEnnemies(std::string modelName);

        AI assignAI(std::string AIType, EntityID ennemy);
        AI assignSimpleAI(std::string AIType, EntityID ennemy);

    protected:
    private:
        std::chrono::system_clock::time_point _wavetimer;
        std::shared_ptr<AssetManager> _assetManager;
        float _wavedelay = 3;

};
