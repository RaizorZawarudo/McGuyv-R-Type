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

//to do : the randomness of lootm from a seed sent by server SIR
void LootSystem::update(std::vector<EntityID> &allEntities)
{
    if (_assetManager->getLootRand() % 100 > DROPRATE) // if the roll is below 15 it can loot, so basically we have a 15% drop chance
        return;
    int rand = _assetManager->getLootRand() % _assetManager->getPowerUpModels().size();
    for (EntityID ent : EntityViewer<Loot>(*_em.get())) {
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::POWERUP && _em->Get<EntityModelType>(ent)->modelType != RL::ModelType::SPACESHIP && !_em->Get<IsAlive>(ent)->alive) {
                create_loot(_em->Get<Position>(ent)->pos,  _assetManager->getPowerUpModels().at(rand)->getName());
                std::cout << "created loot :" << _assetManager->getPowerUpModels().at(rand)->getName() << std::endl;
            // if (rand < 3)
            //     create_loot(_em->Get<Position>(ent)->pos, "plasmaProj");
            // if (rand >= 3 && rand <= 5)
            //     create_loot(_em->Get<Position>(ent)->pos, "shield");
            // if (rand >= 6 && rand <= 8)
            //     create_loot(_em->Get<Position>(ent)->pos, "fireball");
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
    _em->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(lootName, RL::ModelType::POWERUP)->getWidth(),
                                                                _assetManager->getSpecificDrawableWithType(lootName, RL::ModelType::POWERUP)->getHeight(),
                                                                _assetManager->getSpecificDrawableWithType(lootName, RL::ModelType::POWERUP)->getLength()});
    _em->Assign<Collider>(id, Collider{BoundingBox{}});
    _em->Assign<Velocity>(id, Velocity{0.0f, 0.0f, 0.1f});
    _em->Assign<Timer>(id, Timer{GetTime(), 12});
    if (_assetManager->getSpecificDrawableWithType(lootName, RL::ModelType::POWERUP)->getStyle() == "projectile") {
        _em->Assign<Loot>(id, Loot{true,generateWeaponLoot(lootName), Shield{20, false}});
        _em->Assign<PowerUpType>(id, PowerUpType{PowerUpEnum::WEAPONPOWER});
    }
    if (_assetManager->getSpecificDrawableWithType(lootName, RL::ModelType::POWERUP)->getStyle() == "shield") {
        _em->Assign<Shield>(id, generateShieldLoot());
        _em->Assign<PowerUpType>(id, PowerUpType{PowerUpEnum::SHIELDPOWER});
    }
}

ProjectileWeapon LootSystem::generateWeaponLoot(std::string projectileName)
{
    ProjectileWeapon BaseWeapon;
    Vector3 Vel;
    BaseWeapon.name = projectileName;
    BaseWeapon.modelName = projectileName;
    BaseWeapon.maxAmmo = 999; // max amom is 999
    BaseWeapon.curAmmo = 100; // set ammo per loot to 50? 
    BaseWeapon.splash = 0.0f; //TODO : add in projectile CSV and in drawable 3d class and constructor and in asset manager loadProjectiles models
    BaseWeapon.range = 50.0f; // TODO: same as above
    BaseWeapon.cooldowninseconds = _assetManager->getSpecificDrawableWithType(BaseWeapon.modelName, RL::ModelType::PROJECTILE)->getShootCD();
    BaseWeapon.damage = _assetManager->getSpecificDrawableWithType(BaseWeapon.modelName, RL::ModelType::PROJECTILE)->getHp();
    Vel = _assetManager->getSpecificDrawableWithType(BaseWeapon.modelName, RL::ModelType::PROJECTILE)->getVelocity();
    BaseWeapon.vel = {Vel.x, Vel.y, Vel.z};
    BaseWeapon.lasttimeweaponwasshot = 0;

    return BaseWeapon;
}

Shield LootSystem::generateShieldLoot()
{
    Shield ShieldLoot;

    ShieldLoot.shield = 20;
    ShieldLoot.shieldActive = false;
    return ShieldLoot;
}