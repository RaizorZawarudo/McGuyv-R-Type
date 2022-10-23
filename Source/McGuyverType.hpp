/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** McGuyverType
*/

#include "raylib.h"
#include "Window.hpp"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "InputManager.hpp"
#include "Renderer.hpp"
#include "CameraManager.hpp"
#include "ECS/EntityManager.hpp"
#include "ECS/EntityViewer.hpp"
#include "ECS/ComponentPool.hpp"
#include "ECS/EntityManager.hpp"
#include "Components&Systems/ISystem.hpp"
#include "Components&Systems/Components.hpp"
#include "Components&Systems/ShootingSystem.hpp"
#include "Components&Systems/MovementSystem.hpp"
#include "Components&Systems/InputSystem.hpp"
#include "Components&Systems/ClearInputsSystem.hpp"
#include "Components&Systems/DrawingSystem.hpp"
#include "Components&Systems/DeleteEntitiesSystem.hpp"
#include "Components&Systems/CollisionSystem.hpp"
// #include "CollisionManager.hpp"

#pragma once

class McGuyverType {
    public:
        McGuyverType();
        ~McGuyverType();

        void startGame();

        void gameLoop();

        //entity creation functions
        void createPlayer(std::string modelName, std::string avatarName);
        void createObstacle(std::string modelName, Vector3 position);
        std::vector<ProjectileWeapon> generateStartWeaponset(std::string modelName);
        //void createEnnemy();
        //void createProjectile();
        //void createObstacle();
        //void createPowerup();

        //getters
        std::shared_ptr<EntityManager> getEm();

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
        std::shared_ptr<RL::CameraManager> _cameraManager;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Renderer> _renderer;
        std::shared_ptr<RL::Window> _window;
        // std::shared_ptr<RL::CollisionManager> _collisionManager;
        std::shared_ptr<EntityManager> _entityManager;
        std::vector<std::shared_ptr<ISystem>> _systems;

        
        std::vector<int> _keysPressed; //the pressed by player must be saved every frame

        //Entities
        std::vector<EntityID> _allEntities;
        std::vector<EntityID> _players;

        //game related data     
        int _currentLevel = 1;
        Position _playerStartingPos = {0.0f, 1.0f, -8.0f};
        Position _ennemyStartingPos = {0.0f, 4.0f, 20.0f}; //can delete 
        float _playerStartingZ = 8.0f; //can delete
        float enemyStartingZ = 20.0f; // cand delete

        EntityID _thisClientPlayerEntityID = -1000; //create a rand function where initiatilising client to have a unique ID for networking
        //timer
        //gamepaused
        //ui-related stuff
        //drawable2D to be added to the assetmanager !!
        //enemy waves and obstacle waves to be added to assetmanager!!



        //main transfer functions to remake archi : DELETE ASAP
        int spaceshipIndex = 0;
        int ennemyIndex = 0;
        int projectileIndex = 0;
};

