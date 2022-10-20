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

class DrawingSystem : public ISystem  {
    public:
        DrawingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Renderer> renderer, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::CameraManager> cameraManager);
        ~DrawingSystem();

        void update(std::vector<EntityID> &allEntities) override;

    protected:
    private:
        std::shared_ptr<RL::Renderer> _renderer;
        std::shared_ptr<AssetManager> _assetManager;
        std::shared_ptr<RL::CameraManager> _cameraManager;

};

