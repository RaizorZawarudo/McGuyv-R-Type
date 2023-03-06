/*
** EPITECH PROJECT, 2023
** MC_GUYVER TYPE
** File description:
** MenuManager
*/

#include "MenuManager.hpp"

RL::MenuManager::MenuManager(std::shared_ptr<RL::Window> window, std::shared_ptr<RL::CameraManager> cameraManager, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::Renderer> renderer, std::shared_ptr<RL::InputManager> inputManager,std::shared_ptr<RL::SoundManager> soundManager, std::shared_ptr<UDPClient> udpClient)
{
    _window = window;
    _cameraManager = cameraManager;
    _assetManager = assetManager;
    _renderer = renderer;
    _inputManager = inputManager;
    _soundManager= soundManager;
    _udpClient = udpClient;

    for (RL::Drawable2D* icon : _assetManager->getUIelements()) {
        if (icon->getName() == "menuButton1") {
            _menuElements.push_back(icon);
            _menuElements.back()->setPosition(_window->getDimensions().x/100 * 15,_window->getDimensions().y/100 * 70, 0);
        }
        if (icon->getName() == "menuButton2") {
            _menuElements.push_back(icon);
            _menuElements.back()->setPosition(_window->getDimensions().x/100 * 55,_window->getDimensions().y/100 * 70, 0);
        }
        if (icon->getType() == "player") {
            _menuElements.push_back(icon);
        }
        if (icon->getType() == "arrow") {
            _menuElements.push_back(icon);
            icon->resize(Vector2{_window->getDimensions().x * 3.9f / 100,_window->getDimensions().y * 5.2f / 100 });
        }
        if (icon->getType() == "gameMode") {
            _menuElements.push_back(icon);
            icon->resize(Vector2{_window->getDimensions().x * 7.8f / 100,_window->getDimensions().y * 10.4f / 100 });
        }
    }
}

RL::MenuManager::~MenuManager()
{  
}

int RL::MenuManager::mouseInteractWithMenuElement(RL::Drawable2D* element)
{
    if (_inputManager->getMousePosition().x < element->getPosition().x || _inputManager->getMousePosition().x > (element->getPosition().x + element->getSize().x))
        return NOINTERACT;
    if (_inputManager->getMousePosition().y < element->getPosition().y || _inputManager->getMousePosition().y > (element->getPosition().y + element->getSize().y))
        return NOINTERACT;
    element->setTint(YELLOW);
    if (_inputManager->isMouseLeftClicked())
        return CLICK;
    return HOVER;
}

bool RL::MenuManager::drawMenu()
{
    int j;
    _curScreen = STARTSCREEN;
    while(_curScreen != QUITGAME && _curScreen != TIMETOPLAY) {
        std::vector<boost::array<char, 1024UL>> packets = _udpClient->getMessages();
        for (auto packet : packets) {
            Msg msg = _serializator.bytesToStruct(packet.data());
            switch (msg.getstatus()) {
                case serializator::Header::menu:
                    if (msg.getClientHash() == 1) {
                        _isMaster = true;
                        _canSelect = true;
                    }
                    // std::cout << "HASH CLIENT " << msg.getClientHash() << std::endl;
                    _assetManager->setCurrentClientID(msg.getClientHash());
                    break;
                case serializator::Header::canSelect:
                    // if (!_isMaster) {
                        _canSelect = true;
                        _assetManager->setCurrentMapBeingPlayed(msg.getMapIndex());
                        if (msg.getRacerMode())
                            _assetManager->setRacerMode();
                    // }
                    break;
                case serializator::Header::startGame:
                    std::cout << " start Game " << std::endl;
                    _curScreen = TIMETOPLAY;
                    // _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed())->setGameRunning();
                    // _assetManager->set (msg.getMapIndex());
                    // _assetManager->setCurrentMapBeingPlayed(msg.getMapIndex());
                    break;
                default:
                    break;
            }
        }
        _renderer->beginDrawing();
            _renderer->clearBackground();
            //get the player presses
            // j = handleMenuInputs(j);
            
            
            //change menu screens dependig on what the player pressed
            j = _curScreen;
            switch (j)
            {
                case STARTSCREEN :
                    StartScreen();
                    break;
                case GAMETYPESELECTIONSCREEN:
                    gameTypeSelectionScreen();
                    break;
                case CHARACTERSELECTSCREEN:
                    CharacterSelectionScreen();
                    break;

                default:
                    break;
            }
        DrawFPS(10, 10);
        _renderer->endDrawing();
        _inputManager->popInputs();
    }
    std::cout << "curScreen = " << _curScreen << " prevScreen = " << _prevScreen << std::endl;
    return false;
}

void RL::MenuManager::drawTitle()
{
    _renderer->draw_text("McGUYVER-TYPE", RAYWHITE,_window->getDimensions().x/100 * TITLEX,_window->getDimensions().y/100 * TITLEY, _assetManager->getAllFonts().at(0), 35);
}

void RL::MenuManager::drawHomePageButtons()
{
    if (_canSelect)
        _renderer->draw_text("\tENTER", RAYWHITE,_window->getDimensions().x/100 * PLAYGAMEX,_window->getDimensions().y/100 * PLAYGAMEY, _assetManager->getAllFonts().at(0), 30);
    _renderer->draw_text("\tQUIT", RAYWHITE,_window->getDimensions().x/100 * EXITX,_window->getDimensions().y/100 * PLAYGAMEY, _assetManager->getAllFonts().at(0), 30);
}

//START SCREEN WHEN
void RL::MenuManager::StartScreen()
{
    _prevScreen = _curScreen;
    _renderer->draw_2D_model(_assetManager->getSpecificBackground("neonracing")->getTexture() , 0 , 0);

    drawTitle();
    for (RL::Drawable2D* button : _menuElements) {
        if ((button->getName() == "menuButton1" && _canSelect) || button->getName() == "menuButton2")
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                if (button->getName() == "menuButton2")
                    _curScreen = QUITGAME;
                if (button->getName() == "menuButton1" && _canSelect) {
                    //call to server
                     // _isMaster = callToServerGetAnswer();
                    if (_isMaster)
                        _curScreen = GAMETYPESELECTIONSCREEN;
                    else
                        _curScreen = CHARACTERSELECTSCREEN;
                }
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
    }
    
    drawHomePageButtons(); //this is acrually drawHomePageButtonTEXT...
}

//GAME TYPE SELECTION SCREEN FOR MASTER PLAYER
void RL::MenuManager::gameTypeSelectionScreen()
{
    int startbuttonx =  _window->getDimensions().x /100 * 27;
    int startbuttony =  _window->getDimensions().y /100 * 76;
    int charselX = 37;
    int charselY = 22;
    int worldselectx = _window->getDimensions().x /100 * 40;
    int worldselecty = _window->getDimensions().x /100 * 26;

    _renderer->draw_2D_model(_assetManager->getSpecificBackground("neonracing")->getTexture() , 0 , 0);

    _renderer->draw_text("SELECT GAME MODES", RAYWHITE,_window->getDimensions().x/100 * charselX,_window->getDimensions().y/100 * charselY, _assetManager->getAllFonts().at(0), 35);
    
    for (RL::Drawable2D* button : _menuElements) {
        if (_isMaster) {
            //CONFIRM BUTTON
            if (button->getName() == "menuButton2") {
                button->draw();
                if (mouseInteractWithMenuElement(button) == CLICK) {
                    _soundManager->playSpecificSoundFx("smallClick");
                    char *package = _serializator.createPackageCanSelect(serializator::Header::canSelect, _mapSelectIndex, _racerMode);
                    _udpClient->send(package, SIZE_CAN_SELECT);
                    delete package;
                    //send message to server to launch game
                    _curScreen = CHARACTERSELECTSCREEN; // to be removed once we implement
                    _assetManager->setCurrentMapBeingPlayed(_mapSelectIndex);
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
            }
            _renderer->draw_text("CONFIRM", RAYWHITE, startbuttonx /26 * 67, startbuttony, _assetManager->getAllFonts().at(0), 30);
        }
        //RETURN BUTTON
        if (button->getName() == "menuButton1") {
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                if (button->getName() == "menuButton1") {
                    _curScreen = _prevScreen;
                }
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
        }
        _renderer->draw_text("RETURN", RAYWHITE, startbuttonx, startbuttony, _assetManager->getAllFonts().at(0), 30);

        //LEFT ARROW
        if (button->getName() == "leftArrow") {
            button->setPosition(worldselectx /40 * 30 , worldselecty, 0);
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                _mapSelectIndex -= 1;             
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
        }
        //RIGHT ARROW
        if (button->getName() == "rightArrow") {
            button->setPosition(worldselectx /40 * 68, worldselecty, 0);
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                _mapSelectIndex += 1;                
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
        }

        if (button->getName() == "racerMode") {
            if (_racerMode == true)
                button->setTint(YELLOW);
            button->setPosition(worldselectx /40 * 45, worldselecty /26 * 40, 0);
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                _racerMode = true;                
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
        }

        if (button->getName() == "storyMode") {
            if (_racerMode == false)
                button->setTint(YELLOW);
            button->setPosition(worldselectx /40 * 55, worldselecty /26 * 40, 0);
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                _racerMode = false;                
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
        }

        //ADD ICONS FOR RACER OR NORMAL MODE AND WE HAVE A MENU

        if (_mapSelectIndex < 0)
            _mapSelectIndex = _assetManager->getMaps().size() - 1;
        if (_mapSelectIndex > _assetManager->getMaps().size() -1)
            _mapSelectIndex = 0;
        
        
        _renderer->draw_text(_assetManager->getMaps().at(_mapSelectIndex)->getMapName(), RAYWHITE, worldselectx, worldselecty, _assetManager->getAllFonts().at(0), 30);


    }
}

//CHARACTER SELECTION SCREEN FOR ALL PLAYERS
void RL::MenuManager::CharacterSelectionScreen()
{
    int charselX = 35;
    int charselY = 22;
    int x = _window->getDimensions().x /100 * 25;
    int y = _window->getDimensions().y /100 * 42;
    int choicex = _window->getDimensions().x /100 * 47;
    int choicey = _window->getDimensions().y /100 * 73;
    int startbuttonx =  _window->getDimensions().x /100 * 26;
    int startbuttony =  _window->getDimensions().y /100 * 76;
    int pos = 0;

    _renderer->draw_2D_model(_assetManager->getSpecificBackground("neonracing")->getTexture() , 0 , 0);

    _renderer->draw_text("SELECT YOUR CHARACTER", RAYWHITE,_window->getDimensions().x/100 * charselX,_window->getDimensions().y/100 * charselY, _assetManager->getAllFonts().at(0), 35);


    //here do call for the server to know if master sent the game
    // _curScreen =  = call to server
    

    for (RL::Drawable2D* button : _menuElements) {
        if (button->getType() == "player" && !_hasSelected) {
            if (_selectedCharName == button->getName())
                button->setTint(YELLOW);
            button->setPosition(x + (pos * (_window->getDimensions().x * 7.8f / 100 + (_window->getDimensions().x * 7.8f / 100 / 8))), y,0);
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("bigClick");
                for (int i = 0; i < _assetManager->getSpacecraftModels().size(); i += 1) {
                    if (_assetManager->getSpacecraftModels().at(i)->getName() == button->getName()) {
                        std::cout << "CURRENT ID  " << _assetManager->getCurrentClientID() << std::endl;
                        char *package = _serializator.createPackageSetSpaceShip(serializator::Header::spaceShipSelection, i, _assetManager->getCurrentClientID());
                        _udpClient->send(package, sizeof(int) + 1 + sizeof(unsigned long long));
                        delete package;
                        _hasSelected = true;
                    }
                }
                std::cout << button->getName() << std::endl;
                _selectedCharName == button->getName() ? _selectedCharName = "none" : _selectedCharName = button->getName();                
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
        pos++;
        }
    }

    for (RL::Drawable2D* button : _menuElements) {
        if (button->getName() == _selectedCharName) {
            _renderer->draw_text("YOU CHOOSE", RAYWHITE, choicex / 45 * 45, choicey / 75 * 68, _assetManager->getAllFonts().at(0), 30);
            button->setPosition(choicex, choicey, 0);
            button->setTint(WHITE);
            button->draw();
        }
    }
    for (RL::Drawable2D* button : _menuElements) {
        if (_isMaster) {
            if (button->getName() == "menuButton2") {
                button->draw();
                if (mouseInteractWithMenuElement(button) == CLICK) {
                    _soundManager->playSpecificSoundFx("smallClick");
                    if (_selectedCharName != "none") {
                        char *package = _serializator.createPackageStartGame(serializator::Header::startGame, true);
                        _udpClient->send(package, 2);
                        delete package;
                        // _curScreen = TIMETOPLAY; // to be removed once we implement
                    }
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
            }
            _renderer->draw_text("PLAY", RAYWHITE, startbuttonx /26 * 68, startbuttony, _assetManager->getAllFonts().at(0), 30);
        }
        if (button->getName() == "menuButton1")
            button->draw();
            if (mouseInteractWithMenuElement(button) == CLICK) {
                _soundManager->playSpecificSoundFx("smallClick");
                if (button->getName() == "menuButton1") {
                    _curScreen = _prevScreen;
                    _selectedCharName = "none";
                }
            }
            else if (mouseInteractWithMenuElement(button) == NOINTERACT)
                button->setTint(WHITE);
            _renderer->draw_text("RETURN", RAYWHITE, startbuttonx, startbuttony, _assetManager->getAllFonts().at(0), 30);
    }

    

    //send selected char name to server

    //if (server sends OK CHAR NAME)

    if (_curScreen == TIMETOPLAY) {
        // send to server that we are ready to play
        return;
    }

}

//getter

int RL::MenuManager::getCurScreen()
{
    return this->_curScreen;
}

std::string RL::MenuManager::getCharacterName()
{
    return this->_selectedCharName;
}

int RL::MenuManager::getMapSelectIndex()
{
    return this->_mapSelectIndex;
}

bool RL::MenuManager::getRacerMode()
{
    return this->_racerMode;
}


//setter

void RL::MenuManager::setMenuPage(int menuPage)
{
    this->_curScreen = menuPage;
    this->_prevScreen = STARTSCREEN;
}