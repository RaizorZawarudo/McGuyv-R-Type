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
    this->_assetManager = std::make_shared<AssetManager>();
    this->_renderer = std::make_shared<RL::Renderer>("Renderer");
    this->_inputManager = std::make_shared<RL::InputManager>("InputManager");
    this->_entityManager = std::make_shared<EntityManager>();


    this->_systems.push_back(std::make_shared<InputSystem>(this->_entityManager, this->_inputManager, this->_thisClientPlayerEntityID));
    this->_systems.push_back(std::make_shared<MovementSystem>(this->_entityManager));
    this->_systems.push_back(std::make_shared<ClearInputsSystem>(this->_entityManager, this->_inputManager));
    this->_systems.push_back(std::make_shared<DrawingSystem>(this->_entityManager, this->_renderer, this->_assetManager, this->_cameraManager));

    //here we resize all the maps to be the dimension of the window
    for (Map* map: this->_assetManager->getMaps())
        _assetManager->getSpecificBackground(map->getBackgroundName())->resize(_window->getDimensions());
}

McGuyverType::~McGuyverType()
{
}

void McGuyverType::startGame() // must have player choices etc
{
    SetTargetFPS(60);
    
    
    //HERE WE CREATE PLAYERS, assume player chose the DartAssault spaceship for testing
    createPlayer("dartAssault");


    _assetManager->setCurrentMapBeingPlayed(_currentLevel);
    _assetManager->getMaps().at(_currentLevel)->setGameRunning(); // current level to be modified my ui choice
    while (_window->isWindowOpen()) {
        //UI LOOP functions
        gameLoop(); //might take more arguments to refelct player choice of map and choice of character
    }
    //clear everything
    _window->close();
    
}

void McGuyverType::gameLoop()
{
    // here we need to check with clients if new people connect in order to create new player entities with their spaceship choice

    _assetManager->getMaps().at(_currentLevel)->mapUpdate();
    _cameraManager->changeCameraPosition(_assetManager->getSpecificDrawableWithType(_assetManager->getMaps().at(_currentLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));
    //do all checks if needed ( pause game, open whatefver menu, communicated with whatever process)
    //here we loop through all our systems to update them
    for( std::shared_ptr<ISystem> system : _systems)
        system->update(this->_allEntities);
    //then we draw (normally we draw in systems but with networking we have to split it)
    //then if game ends or somethings
    //then finish

    // Draw
    //----------------------------------------------------------------------------------
    // _renderer->beginDrawing();
    //     _renderer->clearBackground();

    //     _renderer->drawBackground(_assetManager, _currentLevel);

    //     _renderer->begin3DMode(_cameraManager->getCamera());
        


            // if (_inputManager->playerHasPressedKeyAsChar('p')) {
            //    spaceshipIndex += 1;
            //     if (spaceshipIndex == _assetManager->getSpacecraftModels().size() )
            //         spaceshipIndex = 0;
            // }
            // DrawModelEx(_assetManager->getSpacecraftModels()[spaceshipIndex]->getModel(),{2.5f, 1.0f, _cameraManager->getCamera().position.z + enemyStartingZ }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);     
            // if (_inputManager->playerHasPressedKeyAsChar('e')) {
            //     ennemyIndex += 1;
            //     if (ennemyIndex == _assetManager->getEnnemyModels().size() )
            //         ennemyIndex = 0;
            // }   
            // DrawModelEx(_assetManager->getEnnemyModels()[ennemyIndex]->getModel(),{-5.0f, 1.0f,_cameraManager->getCamera().position.z + enemyStartingZ }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
            // if (_inputManager->playerHasPressedKeyAsChar('l')) {
            //     projectileIndex += 1;
            //     if (projectileIndex == _assetManager->getProjectileModels().size() )
            //         projectileIndex = 0;
            // }
            // DrawModelEx(_assetManager->getProjectileModels()[projectileIndex]->getModel(),{0.0f, 1.0f, _cameraManager->getCamera().position.z + _playerStartingZ }, {0, 1, 0}, 180.0f, {4.0f,4.0f, 4.0f}, WHITE);
            // if (_inputManager->playerHasPressedKeyAsChar('b'))
            //     _assetManager->getMaps().at(_currentLevel)->setFightingBossTrue();
            // if (_inputManager->playerHasPressedKeyAsChar('v'))
            //     _assetManager->getMaps().at(_currentLevel)->bossIsDown();




    //         _renderer->drawMap( _assetManager->getMaps().at(_currentLevel), _cameraManager->getCamera(), _assetManager);
    //         for (EntityID _ent:  EntityViewer<Position, Velocity, Input, EntityModelType>(*_entityManager.get()) ) {
    //             Position *objectPos = _entityManager->Get<Position>(_ent);
    //             ModelName *objectModelName = _entityManager->Get<ModelName>(_ent);
    //             EntityModelType *modelType = _entityManager->Get<EntityModelType>(_ent);
    //             ModelScale *modelScale = _entityManager->Get<ModelScale>(_ent);
    //             Owner *owner = _entityManager->Get<Owner>(_ent);
    //             _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType(objectModelName->modelname, modelType->modelType)->getModel(), objectPos->pos, modelScale->modelScale, owner->ownerType);
    //         }
    //         // DrawGrid(2000, 1.0f);        // Draw a grid
    //         // std::cout << " current stage = " << this->_assetManager->getMaps().at(_currentLevel)->getCurrentStage() 
    //         // << "and max stage is = " << this->_assetManager->getMaps().at(_currentLevel)->getMaxStage() << std::endl;
    //     _renderer->end3DMode();


    //     // send data to server functions
    //     DrawFPS(10, 10);
    // _renderer->endDrawing();
    //---------------------------------------------------------------------------------- 
    
}



void McGuyverType::createPlayer(std::string modelName)
{
    EntityID id = _entityManager->CreateNewEntity();
    //register this entity as the player for this client
    std::vector<int> playerInput;
    _entityManager->Assign<EntityModelType>(id, EntityModelType{RL::ModelType::SPACESHIP});
    _entityManager->Assign<Owner>(id, Owner{this->_thisClientPlayerEntityID, RL::ModelType::MCGUYVER});
    
    _entityManager->Assign<ModelName>(id, ModelName{modelName});
    _entityManager->Assign<ModelScale>(id, ModelScale{1.0f});
    _entityManager->Assign<PitchYawRoll>(id, PitchYawRoll{0.0f, 0.0f, 0.0f});
    _entityManager->Assign<Input>(id, Input{playerInput});
    
    _entityManager->Assign<IsAlive>(id, IsAlive{true});
    _entityManager->Assign<Position>(id, _playerStartingPos);
    _entityManager->Assign<Velocity>(id, Velocity{0.2f, 0.2f, 0.2f});
    _entityManager->Assign<Score>(id, Score{0});
    _entityManager->Assign<Hp>(id, Hp{100});
    _entityManager->Assign<Shield>(id, Shield{0});


}


//getters

std::shared_ptr <EntityManager> McGuyverType::getEm()
{
    return _entityManager;
}


