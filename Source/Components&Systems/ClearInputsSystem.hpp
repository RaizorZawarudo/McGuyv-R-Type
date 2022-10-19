/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** ClearInputsSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../InputManager.hpp"

class ClearInputsSystem : public ISystem {
    public:
        ClearInputsSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::InputManager> inputManager) : _inputManager(inputManager)
        {
            _em = em;
        }
        ~ClearInputsSystem();

        void update(std::vector<EntityID> &allEntities) override;

    protected:
    private:
        std::shared_ptr<RL::InputManager> _inputManager;
};

