/*
** EPITECH PROJECT, 2023
** MCGUYVER-TYPE_EPITECH
** File description:
** DataReceivingSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../AssetManager.hpp"
#include "../MenuManager.hpp"
#include "Components.hpp"
#include "../InputManager.hpp"
#include "../Networking/UDPClient.hpp"
#include "../../Server/Networking/protocol/Serializator.hpp"

const float MOVEBUFFER = 0.1f;
const float RANGEBUFFER = 1.0;

const float SIMPLEAIMOVECOOLDOWN = 2.5;
const float SIMPLEAIMOVEDETECTRANGE = 10.0;
const float SIMPLEAITARGETPLAYERDETECTRANGE = 60;
const int SIMPLEMOVERANGE = 7.0;

const float SIMPLEAISHOOTCOOLDOWN = 3;
const float SIMPLEAISHOOTDETECTRANGE = 30;

class DataReceivingSystem : public ISystem {
    public:
        DataReceivingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::InputManager> inputManager,std::shared_ptr<RL::MenuManager> _menuManager, std::shared_ptr<UDPClient> ); //add deserialiser to constructor
        ~DataReceivingSystem();

        void update(std::vector<EntityID> &allEntities) override;


        //ALL THE CREATE FUNCTIONS BELOW NEED AN EXTRA PARAMETER WHICH IS AN ID SENT BY SERVER
        void createPlayerClient(std::string modelName, unsigned long long ID, unsigned long long clientHashID);
        void createObstacleClient(std::string modelName, Vector3 position, unsigned long long ID);
        void createEnnemyClient(std::string modelName, Vector3 position, unsigned long long ID);
        void createProjectileClient(Vector3 entityPos, int weaponIndex, EntityID ownerID, int direction, unsigned long long ID);
        void create_lootClient(Vector3 pos, std::string lootName, unsigned long long ID);
        ProjectileWeapon generateWeaponLootClient(std::string projectileName);
        Shield generateShieldLootClient();        
        AI assignAI(std::string AIType, EntityID ennemy);
        AI assignSimpleAI(std::string AIType, EntityID ennemy);
        std::vector<ProjectileWeapon> generateStartWeaponset(std::string modelName);
        std::vector<ProjectileWeapon> generateStartWeaponsetEnnemies(std::string modelName);
        void create_explosion(Vector3 pos, std::string exploName, unsigned long long ID);
        void createEntities(EntityID, char);
        void applyNewPosition(EntityID id, int x, int y, int z, int pitch, int yaw, int roll);

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
        std::shared_ptr<RL::MenuManager> _menuManager;
        //add deserialiser
        Position _playerStartingPos = {0.0f, 1.0f, -8.0f};
        bool _createdplayer = false;
        std::shared_ptr<UDPClient> _udpClient;
        Serializator _serializator;



        std::vector<int> _keysPressed; //to be changed to vector of vector when networking is implemeneted
        std::shared_ptr<RL::InputManager> _inputManager;
};

