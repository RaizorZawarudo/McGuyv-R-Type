/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** AssetManager
*/

#include <vector>
#include "raylib.h"
#include "Drawable3D.hpp"
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

        //getters
        std::vector<RL::Drawable3D*> getZonesModels();
        std::vector<RL::Drawable3D*> getProjectileModels();
        std::vector<RL::Drawable3D*> getSpacecraftModels();
        std::vector<RL::Drawable3D*> getEnnemyModels();
        std::vector<Map*> getMaps();

        RL::Drawable3D* getSpecificDrawableWithType(std::string modelName, RL::ModelType modelType);

    private:
        //3d assets
        std::vector<RL::Drawable3D*> _zonesModels;
        std::vector<RL::Drawable3D*> _projectileModels;
        std::vector<RL::Drawable3D*> _spacecraftModels;
        std::vector<RL::Drawable3D*> _ennemyModels;

        //maps
        std::vector<Map*> _maps;

};

