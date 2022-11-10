/*
** EPITECH PROJECT, 2022
** McGuyverType
** File description:
** AISystem
*/

#pragma once

#include "ISystem.hpp"
#include "Components.hpp"

class BotSystem : public ISystem {
    public:
        BotSystem(std::shared_ptr<EntityManager> em);
        ~BotSystem();
        void update(std::vector<EntityID> &allEntities) override;
        void doAI_simple(EntityID ennemy);

        protected:
    private:
};