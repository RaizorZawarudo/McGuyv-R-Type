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
                // powerUp_collisons(ent, other);
                // body_collisions(ent, other);
            }
        }
    }
}

void CollisionSystem::bullet_collisions(EntityID projectile, EntityID other)
{
    if (_em->Get<EntityModelType>(projectile)->modelType != RL::ModelType::PROJECTILE)
        return;
    // Position* projectilePos = _em->Get<Position>(projectile);
    // Position* otherPos = _em->Get<Position>(other);
    Collider* projectileCollider = _em->Get<Collider>(projectile);
    Collider* otherCollider = _em->Get<Collider>(other);
    if (CheckCollisionBoxes(projectileCollider->collider, otherCollider->collider)) {
        std::cout << _em->Get<ModelName>(projectile)->modelname << " collided with" << _em->Get<ModelName>(other)->modelname << std::endl;
        //create bullet impact (another explosion) entity with the path stored in the projectile´s components ==> createExplosion(_em->Get<ExplosionName>)(projectile)->name); this one has to be super small preferably except for badabig weapons

        //set bullet to dead
        _em->Get<IsAlive>(projectile)->alive = false;
        //reduce other hp by bullet damage
        _em->Get<Hp>(other)->hp -= _em->Get<Hp>(projectile)->hp;
        // give points to owner


        if (_em->Get<Hp>(other)->hp <= 0) {
            _em->Get<IsAlive>(other)->alive = false;
            Position* projectilePos = _em->Get<Position>(projectile);
            ModelName* otherName = _em->Get<ModelName>(other);
            create_explosion(projectilePos->pos, otherName->explosionname);
        }

        //check if other hp is below zero : if yes set it to dead and create an explosion entity with the explosion path stored in the other´s components ==>  createExplosion(_em->Get<ExplosionName>(other)->name);
        // Position* projectilePos = _em->Get<Position>(projectile);
        // ModelName* otherName = _em->Get<ModelName>(other);
        // create_explosion(projectilePos->pos, otherName->explosionname); //here should be create bullet impact but we test explosion
    }
}

void CollisionSystem::powerUp_collisons(EntityID ent, EntityID other)
{

}

void CollisionSystem::body_collisions(EntityID ent, EntityID other)
{

}

void CollisionSystem::create_explosion(Vector3 pos, std::string exploName)
{
    std::cout << "should explode with this animation : " << exploName << " at this position " << pos.y << " " << pos.y << " " << pos.z << std::endl;

    EntityID id = _em->CreateNewEntity();
    _em->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::EXPLOSION});
    _em->Assign<Owner>(id, Owner{id, RL::ModelType::EXPLOSION});
    _em->Assign<IsAlive>(id, IsAlive{true});
    _em->Assign<ModelName>(id, ModelName{exploName,exploName});
    _em->Assign<ModelScale>(id, ModelScale{_assetManager->getSpecificDrawableWithType(exploName, RL::ModelType::EXPLOSION)->getScale()});
    _em->Assign<Position>(id, Position{pos});
    _em->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _em->Assign<AnimationData>(id, AnimationData{0, 0});
}
