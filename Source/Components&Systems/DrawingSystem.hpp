/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** DrawingSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../Renderer.hpp"
#include "../AssetManager.hpp"
#include "../CameraManager.hpp"
#include "../Window.hpp"
#include "raymath.h"

const int PANNELLEFTX = 15;
const int PANNELRIGHTX = 55;
const int PANNELSY = 80;

const int PLAYERICONX = 17;
const int PLAYERICONY = 83;

const int SCOREX = 62;
const int SCOREY = 87;

const float WEAPON1INDX = 4.2+28;
const float WEAPON1INDY = 82.5;
const float WEAPON2INDX = 4.2+33;
const float WEAPON2INDY = 82.5;
const float WEAPON3INDX = 4.2+38;
const float WEAPON3INDY = 82.5;

const float SHIELDVALUEX = 4.2+23;
const float SHIELDVALUEY = 91;
const float WEAP1AMMOX = 4.2+28;
const float WEAP1AMMOY = 91;
const float WEAP2AMMOX = 4.2+32.2;
const float WEAP2AMMOY = 91;
const float WEAP3AMMOX = 4.2+37.2;
const float WEAP3AMMOY = 91;

class DrawingSystem : public ISystem  {
    public:
        DrawingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Renderer> renderer, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::CameraManager> cameraManager, std::shared_ptr<RL::Window> window);
        ~DrawingSystem();

        void update(std::vector<EntityID> &allEntities) override;

        void explosionDrawing();
        void shieldDrawing();
        void playerUIDrawing(EntityID clientplayerID);

        void handleWeaponslots(EntityID clientplayerID);
        void handleWeaponAmmo(EntityID clientplayerID);

        void handleShield(EntityID clientplayerID);



    protected:
    private:
        std::shared_ptr<RL::Renderer> _renderer;
        std::shared_ptr<AssetManager> _assetManager;
        std::shared_ptr<RL::CameraManager> _cameraManager;
        std::shared_ptr<RL::Window> _window;
};

