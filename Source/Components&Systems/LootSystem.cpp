/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** LootSystem
*/

#include "LootSystem.hpp"

LootSystem::LootSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager) : _assetManager(assetManager)
{
    _em = em;
}

LootSystem::~LootSystem()
{
}

void LootSystem::update(std::vector<EntityID> &allEntities)
{
    int rand = std::rand() % 10;
    for (EntityID ent : EntityViewer<Loot>(*_em.get())) {
        if (!_em->Get<IsAlive>(ent)->alive) {
            if (rand > 8)
                create_loot(_em->Get<Position>(ent)->pos, "missileProj");
            if (rand < 3)
                create_loot(_em->Get<Position>(ent)->pos, "plasmaProj");
            if (rand >= 3 && rand <= 5)
                create_loot(_em->Get<Position>(ent)->pos, "orangeLight");
            if (rand >= 6 && rand <= 8)
                create_loot(_em->Get<Position>(ent)->pos, "fireball");
        }
    }

}

void LootSystem::create_loot(Vector3 pos, std::string lootName)
{
    EntityID id = _em->CreateNewEntity();
    _em->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::POWERUP});
    _em->Assign<Owner>(id, Owner{id, RL::ModelType::MCGUYVER});
    _em->Assign<IsAlive>(id, IsAlive{true});
    _em->Assign<ModelName>(id, ModelName{lootName,lootName});
    _em->Assign<ModelScale>(id, ModelScale{_assetManager->getSpecificDrawableWithType(lootName, RL::ModelType::POWERUP)->getScale()});
    _em->Assign<Position>(id, Position{pos});
    _em->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _em->Assign<Collider>(id, Collider{BoundingBox{}});
    _em->Assign<Velocity>(id, Velocity{0.0f, 0.0f, 0.0f});
    _em->Assign<Timer>(id, Timer{GetTime(), 12});
    // if ( asset manager Get drawable name ->get type == shield)
        //add shield component
    // iftpye == projectile 
        //add projectileweapon componnennt with these data : maxAmmo 999 ; curAmmo 200; make distinction if player already has the weapon or not.
    std::cout << "creating LOOT" << std::endl;

}