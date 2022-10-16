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
        std::vector<Map*> loadMaps();
        std::vector<RL::Drawable2D*> loadAllBackgrounds(const std::string &path);

        //getters
        std::vector<RL::Drawable3D*> getZonesModels();
        std::vector<RL::Drawable3D*> getProjectileModels();
        std::vector<RL::Drawable3D*> getSpacecraftModels();
        std::vector<RL::Drawable3D*> getEnnemyModels();
        std::vector<Map*> getMaps();
        std::vector<RL::Drawable2D*> getBackgrounds();

        RL::Drawable2D* getSpecificBackground(std::string backgroundName);
        RL::Drawable3D* getSpecificDrawableWithType(std::string modelName, RL::ModelType modelType);

    private:
        //3d assets
        std::vector<RL::Drawable3D*> _zonesModels;
        std::vector<RL::Drawable3D*> _projectileModels;
        std::vector<RL::Drawable3D*> _spacecraftModels;
        std::vector<RL::Drawable3D*> _ennemyModels;
        std::vector<RL::Drawable2D*> _ingameBackgrounds;

        //maps
        std::vector<Map*> _maps;

};

