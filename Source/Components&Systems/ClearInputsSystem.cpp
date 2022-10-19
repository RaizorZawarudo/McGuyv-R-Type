/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** ClearInputsSystem
*/

#include "ClearInputsSystem.hpp"

ClearInputsSystem::~ClearInputsSystem()
{
}

void ClearInputsSystem::update(std::vector<EntityID> &allEntities)
{
    for (EntityID _ent:  EntityViewer<Input>(*_em.get()) )
        _em->Get<Input>(_ent)->_inputQueue.clear();
    _inputManager->popInputs();
}

