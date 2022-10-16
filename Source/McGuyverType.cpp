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

    //here we resize all the maps to be the dimension of the window
    for (Map* map: this->_assetManager->getMaps())
        _assetManager->getSpecificBackground(map->getBackgroundName())->resize(_window->getDimensions());
}

McGuyverType::~McGuyverType()
{
}

void McGuyverType::startGame()
{
    SetTargetFPS(60);
    _assetManager->getMaps().at(_currentLevel)->setGameRunning(); // current level to be modified my ui choice

    while (_window->isWindowOpen()) {
        //UI LOOP functions
        gameLoop(); //might take more arguments to refelct player choice of map and choice of character
    }
    _window->close();
    
}

void McGuyverType::gameLoop()
{

    _inputManager->popInputs();
    _inputManager->recordInputs();
    _keysPressed = _inputManager->getInputs();

    _assetManager->getMaps().at(_currentLevel)->mapUpdate();
    _cameraManager->changeCameraPosition(_assetManager->getSpecificDrawableWithType(_assetManager->getMaps().at(_currentLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));
       
    //do all checks if needed ( pause game, open whatefver menu, communicated with whatever process)
    //here we loop through all our systems to update them
    // for( std::shared_ptr<ISystem> system : _systems)
    //     system->update(what has the be updated as a system)
    //then we draw (normally we draw in systems but with networking we have to split it)
    //then if game ends or somethings
    //then finish

    // Draw
    //----------------------------------------------------------------------------------
    _renderer->beginDrawing();
        _renderer->clearBackground();

        _renderer->drawBackground(_assetManager, _currentLevel);

        _renderer->begin3DMode(_cameraManager->getCamera());
            //DRAW MODEL USING ASSET LIST FROM MANAGER 
            //TO BE ADDED IN THE RENDERER
            if (_inputManager->playerHasPressedKeyAsChar('p')) {
               spaceshipIndex += 1;
                if (spaceshipIndex == _assetManager->getSpacecraftModels().size() )
                    spaceshipIndex = 0;
            }
            DrawModelEx(_assetManager->getSpacecraftModels()[spaceshipIndex]->getModel(),{2.5f, 1.0f, _cameraManager->getCamera().position.z + enemyStartingZ }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
            
                
            if (_inputManager->playerHasPressedKeyAsChar('e')) {
                ennemyIndex += 1;
                if (ennemyIndex == _assetManager->getEnnemyModels().size() )
                    ennemyIndex = 0;
            }
                
            DrawModelEx(_assetManager->getEnnemyModels()[ennemyIndex]->getModel(),{-5.0f, 1.0f,_cameraManager->getCamera().position.z + enemyStartingZ }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
            if (_inputManager->playerHasPressedKeyAsChar('l')) {
                projectileIndex += 1;
                if (projectileIndex == _assetManager->getProjectileModels().size() )
                    projectileIndex = 0;
            }
            DrawModelEx(_assetManager->getProjectileModels()[projectileIndex]->getModel(),{0.0f, 1.0f, _cameraManager->getCamera().position.z + _playerStartingZ }, {0, 1, 0}, 180.0f, {4.0f,4.0f, 4.0f}, WHITE);
            _renderer->drawMap( _assetManager->getMaps().at(_currentLevel), _cameraManager->getCamera(), _assetManager);
            // DrawGrid(2000, 1.0f);        // Draw a grid
        _renderer->end3DMode();
        //Input queue must be popped
        _inputManager->popInputs();
        DrawFPS(10, 10);
    _renderer->endDrawing();
    //---------------------------------------------------------------------------------- 
    
}


