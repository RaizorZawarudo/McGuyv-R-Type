/*
** EPITECH PROJECT, 2023
** MC_GUYVER TYPE
** File description:
** MenuManager
*/
#pragma once

#include "Renderer.hpp"
#include "AssetManager.hpp"
#include "CameraManager.hpp"
#include "Window.hpp"
#include "InputManager.hpp"
#include "Networking/UDPClient.hpp"
#include "../Server/Networking/protocol/Serializator.hpp"
#include "SoundManager.hpp"
#include <string> 
#include <raylib.h>
#include <iostream>
#include <thread>
#include <queue>

const int HOVER = -54;
const int CLICK = -55;
const int NOINTERACT = -56;

const int QUITGAME = 1000;
const int STARTSCREEN = 999;
const int CHARACTERSELECTSCREEN = 998;
const int GAMETYPESELECTIONSCREEN = 997;
const int TIMETOPLAY = 996;
const int PLAYING = 995;

const int WAITING = 994;


const int TITLEX = 40;
const int TITLEY = 20;
const int PLAYGAMEX = 25;
const int EXITX = 65;
const float PLAYGAMEY = 75.5;

namespace RL {
    class MenuManager {
        public:
            MenuManager(std::shared_ptr<RL::Window> window, std::shared_ptr<RL::CameraManager> cameraManager, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::Renderer> renderer, std::shared_ptr<RL::InputManager> inputManager, std::shared_ptr<RL::SoundManager> soundManager, std::shared_ptr<UDPClient> udpClient);
            ~MenuManager();

            int mouseInteractWithMenuElement(RL::Drawable2D* element);

            bool drawMenu();
            void StartScreen();
            void drawTitle();
            void drawHomePageButtons();
            
            void gameTypeSelectionScreen();
            void CharacterSelectionScreen();

            //getter

            int getCurScreen();
            int setCurentClientId();
            std::string getCharacterName();
            int getMapSelectIndex();
            bool getRacerMode();

            //setter

            void setMenuPage(int menuPage);

            

        protected:
        private:
            std::shared_ptr<RL::Renderer> _renderer;
            std::shared_ptr<AssetManager> _assetManager;
            std::shared_ptr<RL::CameraManager> _cameraManager;
            std::shared_ptr<RL::Window> _window;
            std::shared_ptr<RL::InputManager> _inputManager;
            std::shared_ptr<RL::SoundManager> _soundManager;
            std::shared_ptr<UDPClient> _udpClient;
            Serializator _serializator;
            bool _canSelect = false;
            bool _hasSelected = false;

            std::vector<int> _keysPressed;
            std::vector<RL::Drawable2D*> _menuElements;


            std::string _selectedCharName = "none";
            std::string _selectedWorld;
            std::string _selectedMode;
            int _mapSelectIndex = 0;

            bool _racerMode = false; //set to false by default, true is only for testing



            bool _isMaster = false;
            int _curScreen;
            int _prevScreen;
            

    };
};