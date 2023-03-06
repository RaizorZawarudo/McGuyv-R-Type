/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** DrawingSystem
*/


#pragma once

#include "ISystem.hpp"
#include "../InputManager.hpp"


class InputSystem : public ISystem {
    public:
        InputSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::InputManager> inputManager, EntityID clientID) : _inputManager(inputManager) {
            _em = em;
            _clientID = clientID;
        }
        ~InputSystem();

        void update(std::vector<EntityID> &allEntities) override;

    private:
        std::vector<int> _keysPressed; //to be changed to vector of vector when networking is implemeneted
        std::shared_ptr<RL::InputManager> _inputManager;
        EntityID _clientID;
};
