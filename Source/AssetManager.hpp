/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** AssetManager
*/

#include <vector>
#include "raylib.h"
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"
#include "Map.hpp"

#pragma once


class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        //loading functions
        void loadAllModels();
        void loadAllMaps();
        std::vector<RL::Drawable3D*> loadModels(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadObstacleModels(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadExplosionModels(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadEffectModels3D(const std::string &path, RL::ModelType type);
        std::vector<Map*> loadMaps();
        std::vector<RL::Drawable2D*> loadAllBackgrounds(const std::string &path);

        //getters
        std::vector<RL::Drawable3D*> getZonesModels();
        std::vector<RL::Drawable3D*> getProjectileModels();
        std::vector<RL::Drawable3D*> getSpacecraftModels();
        std::vector<RL::Drawable3D*> getEnnemyModels();
        std::vector<RL::Drawable3D*> getObstacleModels();
        std::vector<RL::Drawable3D*> getExplosionModels();
        std::vector<RL::Drawable3D*> getEffectsModels3D();
        std::vector<Map*> getMaps();
        std::vector<RL::Drawable2D*> getBackgrounds();
        int getCurrentMapBeingPlayed();


        RL::Drawable2D* getSpecificBackground(std::string backgroundName);
        RL::Drawable3D* getSpecificDrawableWithType(std::string modelName, RL::ModelType modelType);

        //setters

        void setCurrentMapBeingPlayed(int level);

    private:
        int _currentLevelBeingPlayed;
        //3d assets
        std::vector<RL::Drawable3D*> _zonesModels;
        std::vector<RL::Drawable3D*> _projectileModels;
        std::vector<RL::Drawable3D*> _spacecraftModels;
        std::vector<RL::Drawable3D*> _ennemyModels;
        std::vector<RL::Drawable3D*> _obstacleModels;
        std::vector<RL::Drawable3D*> _explosionModelsAnim;
        std::vector<RL::Drawable3D*> _effectsModels3D;
        std::vector<RL::Drawable2D*> _ingameBackgrounds;

        //maps
        std::vector<Map*> _maps;

};

