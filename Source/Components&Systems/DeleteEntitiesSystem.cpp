/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** DeleteEntitiesSystem
*/

#include "DeleteEntitiesSystem.hpp"


DeleteEntitiesSystem::DeleteEntitiesSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager) : _assetManager(assetManager)
{
    _em = em;
}

DeleteEntitiesSystem::~DeleteEntitiesSystem()
{
}

//to update to all delete cases
//NOT FINISHED, HAVE TO DECIDE HOW WE DELETE PLAYER ENTITIES
void DeleteEntitiesSystem::update(std::vector<EntityID> &allEntities)
{
    for (EntityID ent : EntityViewer<Position, IsAlive>(*_em.get())) {
         if (!_em->Get<IsAlive>(ent)->alive && _em->Get<EntityModelType>(ent)->modelType == RL::ModelType::POWERUP ) {
            _em->Remove<Timer>(ent);
            _em->Remove<Position>(ent);
            _em->Remove<EntityModelType>(ent);
            _em->Remove<Input>(ent);
            _em->Remove<IsAlive>(ent);
            _em->Remove<Velocity>(ent);
            _em->Remove<PitchYawRoll>(ent);
            _em->Remove<Collider>(ent);
            _em->Remove<ModelDimensions>(ent);
            _em->Remove<Owner>(ent);
            _em->Remove<Loot>(ent);
            _em->DestroyEntity(ent);
            continue;
         }


        if (_em->Get<EntityModelType>(ent)->modelType == RL::ModelType::POWERUP && (GetTime() -_em->Get<Timer>(ent)->lastTimeClocked > _em->Get<Timer>(ent)->cooldowninseconds)) {
            _em->Remove<Timer>(ent);
            _em->Remove<Position>(ent);
            _em->Remove<EntityModelType>(ent);
            _em->Remove<Input>(ent);
            _em->Remove<IsAlive>(ent);
            _em->Remove<Velocity>(ent);
            _em->Remove<ModelDimensions>(ent);
            _em->Remove<PitchYawRoll>(ent);
            _em->Remove<Collider>(ent);
            _em->Remove<Owner>(ent);
            _em->DestroyEntity(ent);
            continue;
        }

        if (_em->Get<EntityModelType>(ent)->modelType == RL::ModelType::SPACESHIP && _em->Get<Owner>(ent)->id == _assetManager->getCurrentClientID()
            && !_em->Get<IsAlive>(ent)->alive) {
            _em->Remove<Position>(ent);
            _em->Remove<Input>(ent);
            _em->Remove<Velocity>(ent);
            _em->Remove<PitchYawRoll>(ent);
            _em->Remove<Collider>(ent);
            continue;
        }

        if ( (_em->Get<EntityModelType>(ent)->modelType == RL::ModelType::ENNEMY  && !_em->Get<IsAlive>(ent)->alive)) {
            _em->Remove<Position>(ent);
            _em->Remove<EntityModelType>(ent);
            _em->Remove<Weaponset>(ent);
            _em->Remove<Input>(ent);
            _em->Remove<IsAlive>(ent);
            _em->Remove<Velocity>(ent);
            _em->Remove<PitchYawRoll>(ent);
            _em->Remove<Collider>(ent);
            _em->Remove<Owner>(ent);
            _em->DestroyEntity(ent);
            continue;
        }

        else if ( (_em->Get<EntityModelType>(ent)->modelType == RL::ModelType::SPACESHIP  && !_em->Get<IsAlive>(ent)->alive) || (_em->Get<Position>(ent)->pos.z > MAXPOSSIBLEZ || _em->Get<Position>(ent)->pos.z < MINPOSSIBLEZ || !_em->Get<IsAlive>(ent)->alive)) {
            _em->Remove<Position>(ent);
            _em->Remove<EntityModelType>(ent);
            _em->Remove<Weaponset>(ent);
            _em->Remove<Input>(ent);
            _em->Remove<IsAlive>(ent);
            _em->Remove<Velocity>(ent);
            _em->Remove<PitchYawRoll>(ent);
            _em->Remove<Collider>(ent);
            _em->Remove<Owner>(ent);
            _em->DestroyEntity(ent);
        }
    }
}
