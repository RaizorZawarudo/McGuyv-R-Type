/*
** EPITECH PROJECT, 2022
** McGuyverType
** File description:
** AISystem
*/

#include "BotSystem.hpp"

BotSystem::BotSystem(std::shared_ptr<EntityManager> em)
{
    _em = em;
}

BotSystem::~BotSystem()
{
}

void BotSystem::update(std::vector<EntityID> &allEntities)
{
    for (EntityID ent : EntityViewer<AI>(*_em.get())) {
        if (_em->Get<AI>(ent)->style == "simple")
            doAI_simple(ent);
    }
}

void BotSystem::doAI_simple(EntityID ennemy)
{
    //dodge bullets and update movement keys input
    _em->Get<Input>(ennemy)->_inputQueue.emplace_back(0x0A);

    //check for obstacles and update movement keys

}
