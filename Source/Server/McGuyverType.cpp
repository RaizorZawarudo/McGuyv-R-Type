/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** McGuyverType
*/

#include "McGuyverType.hpp"

void McGuyverType::threadIoContext() {
    _ioContext.run();
}

McGuyverType::McGuyverType()
{
    this->_udpServer = std::make_shared<UDPServer>(_ioContext);
    _serverThread = std::thread(&McGuyverType::threadIoContext, this);
    // this->_window  = std::make_shared<RL::Window>("McGuyv R-Type");
    // this->_cameraManager = std::make_shared<RL::CameraManager>();
    this->_assetManager = std::make_shared<AssetManager>(this->_thisClientPlayerEntityID);
    // this->_renderer = std::make_shared<RL::Renderer>("Renderer");
    this->_inputManager = std::make_shared<RL::InputManager>("InputManager");
    this->_entityManager = std::make_shared<EntityManager>();
    this->_assetManager->startTime();

    //this is the scenario system


    this->_systems.push_back(std::make_shared<InputSystem>(this->_entityManager, this->_inputManager, this->_thisClientPlayerEntityID));
    this->_systems.push_back(std::make_shared<ScenarioSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<BotSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<ShootingSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<MovementSystem>(this->_entityManager, this->_assetManager)); // this sets the bounding boxes so it must come as the last system before collisions 
    //add collision system
    this->_systems.push_back(std::make_shared<CollisionSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<LootSystem>(this->_entityManager, this->_assetManager));
    //add ui update system (ui buttons ui keypresses to stop game etc etc)
    this->_systems.push_back(std::make_shared<ClearInputsSystem>(this->_entityManager, this->_inputManager));
    this->_systems.push_back(std::make_shared<HasUpdatedSystem>(this->_entityManager, this->_udpServer, this->_assetManager));
    this->_systems.push_back(std::make_shared<DeleteEntitiesSystem>(this->_entityManager, this->_assetManager));
    // read entities, serialize and send data to the client
    // this->_systems.push_back(std::make_shared<DrawingSystem>(this->_entityManager, this->_renderer, this->_assetManager, this->_cameraManager, this->_window)); // client side only
    // read client inputs, serialize and send data to the server

    //here we resize all the maps to be the dimension of the window
    // for (Map* map: this->_assetManager->getMaps())
    //     _assetManager->getSpecificBackground(map->getBackgroundName())->resize(_window->getDimensions());
    // for (RL::Drawable2D* icon: this->_assetManager->getUIelements()) {
    //     if (icon->getType() == "player") {
    //         icon->resize(Vector2{_window->getDimensions().x * 7.8f / 100,_window->getDimensions().y * 10.4f / 100 });
    //     }
    //     else if (icon->getType() == "bottomPannel") {
    //         icon->resize(Vector2{_window->getDimensions().x * 31.25f / 100,_window->getDimensions().y * 15.62f / 100 });
    //     }
    //     else if (icon->getType() == "power") {
    //         icon->resize(Vector2{_window->getDimensions().x * 7.8f / 100 / 2,_window->getDimensions().y * 10.4f / 100 / 2 });
    //     }
    // }
}

McGuyverType::~McGuyverType()
{
    _ioContext.stop();
    _serverThread.join();
    std::cout << "McGuyverType destructor called" << std::endl;
}

void McGuyverType::startGame() // must have player choices etc
{
    char *data = nullptr;

    while (!_assetManager->getMaps().at(_currentLevel)->getGameRunning()) {
        std::vector<boost::array<char, 1024UL>> packets = _udpServer->getMessages();
        for (auto packet : packets) {
            Msg msg = _serializator.bytesToStruct(packet.data());
            switch(msg.getstatus()) {
                case serializator::Header::startGame:
                    _assetManager->getMaps().at(_currentLevel)->setGameRunning();
                    data = _serializator.createPackageStartGame(serializator::Header::startGame, true);
                    _udpServer->send(data, SIZE_STATE_GAME);
                    break;
                case serializator::Header::canSelect:
                    _currentLevel = msg.getMapIndex();
                    if (msg.getRacerMode())
                        _assetManager->setRacerMode();
                    data = _serializator.createPackageCanSelect(serializator::Header::canSelect, _currentLevel, msg.getRacerMode());
                    _udpServer->send(data, SIZE_CAN_SELECT);
                    break;
                case serializator::Header::spaceShipSelection:
                    // std::cout << "spaceShipSelection " << msg.setModelIndex() << std::endl;
                    std::cout << "spaceShipSelection " << msg.getClientHash() << "  " << msg.getSpaceShipIndex() << std::endl;
                    createPlayer(_assetManager->getSpacecraftModels().at(msg.getSpaceShipIndex())->getName(), msg.getClientHash());
                    break;
            }
        }
    }   // send start packet to client
    delete data;
    // SetTargetFPS(60);
    
    //HERE WE CREATE PLAYERS, assume player chose the DartAssault spaceship for testing
    

    
    //this order or setting level then creating entities then setting game to play is necessary for no seggy


    _assetManager->setCurrentMapBeingPlayed(_currentLevel);
    // _assetManager->setRacerMode();

    // while (_window->isWindowOpen()) {

    while (true) {
        //UI LOOP functions
        gameLoop(); //might take more arguments to refelct player choice of map and choice of character
    }

    
    // _window->close();

    //clear everything in entities
    for (EntityID _ent:  EntityViewer<>(*_entityManager.get()) ) {
        std::cout << "destroying entity : " << _ent << std::endl;
        _entityManager->DestroyEntity(_ent);
    }
    //clear everything in asset manager maannnn

}

void McGuyverType::gameLoop()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    // here we need to check with clients if new people connect in order to create new player entities with their spaceship choice

    _assetManager->getMaps().at(_currentLevel)->mapUpdate();
    // _cameraManager->changeCameraPosition(_assetManager->getSpecificDrawableWithType(_assetManager->getMaps().at(_currentLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));
    //do all checks if needed ( pause game, open whatefver menu, communicated with whatever process)
    
    // lock message qu the server setting us the rand, to add into a system to communicate with server

    _assetManager->setLootRand(std::rand());
    // if (_assetManager->getRacerMode()) {
    //     if (GetTime() - _racerTimer > 3) {
    //         _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->setMapSpeed(0.05);
    //         _racerTimer = GetTime();
    //         std::cout << "speedin' up" << std::endl;
    //     }

    // }
    //here we loop through all our systems to update them
    for (std::shared_ptr<ISystem> system : _systems) {
        system->update(this->_allEntities);
        // std::cout << "SIZE OF _ALLENTITIES   " << this->_allEntities.size() << std::endl;
        // lock message queue in the thread using mutex
        // Add message to the queue
        // get entities and send them
    }
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
    BaseWeapon.lasttimeweaponwasshot = std::chrono::system_clock::now();

    startWeaponset.push_back(BaseWeapon);
    return startWeaponset;
}

void addWeapon()
{

}

void McGuyverType::createPlayer(std::string modelName, unsigned long long clientId) // here we will add base weapon choice, avatar choice as well chosen by user in menu, the avatar is just cosmetic
{
    EntityID id = _entityManager->CreateNewEntity();
    //register this entity as the player for this client
    std::vector<int> playerInput;
    Vector3 Vel;

    _entityManager->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::SPACESHIP});
    _entityManager->Assign<Owner>(id, Owner{clientId, RL::ModelType::MCGUYVER});
    std::cout << "OWNER ID CREATE PLAYER " << id << " with Owner " << clientId << std::endl;

    _entityManager->Assign<UIAvatarNames>(id, UIAvatarNames{modelName});
    
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
    _entityManager->Assign<HasUpdated>(id, HasUpdated{true});
}

//getters

std::shared_ptr <EntityManager> McGuyverType::getEm()
{
    return _entityManager;
}


