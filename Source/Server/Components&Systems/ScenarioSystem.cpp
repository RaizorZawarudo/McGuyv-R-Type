/*
** EPITECH PROJECT, 2023
** MCGUYVER-TYPE_EPITECH
** File description:
** ScenarioSystem
*/

#include "ScenarioSystem.hpp"

ScenarioSystem::ScenarioSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager) : _assetManager(assetManager)
{
    _wavetimer =_assetManager->getStartTimestamp();
    _em = em;
}

ScenarioSystem::~ScenarioSystem()
{
}

void ScenarioSystem::update(std::vector<EntityID> &allEntities)
{
    std::string foregroundsectionName;
    Map* currentMap = _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed());

    if (currentMap->getCurrentWave() == currentMap->getWaveAmountsVector().at(currentMap->getCurrentStage())) {
        if (currentMap->getIsFightingBoss() == false) {
            std::cout << "WE GET IN THE LOOP" << std::endl;
            currentMap->setFightingBossTrue();
        }
    }

    //spawn the boss in the bossrom at the correct position
    if (currentMap->getIsFightingBoss() == true) {
        for (int i = 0; i < currentMap->getMapQueue().size(); i++) {
            if (currentMap->getMapQueue().at(i)._isBossRoom && currentMap->getMapQueue().at(i)._zPosition <= MAXPOSSIBLEZ - 40 && currentMap->getHasSpawnedBossRoom() == true && currentMap->getHasSpawnedBoss() == false) {
                createEnnemy(currentMap->getBossRoomBossName().at(currentMap->getCurrentStage()), (Vector3){0 ,4 ,currentMap->getMapQueue().at(i)._zPosition + 30});
                std::cout << "spawning boss : " << currentMap->getBossRoomBossName().at(currentMap->getCurrentStage()) << std::endl;
                currentMap->setSpawnedBoss();
            }
        }
    }
    
    std::chrono::duration<float> diff = std::chrono::system_clock::now() - _wavetimer;
    if (_assetManager->getRacerMode()) {
        int rand = std::rand() % (_assetManager->getObstacleWaves().size());
        std::string waveName = _assetManager->getObstacleWaves().at(rand).name;
        if (diff.count() > _wavedelay) {
            if (_wavedelay > 0.5)
                _wavedelay -= 0.025;
            std::cout << "wave name = " << waveName << std::endl;
            createObstacleWave(waveName);
            _wavetimer = std::chrono::system_clock::now();
        }
    }
    if (!_assetManager->getRacerMode() && diff.count() > 3 && currentMap->getIsFightingBoss() == false && currentMap->getMapQueue().at(0)._isBossRoom == false ) {
        std::cout << "Spawning wave" << std::endl;
        int waveIndextoSpawn = _assetManager->getLootRand() % currentMap->getRepeathPathWaves()[currentMap->getCurrentStage()].size();
        std::cout << currentMap->getRepeathPathWaves()[currentMap->getCurrentStage()][waveIndextoSpawn] << std::endl;
        for (int i = 0; i < _assetManager->getScenarios().size(); i++) {
            if (currentMap->getMapName() == _assetManager->getScenarios().at(i).scenarioName) {
                std::cout << "MATCH BETWEEN MAP AND SCENARIOS" << std::endl;
                //now loop within the waves of the scenario and if the type is obstacle create obstacle, if the type is enemy create enemy
                for (int y = 0; y < _assetManager->getScenarios().at(i).waveNames.size(); y++) {
                    if (currentMap->getRepeathPathWaves()[currentMap->getCurrentStage()][waveIndextoSpawn] == _assetManager->getScenarios().at(i).waveNames[y]) {
                        std::cout << "MATCHED THE WAVE FOUND IN MAPS WITH THE WAVE FOUND IN SCENARIOS OF THE MAP" << std::endl;
                        if (_assetManager->getScenarios().at(i).waveTypes[y] == "obstaclewave") {
                            createObstacleWave(currentMap->getRepeathPathWaves()[currentMap->getCurrentStage()][waveIndextoSpawn]);
                            break;
                        }
                        if (_assetManager->getScenarios().at(i).waveTypes[y] == "ennemywave") {
                            createEnnemyWave(currentMap->getRepeathPathWaves()[currentMap->getCurrentStage()][waveIndextoSpawn]);
                            std::cout << "CREATE the createEnnemyWave FUCNTION BRO AND COPY PASTA CREATE ENNEMY IN SCENARIO.CPP" << std::endl;
                            break;
                        }
                    }
                }
            }
        }
        //DEBUG END            
        _wavetimer = std::chrono::system_clock::now();
        currentMap->setCurrentWavePlusOne();
        std::cout << currentMap->getCurrentWave() << std::endl;         
    }
}

void ScenarioSystem::createObstacleWave(std::string waveName)
{
    for (int i = 0; i < _assetManager->getObstacleWaves().size(); i++) {
        if (waveName == _assetManager->getObstacleWaves()[i].name) {
            std::cout << "WE found the wave : " << waveName << std::endl;
            for (int j = 0; j < _assetManager->getObstacleWaves()[i].waveComponents.size(); j++) {
                // std::cout << waveName << " has this obstacle : " << _assetManager->getObstacleWaves()[i].waveComponents[j].codename << std::endl;
                createObstacle(_assetManager->getObstacleWaves()[i].waveComponents[j].codename, (Vector3){_assetManager->getObstacleWaves()[i].waveComponents[j].position.x ,_assetManager->getObstacleWaves()[i].waveComponents[j].position.y ,MAXPOSSIBLEZ -1});
            }
        }        
    }
}

void ScenarioSystem::createEnnemyWave(std::string waveName)
{
    for (int i = 0; i < _assetManager->getEnnemyWaves().size(); i++) {
        if (waveName == _assetManager->getEnnemyWaves()[i].name) {
            std::cout << "WE found the wave : " << waveName << std::endl;
            for (int j = 0; j < _assetManager->getEnnemyWaves()[i].waveComponents.size(); j++) {
                // std::cout << waveName << " has this Ennemy : " << _assetManager->getEnnemyWaves()[i].waveComponents[j].codename << std::endl;
                createEnnemy(_assetManager->getEnnemyWaves()[i].waveComponents[j].codename, (Vector3){_assetManager->getEnnemyWaves()[i].waveComponents[j].position.x ,_assetManager->getEnnemyWaves()[i].waveComponents[j].position.y ,MAXPOSSIBLEZ -1});
            }
        }        
    }
}

void ScenarioSystem::createObstacle(std::string modelName, Vector3 position)
{
    EntityID id = _em->CreateNewEntity(); // this causes the segfault, check when i delete entities that i do it properly
    float scrollspeed;

    _em->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::OBSTACLE});
    _em->Assign<Owner>(id, Owner{100000, RL::ModelType::ENNEMY}); //HERE THE VALUE 100000 SHOULD BE THE ID OF THE SERVER NOW SINCE WE MAKE THE GAME IN SERVER
    _em->Assign<Loot>(id, Loot{true});
    _em->Assign<ModelName>(id, ModelName{modelName, _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getExplosionName()});
    _em->Assign<ModelScale>(id, ModelScale{1.0f});
    _em->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getWidth(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getHeight(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getLength()});
    _em->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _em->Assign<Collider>(id, Collider{BoundingBox{}});
    _em->Assign<IsAlive>(id, IsAlive{true});
    _em->Assign<Position>(id, Position{position});
    scrollspeed = _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->getScrollSpeed();
    _em->Assign<Velocity>(id, Velocity{scrollspeed, scrollspeed, scrollspeed});
    _em->Assign<Hp>(id, Hp{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getHp()});
    _em->Assign<HasUpdated>(id, HasUpdated{true});
}

void ScenarioSystem::createEnnemy(std::string modelName, Vector3 ennemyPos) // here we will add base weapon choice, avatar choice as well chosen by user in menu, the avatar is just cosmetic
{
    EntityID id = _em->CreateNewEntity();
    //register this entity as the player for this client
    std::vector<int> ennemyInput;
    Vector3 Vel;
    
    float scrollspeed;
    _em->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::ENNEMY});
    
    _em->Assign<Owner>(id, Owner{100000, RL::ModelType::ENNEMY}); //here we use 100000 but its the id of the server same as before
    
    _em->Assign<IsAlive>(id, IsAlive{true});    
    
    _em->Assign<ModelName>(id, ModelName{modelName, _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getExplosionName()});
    _em->Assign<ModelScale>(id, ModelScale{1.0f});

    _em->Assign<Loot>(id, Loot{true});   
    
    _em->Assign<Position>(id,Position{ennemyPos});
    
    _em->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _em->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getWidth(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getHeight(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getLength()});
    _em->Assign<Collider>(id, Collider{BoundingBox{}});
    
    scrollspeed = _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->getCurrentSpeed();
    _em->Assign<Velocity>(id, Velocity{scrollspeed, scrollspeed, scrollspeed});
    _em->Assign<Hp>(id, Hp{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getHp()});
    // _em->Assign<AI>(id, AI{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getStyle()});
    _em->Assign<AI>(id, assignAI(_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getStyle(), id));
    _em->Assign<Input>(id, Input{ennemyInput});
    _em->Assign<Shield>(id, Shield{100});
    //add weaponset to mobs so that they can pickup weapons
    _em->Assign<Weaponset>(id, Weaponset{generateStartWeaponsetEnnemies("fireball"), 0}); //add this to ennemies CSV and update asset manager to reflect weaponset name in the drawable3D


    //try to add animations to bosses only
    _em->Assign<AnimationData>(id, AnimationData{0, 0});
    if (_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getStyle() == "boss")
        _em->Assign<EnnemyAnim>(id, EnnemyAnim{true});
    else
        _em->Assign<EnnemyAnim>(id, EnnemyAnim{false});
    _em->Assign<HasUpdated>(id, HasUpdated{true});
}

std::vector<ProjectileWeapon> ScenarioSystem::generateStartWeaponsetEnnemies(std::string modelName)
{
    std::vector<ProjectileWeapon> startWeaponset;

    ProjectileWeapon BaseWeapon;
    Vector3 Vel;

    BaseWeapon.name = modelName;
    BaseWeapon.modelName = modelName;
    BaseWeapon.maxAmmo = -999; // unlimitted ammo stock
    BaseWeapon.curAmmo = -999; // unlimitted ammo, both the -999 are for unlimited should define it later
    BaseWeapon.splash = 0.0f; //TODO : add in projectile CSV and in drawable 3d class and constructor and in asset manager loadProjectiles models
    BaseWeapon.range = 50.0f; // TODO: same as above
    BaseWeapon.cooldowninseconds = _assetManager->getSpecificDrawableWithType(BaseWeapon.modelName, RL::ModelType::PROJECTILE)->getShootCD();
    BaseWeapon.damage = _assetManager->getSpecificDrawableWithType(BaseWeapon.modelName, RL::ModelType::PROJECTILE)->getHp();
    Vel = _assetManager->getSpecificDrawableWithType(BaseWeapon.modelName, RL::ModelType::PROJECTILE)->getVelocity();
    BaseWeapon.vel = {Vel.x, Vel.y, Vel.z};
    BaseWeapon.lasttimeweaponwasshot = _assetManager->getStartTimestamp();
    startWeaponset.push_back(BaseWeapon);
    return startWeaponset;
}

AI ScenarioSystem::assignAI(std::string AIType, EntityID ennemy)
{
    if (AIType == "simple")
        return assignSimpleAI(AIType, ennemy);
    // if (AIType == "anythingelse")
    //     return assignSimpleAI(AIType, ennemy);
    if (AIType == "boss")
        return assignSimpleAI(AIType, ennemy); //here add AI of specific boss also
    
    //else
    //  return a simpleaie
}

AI ScenarioSystem::assignSimpleAI(std::string AIType, EntityID ennemy)
{
    AI newAI;

    newAI.style = AIType;
    newAI.isMoving = false;
    newAI.moveCooldown = SIMPLEAIMOVECOOLDOWN;
    newAI.lastTimeMoved = _assetManager->getStartTimestamp();
    newAI.moveDetectRange = SIMPLEAIMOVEDETECTRANGE;
    newAI.targetPlayerDetectRange = SIMPLEAITARGETPLAYERDETECTRANGE;
    newAI.moveRange = SIMPLEMOVERANGE;
    newAI.moveTargetPos = {0,0,0};

    newAI.hasShot = false;
    newAI.lastTimeShot = _assetManager->getStartTimestamp();
    newAI.shootCooldown = SIMPLEAISHOOTCOOLDOWN;
    newAI.shootDetectRange = SIMPLEAISHOOTDETECTRANGE;

    return newAI;
}
