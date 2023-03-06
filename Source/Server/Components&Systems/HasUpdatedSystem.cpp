/*
** EPITECH PROJECT, 2023
** RType
** File description:
** HasUpdatedSystem
*/

#include "HasUpdatedSystem.hpp"

HasUpdatedSystem::HasUpdatedSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<UDPServer> udpServer, std::shared_ptr<AssetManager> assetManager) : _em(em), _udpServer(udpServer), _assetManager(assetManager)
{
}

int HasUpdatedSystem::getIndexModel(RL::ModelType type, EntityID id)
{
    switch(type) {
        case RL::ModelType::SPACESHIP:
            for(int i = 0; i < _assetManager->getSpacecraftModels().size(); i++)
                if (_assetManager->getSpacecraftModels().at(i)->getName() == _em->Get<ModelName>(id)->modelname)
                    return i;
            break;
        case RL::ModelType::ENNEMY:
            for(int i = 0; i < _assetManager->getEnnemyModels().size(); i++)
                if (_assetManager->getEnnemyModels().at(i)->getName() == _em->Get<ModelName>(id)->modelname)
                    return i;
            break;
        case RL::ModelType::PROJECTILE:
            for(int i = 0; i < _assetManager->getProjectileModels().size(); i++)
                if (_assetManager->getProjectileModels().at(i)->getName() == _em->Get<ModelName>(id)->modelname)
                    return i;
            break;
        case RL::ModelType::POWERUP:
            for(int i = 0; i < _assetManager->getPowerUpModels().size(); i++)
                if (_assetManager->getPowerUpModels().at(i)->getName() == _em->Get<ModelName>(id)->modelname)
                    return i;
            break;
        case RL::ModelType::OBSTACLE:
            for(int i = 0; i < _assetManager->getObstacleModels().size(); i++)
                if (_assetManager->getObstacleModels().at(i)->getName() == _em->Get<ModelName>(id)->modelname)
                    return i;
            break;
        default:
            break;
    }
}

void HasUpdatedSystem::sendCreatedEntity(EntityID id)
{
    Position* entityPos = _em->Get<Position>(id);
    int indexModel = getIndexModel(_em->Get<EntityModelType>(id)->modelType, id);
    char *package = nullptr;
    PitchYawRoll *pyr = _em->Get<PitchYawRoll>(id);

    Msg res;
    switch(_em->Get<EntityModelType>(id)->modelType) {
        case RL::ModelType::SPACESHIP:
            package = _serializator.createPackageUpdPlayer(serializator::Header::UpdatePlayer, indexModel, entityPos->pos.x, entityPos->pos.y, entityPos->pos.z, pyr->pitch, pyr->yaw, pyr->roll, id, _em->Get<Owner>(id)->id);
            res = _serializator.bytesToStruct(package);
            _udpServer->send(package, SIZE_UPDATE_PLAYER);
            break;
        case RL::ModelType::ENNEMY:
            package = _serializator.createPackageUpdEnnemies(serializator::Header::UpdateEnnemy, indexModel, entityPos->pos.x, entityPos->pos.y, entityPos->pos.z, pyr->pitch, pyr->yaw, pyr->roll ,id);
            _udpServer->send(package, SIZE_UPDATE_ENNEMY);
            break;
        case RL::ModelType::PROJECTILE:
            package = _serializator.createPackageUpdProjectile(serializator::Header::UpdateProjectile, indexModel, entityPos->pos.x, entityPos->pos.y, entityPos->pos.z, id, _em->Get<Owner>(id)->ownerType, _em->Get<Owner>(id)->id);
            _udpServer->send(package, SIZE_UPDATE_PROJECTILE);
            break;
        case RL::ModelType::POWERUP:
            package = _serializator.createPackageUpdPowerUp(serializator::Header::UpdateLoot, indexModel, entityPos->pos.x, entityPos->pos.y, entityPos->pos.z, id);
            _udpServer->send(package, SIZE_UPDATE_LOOT);
            break;
        case RL::ModelType::OBSTACLE:
        package = _serializator.createPackageUpdObs(serializator::Header::UpdateObstacle, indexModel, entityPos->pos.x, entityPos->pos.y, entityPos->pos.z, id);
            _udpServer->send(package, SIZE_UPDATE_LOOT);
            break;
        case RL::ModelType::EXPLOSION:
            package = _serializator.createPackageUpdExplosion(serializator::Header::UpdateExplosion, indexModel, entityPos->pos.x, entityPos->pos.y, entityPos->pos.z, id);
            _udpServer->send(package, SIZE_UPDATE_LOOT);
            break;
        default:
            break;
        }
        delete package;
}

void HasUpdatedSystem::update(std::vector<EntityID> &allEntities)
{
    if (_assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->getIsFightingBoss() && !_sentFightingBoss) {
        char *package = nullptr;
        package = _serializator.createPackageStateGame(serializator::Header::stateGame, true);
        _udpServer->send(package, SIZE_STATE_GAME);
        delete package;
        _sentFightingBoss = true;
    }
    // Get entities that have the component HasUpdated set to true
    for (EntityID _ent:  EntityViewer<HasUpdated>(*_em.get()) ) {
        Position* entityPos = _em->Get<Position>(_ent);
        EntityModelType *modelType = _em->Get<EntityModelType>(_ent);
        // std::cout << "CHECK UPDATE  " << _em->Get<ModelName>(_ent)->modelname << std::endl;
        if (_em->Get<HasUpdated>(_ent)->updated) { // CASE UPDATE
            sendCreatedEntity(_ent);
        }
        _em->Get<HasUpdated>(_ent)->updated = false;
    }
}
