/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** McGuyverType
*/

#include "McGuyverType.hpp"

//nothing 
McGuyverType::McGuyverType()
{
    this->_udpClient = std::make_shared<UDPClient>(this->_ioContext);
    _udpClientThread = std::thread(&McGuyverType::udpClientThreadFunction, this); 
    
    this->_window  = std::make_shared<RL::Window>("McGuyv R-Type");
    this->_cameraManager = std::make_shared<RL::CameraManager>();
    this->_soundManager = std::make_shared<RL::SoundManager>();
    this->_assetManager = std::make_shared<AssetManager>(this->_thisClientPlayerEntityID);
    this->_renderer = std::make_shared<RL::Renderer>("Renderer");
    this->_inputManager = std::make_shared<RL::InputManager>("InputManager");
    this->_menuManager = std::make_shared<RL::MenuManager>(_window, _cameraManager, _assetManager, _renderer, _inputManager, _soundManager, _udpClient);
    this->_entityManager = std::make_shared<EntityManager>();
    this->_assetManager->startTime();

    this->_systems.push_back(std::make_shared<DataReceivingSystem>(this->_entityManager, this->_assetManager, this->_inputManager, this->_menuManager, this->_udpClient)); //add deserialiser and upd reader

    this->_systems.push_back(std::make_shared<MovementSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<DeleteEntitiesSystem>(this->_entityManager, this->_assetManager));
    this->_systems.push_back(std::make_shared<DrawingSystem>(this->_entityManager, this->_renderer, this->_assetManager, this->_cameraManager, this->_window)); // client side only
    this->_systems.push_back(std::make_shared<ClearInputsSystem>(this->_entityManager, this->_inputManager));
    this->_systems.push_back(std::make_shared<InputSystem>(this->_entityManager, this->_inputManager, this->_thisClientPlayerEntityID)); //add serialiser and udp writer to this system


    // here we resize all the maps to be the dimension of the window
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
    _udpClientThread.join();
//     _ioContext.stop();
//     std::cout << "McGuyverType destructor called" << std::endl;
}

void McGuyverType::udpClientThreadFunction() {
    while(!_isEnd.load(std::memory_order_relaxed)) {
        _udpClient->receive();
    }
}

void McGuyverType::startGame() // must have player choices etc WITH CURRENLEVEL AS THE WORLD THEY CHOSE IN SCREEN SELECT MENU
{
    bool isInMenu = true;
    _soundManager->playSpecificMusic("DaveEast");
    _soundManager->enableDisableShuffle();




    
    SetTargetFPS(60);

    while (_window->isWindowOpen()) {
        _soundManager->updateMusicStream();
        //UI LOOP functions
        if (_menuManager->getCurScreen() == QUITGAME) {
            // _window->close();
            break;
        }
        if (isInMenu) {
            isInMenu = _menuManager->drawMenu();
        }
        if (_menuManager->getCurScreen() == TIMETOPLAY) {
                _currentLevel = _menuManager->getMapSelectIndex();
                _assetManager->setCurrentMapBeingPlayed(_currentLevel);
                if (_menuManager->getRacerMode())
                    _assetManager->setRacerMode();
                // createPlayer("dartAssault", _menuManager->getCharacterName()); //add clientID in player constructor so it can be found for multiplayer in the server etc etc

        }
        if (!isInMenu) {
            if (_assetManager->getMaps().at(_currentLevel)->getGameRunning() == false) {
                _assetManager->getMaps().at(_currentLevel)->setGameRunning(); // current level to be modified my ui choices
            }
            gameLoop(); //might take more arguments to refelct player choice of map and choice of character
        }
    }
    _window->close();    //clear everything in entities
    _isEnd.store(true, std::memory_order_relaxed);
    std::cout << _isEnd.load(std::memory_order_relaxed) << std::endl;
    for (EntityID _ent:  EntityViewer<>(*_entityManager.get()) ) {
        std::cout << "destroying entity : " << _ent << std::endl;
        _entityManager->DestroyEntity(_ent);
    }
    //clear everything in asset manager maannnn
}

void McGuyverType::gameLoop()
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    // here we need to check with clients if new people connect in order to create new player entities with their spaceship choice

    _assetManager->getMaps().at(_currentLevel)->mapUpdate();

    _cameraManager->changeCameraPosition(_assetManager->getSpecificDrawableWithType(_assetManager->getMaps().at(_currentLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));


    //do all checks if needed ( pause game, open whatefver menu, communicated with whatever process)
    //here we imagine we recive data from the server setting us the rand, to add into a system to communicate with server

    //here we loop through all our systems to update them
    for( std::shared_ptr<ISystem> system : _systems) {
        system->update(this->_allEntities);
    }

    //then if game ends or somethings
    //then finish
}



//getters

std::shared_ptr <EntityManager> McGuyverType::getEm()
{
    return _entityManager;
}


