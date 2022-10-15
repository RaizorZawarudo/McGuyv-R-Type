/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** McGuyverType
*/

#include "raylib.h"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "InputManager.hpp"
#include "Renderer.hpp"
#include "CameraManager.hpp"
#include "ECS/EntityViewer.hpp"
#include "Window.hpp"
// #include "CollisionManager.hpp"

#pragma once

class McGuyverType {
    public:
        McGuyverType();
        ~McGuyverType();

        void startGame();

        void gameLoop();

        //entity creation functions
        //void createPlayer();
        //void createEnnemy();
        //void createProjectile();
        //void createObstacle();
        //void createPowerup();

    protected:
    private:
        std::shared_ptr<AssetManager> _assetManager;
        std::shared_ptr<RL::CameraManager> _cameraManager;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Renderer> _renderer;
        std::shared_ptr<RL::Window> _window;
        // std::shared_ptr<RL::CollisionManager> _collisionManager;
        std::shared_ptr<EntityManager> _entityManager;
        //std::shared_ptr<std::shared_ptr<ISystems>> _systems;

        //the pressed by player must be saved every frame
        std::vector<int> _keysPressed;

        //game related data
        int _currentLevel = 1;
        float _playerStartingZ = 8.0f;
        float enemyStartingZ = 20.0f;
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

