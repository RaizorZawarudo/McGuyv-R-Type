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
#include "SoundManager.hpp"
#include "Renderer.hpp"
#include "CameraManager.hpp"
#include "ECS/EntityManager.hpp"
#include "ECS/EntityViewer.hpp"
#include "ECS/ComponentPool.hpp"
#include "ECS/EntityManager.hpp"
#include "Components&Systems/ISystem.hpp"
#include "Components&Systems/Components.hpp"
#include "Components&Systems/MovementSystem.hpp"
#include "Components&Systems/InputSystem.hpp"
#include "Components&Systems/ClearInputsSystem.hpp"
#include "Components&Systems/DrawingSystem.hpp"
#include "Components&Systems/DeleteEntitiesSystem.hpp"
#include "Components&Systems/DataReceivingSystem.hpp"
#include "MenuManager.hpp"
#include "Networking/UDPClient.hpp"

#include <thread>
#include <atomic>

#pragma once

class McGuyverType {
    public:
        McGuyverType();
        ~McGuyverType();

        void startGame();

        void gameLoop();

        void udpClientThreadFunction();

        //entity creation functions
        void createSeggySafe();

        //getters
        std::shared_ptr<EntityManager> getEm();

    protected:
    private:
        std::chrono::system_clock::time_point _startTimestamp; // initialized at the start of the game
        std::shared_ptr<AssetManager> _assetManager;
        
        std::thread _udpClientThread;
        std::atomic<bool> _isEnd{false};
        boost::asio::io_context _ioContext;;
        std::shared_ptr<UDPClient> _udpClient;
        
        std::shared_ptr<RL::SoundManager> _soundManager;
        std::shared_ptr<RL::CameraManager> _cameraManager;
        std::shared_ptr<RL::InputManager> _inputManager;
        std::shared_ptr<RL::Renderer> _renderer;
        std::shared_ptr<RL::Window> _window;
        std::shared_ptr<EntityManager> _entityManager;
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::shared_ptr<RL::MenuManager> _menuManager;
        Serializator _serializator;
        
        std::vector<int> _keysPressed; //the pressed by player must be saved every frame

        //Entities
        std::vector<EntityID> _allEntities;
        std::vector<EntityID> _players;

        //game related data     
        int _currentLevel = 0;
        float _playerStartingZ = 8.0f; //can delete
        float enemyStartingZ = 20.0f; // cand delete

        EntityID _thisClientPlayerEntityID = 100000; //create a rand function where initiatilising client to have a unique ID for networking
};

