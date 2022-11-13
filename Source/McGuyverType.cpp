/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** McGuyverType
*/

#include "McGuyverType.hpp"

McGuyverType::McGuyverType()
{
    this->_window  = std::make_shared<RL::Window>("McGuyv R-Type");
    this->_cameraManager = std::make_shared<RL::CameraManager>();
    this->_assetManager = std::make_shared<AssetManager>(this->_thisClientPlayerEntityID);
    this->_renderer = std::make_shared<RL::Renderer>("Renderer");
    this->_inputManager = std::make_shared<RL::InputManager>("InputManager");
    this->_entityManager = std::make_shared<EntityManager>();


    this->_systems.push_back(std::make_shared<InputSystem>(this->_entityManager, this->_inputManager, this->_thisClientPlayerEntityID));
    this->_systems.push_back(std::make_shared<BotSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<ShootingSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<MovementSystem>(this->_entityManager)); //this sets the bounding boxes so it must come as the last system before collisions 
    //add collision system
    this->_systems.push_back(std::make_shared<CollisionSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<LootSystem>(this->_entityManager, this->_assetManager));
    //add ui update system (ui buttons ui keypresses to stop game etc etc)
    this->_systems.push_back(std::make_shared<ClearInputsSystem>(this->_entityManager, this->_inputManager));
    this->_systems.push_back(std::make_shared<DeleteEntitiesSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<DrawingSystem>(this->_entityManager, this->_renderer, this->_assetManager, this->_cameraManager, this->_window));

    //here we resize all the maps to be the dimension of the window
    for (Map* map: this->_assetManager->getMaps())
        _assetManager->getSpecificBackground(map->getBackgroundName())->resize(_window->getDimensions());
    for (RL::Drawable2D* icon: this->_assetManager->getUIelements()) {
        if (icon->getType() == "player") {
            icon->resize(Vector2{_window->getDimensions().x * 7.8f / 100,_window->getDimensions().y * 10.4f / 100 });
        }
        else if (icon->getType() == "bottomPannel") {
            icon->resize(Vector2{_window->getDimensions().x * 31.25f / 100,_window->getDimensions().y * 15.62f / 100 });
        }
        else if (icon->getType() == "power") {
            icon->resize(Vector2{_window->getDimensions().x * 7.8f / 100 / 2,_window->getDimensions().y * 10.4f / 100 / 2 });
        }
    }
}

McGuyverType::~McGuyverType()
{
}

void McGuyverType::startGame() // must have player choices etc
{
    SetTargetFPS(60);
    
    
    //HERE WE CREATE PLAYERS, assume player chose the DartAssault spaceship for testing
    

    
    //this order or setting level then creating entities then setting game to play is necessary for no seggy


    _assetManager->setCurrentMapBeingPlayed(_currentLevel);


    createPlayer("dartAssault", "malibuPepe"); //add clientID in player constructor so it can be found for multiplayer in the server etc etc
    createEnnemy("tronDrone", _ennemyStartingPos.pos);
    createEnnemy("tronDrone", _ennemyStartingPos2.pos);
    
    
    _assetManager->getMaps().at(_currentLevel)->setGameRunning(); // current level to be modified my ui choices


    //MOCK OBSTACLE CREATION TO BE DELETED
    float x;
    float y;
    double lastshot= 0;
    bool shootingstaractive = false;
    //END MOCK

    while (_window->isWindowOpen()) {
        //UI LOOP functions
        gameLoop(); //might take more arguments to refelct player choice of map and choice of character

        
        // MOCK SPAWN OF OBSTACLES FOR TESTING TO DELETE !!
        if (GetTime() - lastshot > 2) {
            y = std::rand() % 9;
            x = std::rand() % 7;
            if ( std::rand() % 2 == 0)
                x *= -1;
            if (y < 1.5)
                y = 1.5f;
            createObstacle("cube1Blue",(Vector3){x, y, MAXPOSSIBLEZ -1});
            lastshot = GetTime();            
        }
        //END MOCK
    }

    
    _window->close();

    //clear everything in entities
    for (EntityID _ent:  EntityViewer<>(*_entityManager.get()) ) {
        std::cout << "destroying entity : " << _ent << std::endl;
        _entityManager->DestroyEntity(_ent);
    }
    //clear everything in asset manager maannnn

}

void McGuyverType::gameLoop()
{
    // here we need to check with clients if new people connect in order to create new player entities with their spaceship choice

    _assetManager->getMaps().at(_currentLevel)->mapUpdate();
    _cameraManager->changeCameraPosition(_assetManager->getSpecificDrawableWithType(_assetManager->getMaps().at(_currentLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));
    //do all checks if needed ( pause game, open whatefver menu, communicated with whatever process)


    //here we imagine we recive data from the server setting us the rand, to add into a system to communicate with server

    _assetManager->setLootRand(std::rand());
    
    //here we loop through all our systems to update them
    for( std::shared_ptr<ISystem> system : _systems)
        system->update(this->_allEntities);
    

    

                    
    //then if game ends or somethings
    //then finish

    
}

std::vector<ProjectileWeapon> McGuyverType::generateStartWeaponset(std::string modelName)
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
    BaseWeapon.lasttimeweaponwasshot = 0;

    startWeaponset.push_back(BaseWeapon);
    return startWeaponset;
}

void addWeapon()
{

}

void McGuyverType::createEnnemy(std::string modelName, Vector3 ennemyPos) // here we will add base weapon choice, avatar choice as well chosen by user in menu, the avatar is just cosmetic
{
    EntityID id = _entityManager->CreateNewEntity();
    //register this entity as the player for this client
    std::vector<int> ennemyInput;
    Vector3 Vel;
    
    float scrollspeed;
    _entityManager->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::ENNEMY});
    
    _entityManager->Assign<Owner>(id, Owner{this->_thisClientPlayerEntityID, RL::ModelType::ENNEMY});
    
    _entityManager->Assign<IsAlive>(id, IsAlive{true});    
    
    _entityManager->Assign<ModelName>(id, ModelName{modelName, _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getExplosionName()});
    _entityManager->Assign<ModelScale>(id, ModelScale{1.0f});

    _entityManager->Assign<Loot>(id, Loot{true});   
    
    _entityManager->Assign<Position>(id,Position{ennemyPos});
    
    _entityManager->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _entityManager->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getWidth(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getHeight(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getLength()});
    _entityManager->Assign<Collider>(id, Collider{BoundingBox{}});
    
    scrollspeed = _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->getScrollSpeed();
    _entityManager->Assign<Velocity>(id, Velocity{scrollspeed, scrollspeed, scrollspeed});
    _entityManager->Assign<Hp>(id, Hp{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getHp()});

    // _entityManager->Assign<AI>(id, AI{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getStyle()});
    _entityManager->Assign<AI>(id, assignAI(_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::ENNEMY)->getStyle(), id));
    _entityManager->Assign<Input>(id, Input{ennemyInput});
    _entityManager->Assign<Shield>(id, Shield{100});
    //add weaponset to mobs so that they can pickup weapons
    _entityManager->Assign<Weaponset>(id, Weaponset{generateStartWeaponset("fireball"), 0}); //add this to ennemies CSV and update asset manager to reflect weaponset name in the drawable3D 
}

AI McGuyverType::assignAI(std::string AIType, EntityID ennemy)
{
    if (AIType == "simple")
        return assignSimpleAI(AIType, ennemy);
    // if (AIType == "anythingelse")
    //     return assignSimpleAI(AIType, ennemy);
    
    //else
    //  return a simpleaie
}

AI McGuyverType::assignSimpleAI(std::string AIType, EntityID ennemy)
{
    AI newAI;

    newAI.style = AIType;
    newAI.isMoving = false;
    newAI.moveCooldown = SIMPLEAIMOVECOOLDOWN;
    newAI.lastTimeMoved = 0;
    newAI.moveDetectRange = SIMPLEAIMOVEDETECTRANGE;
    newAI.targetPlayerDetectRange = SIMPLEAITARGETPLAYERDETECTRANGE;
    newAI.moveRange = SIMPLEMOVERANGE;
    newAI.moveTargetPos = {0,0,0};

    newAI.hasShot = false;
    newAI.lastTimeShot = 0;
    newAI.shootCooldown = SIMPLEAISHOOTCOOLDOWN;
    newAI.shootDetectRange = SIMPLEAISHOOTDETECTRANGE;

    return newAI;
}

void McGuyverType::createPlayer(std::string modelName, std::string avatarName) // here we will add base weapon choice, avatar choice as well chosen by user in menu, the avatar is just cosmetic
{
    EntityID id = _entityManager->CreateNewEntity();
    //register this entity as the player for this client
    std::vector<int> playerInput;
    Vector3 Vel;

    _entityManager->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::SPACESHIP});
    _entityManager->Assign<Owner>(id, Owner{this->_thisClientPlayerEntityID, RL::ModelType::MCGUYVER});
    std::cout << "OWNER ID CREATE PLAYER " << _entityManager->Get<Owner>(id)->id << std::endl;

    _entityManager->Assign<UIAvatarNames>(id, UIAvatarNames{avatarName});
    
    _entityManager->Assign<ModelName>(id, ModelName{modelName,_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getExplosionName()});
    _entityManager->Assign<ModelScale>(id, ModelScale{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getScale()});
    _entityManager->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getWidth(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getHeight(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getLength()});
    _entityManager->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _entityManager->Assign<Collider>(id, Collider{BoundingBox{}});
    _entityManager->Assign<Input>(id, Input{playerInput});
    
    _entityManager->Assign<IsAlive>(id, IsAlive{true});
    _entityManager->Assign<Position>(id, _playerStartingPos);
    Vel = _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getVelocity();
    _entityManager->Assign<Velocity>(id, Velocity{Vel.x, Vel.y, Vel.z});
    _entityManager->Assign<Score>(id, Score{0});
    _entityManager->Assign<Hp>(id, Hp{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::SPACESHIP)->getHp()});
    _entityManager->Assign<Shield>(id, Shield{100});

    //here we have to assign an Arsenal ( the weapons he has), an arsenal is a struct containing a vector of 3 weapon structs
    _entityManager->Assign<Weaponset>(id, Weaponset{generateStartWeaponset("orangeLight"), 0}); //to be changed along with the constructor of this function to refelect the player choice of starting weapon
    //mock extra weapon for ui testing to delete later
}

void McGuyverType::createObstacle(std::string modelName, Vector3 position)
{
    EntityID id = _entityManager->CreateNewEntity(); // this causes the segfault, check when i delete entities that i do it properly

    float scrollspeed;
    _entityManager->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::OBSTACLE});
    _entityManager->Assign<Owner>(id, Owner{this->_thisClientPlayerEntityID, RL::ModelType::ENNEMY});

    _entityManager->Assign<Loot>(id, Loot{true});    
    
    _entityManager->Assign<ModelName>(id, ModelName{modelName, _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getExplosionName()});
    _entityManager->Assign<ModelScale>(id, ModelScale{1.0f});
    
    _entityManager->Assign<ModelDimensions>(id, ModelDimensions{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getWidth(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getHeight(),
                                                                _assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getLength()});
    _entityManager->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _entityManager->Assign<Collider>(id, Collider{BoundingBox{}});
    
    _entityManager->Assign<IsAlive>(id, IsAlive{true});
    _entityManager->Assign<Position>(id, Position{position});
    scrollspeed = _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->getScrollSpeed();
    _entityManager->Assign<Velocity>(id, Velocity{scrollspeed, scrollspeed, scrollspeed});
    _entityManager->Assign<Hp>(id, Hp{_assetManager->getSpecificDrawableWithType(modelName, RL::ModelType::OBSTACLE)->getHp()});
}


//getters

std::shared_ptr <EntityManager> McGuyverType::getEm()
{
    return _entityManager;
}


