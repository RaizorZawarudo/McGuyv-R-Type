/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** CollisionSystem
*/

#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager) : _assetManager(assetManager)
{
    _em = em;
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(std::vector<EntityID> &allEntities)
{
    for (EntityID ent : EntityViewer<Position, Collider>(*_em.get())) {
        for (EntityID other : EntityViewer<Position, Collider>(*_em.get())) {
            if ( ent != other) {
                bullet_collisions(ent, other);
                obstacle_collisions(ent,other);
                powerUp_collisons(ent, other);
                // body_collisions(ent, other);
            }
        }
    }
}

void CollisionSystem::bullet_collisions(EntityID projectile, EntityID other)
{
    if (_em->Get<EntityModelType>(other)->modelType == RL::ModelType::POWERUP)
        return;
    if (_em->Get<EntityModelType>(projectile)->modelType != RL::ModelType::PROJECTILE)
        return;
    if (!_em->Get<IsAlive>(projectile)->alive)
        return;
    // Position* projectilePos = _em->Get<Position>(projectile);
    // Position* otherPos = _em->Get<Position>(other);
    Collider* projectileCollider = _em->Get<Collider>(projectile);
    Collider* otherCollider = _em->Get<Collider>(other);
    if (CheckCollisionBoxes(projectileCollider->collider, otherCollider->collider)) {

        std::cout << _em->Get<ModelName>(projectile)->modelname << " collided with " << _em->Get<ModelName>(other)->modelname << std::endl;
        //create bullet impact (another explosion) entity with the path stored in the projectile´s components ==> createExplosion(_em->Get<ExplosionName>)(projectile)->name); this one has to be super small preferably except for badabig weapons

        //set bullet to dead
        _em->Get<IsAlive>(projectile)->alive = false;

        //reduce other shield or hp by bullet damage
        if (_em->Get<Shield>(other)) {
            _em->Get<Shield>(other)->shieldActive ? _em->Get<Shield>(other)->shield -= _em->Get<Hp>(projectile)->hp / 2 : _em->Get<Hp>(other)->hp -= _em->Get<Hp>(projectile)->hp;
            if ( _em->Get<Shield>(other)->shield < 0) {
                _em->Get<Hp>(other)->hp += _em->Get<Shield>(other)->shield;
                _em->Get<Shield>(other)->shield = 0;
            }
        }
        else {
            _em->Get<Hp>(other)->hp -= _em->Get<Hp>(projectile)->hp;
        }
        
        // give points to owner
        _em->Get<Score>(_em->Get<Owner>(projectile)->id)->score += _em->Get<Hp>(projectile)->hp;

        //check if other hp is below zero : if yes set it to dead and create an explosion entity with the explosion path stored in the other´s components ==>  createExplosion(_em->Get<ExplosionName>(other)->name);
        if (_em->Get<Hp>(other)->hp <= 0) {
            _em->Get<IsAlive>(other)->alive = false;
            Position* projectilePos = _em->Get<Position>(projectile);
            ModelName* otherName = _em->Get<ModelName>(other);
            create_explosion(projectilePos->pos, otherName->explosionname);
        }
    }
}

void CollisionSystem::obstacle_collisions(EntityID obstacle, EntityID other)
{
    if (_em->Get<EntityModelType>(other)->modelType == RL::ModelType::POWERUP)
        return;
    if (_em->Get<EntityModelType>(obstacle)->modelType != RL::ModelType::OBSTACLE)
        return;
    if (_em->Get<EntityModelType>(other)->modelType == RL::ModelType::OBSTACLE || _em->Get<EntityModelType>(other)->modelType == RL::ModelType::PROJECTILE)
        return;
    if (!_em->Get<IsAlive>(obstacle)->alive)
        return;
    
    Collider* obstacleCollider = _em->Get<Collider>(obstacle);
    Collider* otherCollider = _em->Get<Collider>(other);
    if (CheckCollisionBoxes(obstacleCollider->collider, otherCollider->collider)) {
        std::cout << _em->Get<ModelName>(obstacle)->modelname << " collided with " << _em->Get<ModelName>(other)->modelname << std::endl;
       

        //reduce other shield or hp by obstacle hp
        if (_em->Get<Shield>(other)) {
            _em->Get<Shield>(other)->shieldActive ? _em->Get<Shield>(other)->shield -= _em->Get<Hp>(obstacle)->hp / 2 : _em->Get<Hp>(other)->hp -= _em->Get<Hp>(obstacle)->hp;
            if ( _em->Get<Shield>(other)->shield < 0) {
                _em->Get<Hp>(other)->hp += _em->Get<Shield>(other)->shield;
                _em->Get<Shield>(other)->shield = 0;
            }
        }
        else {
            _em->Get<Hp>(other)->hp -= _em->Get<Hp>(obstacle)->hp;
        }
        //check if other hp is below zero : if yes set it to dead and create an explosion entity with the explosion path stored in the other´s components ==>  createExplosion(_em->Get<ExplosionName>(other)->name);
        if (_em->Get<Hp>(other)->hp <= 0) {
            _em->Get<IsAlive>(other)->alive = false;
            Position* obstaclePos = _em->Get<Position>(obstacle);
            ModelName* otherName = _em->Get<ModelName>(other);
            create_explosion(obstaclePos->pos, otherName->explosionname);
            std::cout << "client ID collisions system" << _assetManager->getCurrentClientID() << std::endl;
         }
        _em->Get<IsAlive>(obstacle)->alive = false;
        Position* obstaclePos = _em->Get<Position>(obstacle);
        ModelName* obstacleName = _em->Get<ModelName>(obstacle);
        create_explosion(obstaclePos->pos, obstacleName->explosionname);
    }
}

void CollisionSystem::powerUp_collisons(EntityID powerup, EntityID other)
{
    if (!_em->Get<IsAlive>(powerup)->alive || !_em->Get<IsAlive>(other)->alive)
        return;
    //no create explosion here, just add a pickup powerup sound.
    if (_em->Get<EntityModelType>(other)->modelType == RL::ModelType::POWERUP)
        return;
    if (_em->Get<EntityModelType>(powerup)->modelType != RL::ModelType::POWERUP)
        return;
    if (_em->Get<PowerUpType>(powerup)->type == PowerUpEnum::WEAPONPOWER) {
        if (_em->Get<EntityModelType>(other)->modelType == RL::ModelType::SPACESHIP) { //add ennemy type when u create AI to change weapon for them
            Collider* powerupCollider = _em->Get<Collider>(powerup);
            Collider* otherCollider = _em->Get<Collider>(other);
            if (CheckCollisionBoxes(powerupCollider->collider, otherCollider->collider)) {
                std::cout << "collinding with player by powerup" << std::endl;
                pick_up_weaponLoot(powerup, other);
                _em->Get<IsAlive>(powerup)->alive = false;
            }

        }
    }
}

void CollisionSystem::pick_up_weaponLoot(EntityID powerup, EntityID other)
{
    //check if the player already has the weapon in base weapon
    if (_em->Get<Weaponset>(other)->weapons.at(0).modelName == _em->Get<Loot>(powerup)->weaponLoot.name)
        return;
    for (int i = _em->Get<Weaponset>(other)->weapons.size()- 1; i < _em->Get<Weaponset>(other)->weapons.size(); i++) { 
        //check if he has the weapon already looted to increase its ammo       
        if (_em->Get<Weaponset>(other)->weapons.at(i).modelName == _em->Get<Loot>(powerup)->weaponLoot.modelName) {
            _em->Get<Weaponset>(other)->weapons.at(i).curAmmo += _em->Get<Loot>(powerup)->weaponLoot.curAmmo;
            _em->Get<Weaponset>(other)->weapons.at(i).curAmmo > 999 ? _em->Get<Weaponset>(other)->weapons.at(i).curAmmo = 999 : _em->Get<Weaponset>(other)->weapons.at(i).curAmmo + 0;
            return;
        }
        //add weapon if we dont have it
        if (_em->Get<Weaponset>(other)->weapons.size() < 3) {
            _em->Get<Weaponset>(other)->weapons.push_back(_em->Get<Loot>(powerup)->weaponLoot);
            return;
        }     
    }
}

void CollisionSystem::body_collisions(EntityID ent, EntityID other)
{
    

}

void CollisionSystem::create_explosion(Vector3 pos, std::string exploName)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::EXPLOSION});
    _em->Assign<Owner>(id, Owner{id, RL::ModelType::EXPLOSION});
    _em->Assign<IsAlive>(id, IsAlive{true});
    _em->Assign<ModelName>(id, ModelName{exploName,exploName});
    _em->Assign<ModelScale>(id, ModelScale{_assetManager->getSpecificDrawableWithType(exploName, RL::ModelType::EXPLOSION)->getScale()});
    _em->Assign<Position>(id, Position{pos});
    _em->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _em->Assign<AnimationData>(id, AnimationData{0, 0});
    std::cout << "creating explosion" << std::endl;
}
