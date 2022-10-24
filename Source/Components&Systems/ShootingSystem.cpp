/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** ShootingSystem
*/

#include "ShootingSystem.hpp"

//add soundmanager
ShootingSystem::ShootingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager)
{
    _em = em;
    _assetManager = assetManager;
}

ShootingSystem::~ShootingSystem()
{
}

void ShootingSystem::update(std::vector<EntityID> &allEntities)
{
    bool haspressedShield = false;
    for (EntityID ent : EntityViewer<Position, Input, IsAlive, Weaponset>(*_em.get())) { //creatre a timer system that updates all timers i guess?
        Position* entityPos = _em->Get<Position>(ent);
        Input* keypresses = _em->Get<Input>(ent);
        EntityModelType* entityType = _em->Get<EntityModelType>(ent);
        Weaponset* weaponSet = _em->Get<Weaponset>(ent);
        ModelDimensions* modelDimensions = _em->Get<ModelDimensions>(ent);
        if (entityType->modelType == RL::ModelType::SPACESHIP ||entityType->modelType == RL::ModelType::ENNEMY) {
            for (int keypressed : keypresses->_inputQueue) {
                if (keypressed == SHOOT) {
                    createProjectile(entityPos, weaponSet, modelDimensions, ent, entityType);
                }
                if (keypressed == SHIELD) {
                    haspressedShield= true;
                    _em->Get<Shield>(ent)->shieldActive = true;
                }
                if(keypressed == FIRSTWEAPON) switchWeapon(0, weaponSet);
                if(keypressed == SECONDWEAPON) switchWeapon(1, weaponSet);
                // if(keypressed == THIRDWEAPON) switchWeapon(2);
            }
            if (!haspressedShield)
                _em->Get<Shield>(ent)->shieldActive = false;
        }
    }
}

void ShootingSystem::createProjectile(Position* entityPos, Weaponset* weaponSet, ModelDimensions* modelDimensions, EntityID ownerID, EntityModelType* ownerModelType) //add clockcomponent that has a clock inside
{
    //if timer of weapon > cooldown
    if ((weaponSet->weapons.at(weaponSet->currentWeapon).curAmmo > 0 || weaponSet->weapons.at(weaponSet->currentWeapon).curAmmo == -999) &&
        GetTime() - weaponSet->weapons.at(weaponSet->currentWeapon).lasttimeweaponwasshot >  weaponSet->weapons.at(weaponSet->currentWeapon).cooldowninseconds) {
        weaponSet->weapons.at(weaponSet->currentWeapon).curAmmo > 0 ? 
        weaponSet->weapons.at(weaponSet->currentWeapon).curAmmo -= 1 : weaponSet->weapons.at(weaponSet->currentWeapon).curAmmo -= 0; // reduce ammo by one unit or do nothing if unlimited ammo
        weaponSet->weapons.at(weaponSet->currentWeapon).lasttimeweaponwasshot = GetTime();// reset cooldown

        EntityID id = _em->CreateNewEntity();
        //register this entity as the player for this client
        _em->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::PROJECTILE});
        _em->Assign<Owner>(id, Owner{ownerID, ownerModelType->modelType});
        _em->Assign<IsAlive>(id, IsAlive{true});
        _em->Assign<ModelName>(id, ModelName{weaponSet->weapons.at(weaponSet->currentWeapon).modelName,_assetManager->getSpecificDrawableWithType(weaponSet->weapons.at(weaponSet->currentWeapon).modelName, RL::ModelType::PROJECTILE)->getExplosionName()});
        _em->Assign<ModelScale>(id, ModelScale{_assetManager->getSpecificDrawableWithType(weaponSet->weapons.at(weaponSet->currentWeapon).modelName, RL::ModelType::PROJECTILE)->getScale()});
        _em->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(weaponSet->weapons.at(weaponSet->currentWeapon).modelName, RL::ModelType::PROJECTILE)->getWidth(),
                                                        _assetManager->getSpecificDrawableWithType(weaponSet->weapons.at(weaponSet->currentWeapon).modelName, RL::ModelType::PROJECTILE)->getHeight(),
                                                        _assetManager->getSpecificDrawableWithType(weaponSet->weapons.at(weaponSet->currentWeapon).modelName, RL::ModelType::PROJECTILE)->getLength()});
        _em->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
        _em->Assign<Collider>(id, Collider{BoundingBox{}});


        _em->Assign<Position>(id, {entityPos->pos.x,
                                   entityPos->pos.y,
                                   entityPos->pos.z + (((modelDimensions->lengthZ /2) + (_em->Get<ModelDimensions>(id)->lengthZ / 2)) * (- ownerModelType->modelType))});
        _em->Assign<Velocity>(id, {weaponSet->weapons.at(weaponSet->currentWeapon).vel.x,
                                   weaponSet->weapons.at(weaponSet->currentWeapon).vel.y,
                                   weaponSet->weapons.at(weaponSet->currentWeapon).vel.z}); // very important  x - OWNERTYPE to change de direction of the bullet, to do in movement system if entity is projectile

        _em->Assign<Hp>(id, Hp{_assetManager->getSpecificDrawableWithType(weaponSet->weapons.at(weaponSet->currentWeapon).modelName, RL::ModelType::PROJECTILE)->getHp()});

        _em->Assign<ProjectileWeapon>(id, ProjectileWeapon{weaponSet->weapons.at(weaponSet->currentWeapon)});

        //play sound of specific weapon being fired, to add in csv the sound name :)

        std::cout << "player 1 is at position : " << entityPos->pos.x << " " << entityPos->pos.y << " " << entityPos->pos.z << std::endl;
        std::cout << "shooting bullet at position" << _em->Get<Position>(id)->pos.x << " " << _em->Get<Position>(id)->pos.y << " " << _em->Get<Position>(id)->pos.z << std::endl;
        std::cout << "owner id : " << _em->Get<Owner>(id)->id << std::endl;
    }
    else {
        //play empty gun sound
        //
        
    }



}

void ShootingSystem::switchWeapon(int weaponIndex, Weaponset* weaponSet)
{
    if (weaponSet->weapons.size() >= weaponIndex + 1) {
        weaponSet->currentWeapon = weaponIndex;
    }
}
