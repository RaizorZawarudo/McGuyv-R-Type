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

const int WEAPON1INDX = 28;
const int WEAPON1INDY = 83;
const int WEAPON2INDX = 33;
const int WEAPON2INDY= 83;
const int WEAPON3INDX = 38;
const int WEAPON3INDY = 83;

const int WEAP1AMMOX = 28;
const int WEAP1AMMOY = 90;
// const int WEAP2AMMOX = ;
// const int WEAP3AMMOX = ; 

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



    protected:
    private:
        std::shared_ptr<RL::Renderer> _renderer;
        std::shared_ptr<AssetManager> _assetManager;
        std::shared_ptr<RL::CameraManager> _cameraManager;
        std::shared_ptr<RL::Window> _window;

};

