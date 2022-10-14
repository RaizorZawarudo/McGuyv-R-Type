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
};

