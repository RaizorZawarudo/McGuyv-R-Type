/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** AssetManager
*/

#pragma once

#include <vector>
#include "raylib.h"
#include "Drawable3D.hpp"
#include "Drawable2D.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"

#pragma once
typedef struct Scenario {
    std::string scenarioName;
    std::vector<std::string> waveNames;
    std::vector<std::string> waveTypes;
    //can add minimum score / minimum time played in the scenario before a boss pops, to be optimised
    std::vector<int> waveamounts; 
} Scenario_t;

typedef struct waveAsset {
    std::string codename;
    Vector3 position;

} waveAsset_t;

typedef struct GameWave {
    std::string name;
    std::vector<waveAsset_t> waveComponents;
} Wave_t;

class AssetManager {
    public:
        AssetManager(EntityID currentClientID);
        ~AssetManager();

        //loading functions
        void loadAllModels();
        void loadAllMaps();
        std::vector<RL::Drawable3D*> loadModels(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadObstacleModels(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadExplosionModels(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadEffectModels3D(const std::string &path, RL::ModelType type);
        std::vector<RL::Drawable3D*> loadPowerUpModels(const std::string &path, RL::ModelType type);
        std::vector<Map*> loadMaps();
        std::vector<RL::Drawable2D*> loadAllBackgrounds(const std::string &path);
        std::vector<RL::Drawable2D*> loadAllIcons(const std::string &path);
        std::vector<Font> loadAllFonts(const std::string &path);

        std::vector<Wave_t> loadObstacleWaves(const std::string &path);
        std::vector<Wave_t> loadEnnemyWaves(const std::string &path);
        std::vector<waveAsset_t> loadWaveData(const std::string &path);
        waveAsset_t loadWaveAssetData(std::string name, int i, int j);

        //std::vector<Wave_t> loadEnnemyWaves(const std::string &path);

        std::vector<Scenario_t> loadAllScenarios(const std::string &path);
        std::vector<std::string> loadScenarioData(const std::string &path);
        std::vector<std::string> loadScenarioDataAgain(const std::string &path);


        


        //getters
        std::vector<RL::Drawable3D*> getZonesModels();
        std::vector<RL::Drawable3D*> getProjectileModels();
        std::vector<RL::Drawable3D*> getSpacecraftModels();
        std::vector<RL::Drawable3D*> getEnnemyModels();
        std::vector<RL::Drawable3D*> getObstacleModels();
        std::vector<RL::Drawable3D*> getExplosionModels();
        std::vector<RL::Drawable3D*> getEffectsModels3D();
        std::vector<RL::Drawable3D*> getPowerUpModels();
        std::vector<Map*> getMaps();
        std::vector<Wave_t> getObstacleWaves();
        std::vector<Wave_t> getEnnemyWaves();
        std::vector<Scenario_t> getScenarios();
        std::vector<RL::Drawable2D*> getBackgrounds();
        std::vector<RL::Drawable2D*> getUIelements();
        std::vector<Font> getAllFonts();
        int getCurrentMapBeingPlayed();
        EntityID getCurrentClientID();
        int getLootRand();
        bool getRacerMode();
        
        std::chrono::system_clock::time_point getStartTimestamp();


        RL::Drawable2D* getSpecificBackground(std::string backgroundName);
        RL::Drawable3D* getSpecificDrawableWithType(std::string modelName, RL::ModelType modelType);
        RL::Drawable2D* getSpecificIcon(std::string modelName);

        //setters

        void setCurrentMapBeingPlayed(int level);
        void setLootRand(int random);
        void startTime();
        void setRacerMode();
        void setCurrentClientID(EntityID id);

    private:
        //game related variables need for updates etc
        EntityID _currentclientID;
        int _currentLevelBeingPlayed;
        int _lootrand;
        std::chrono::system_clock::time_point _startTimestamp; // initialized at the start of the game


        //3d assets
        std::vector<RL::Drawable3D*> _zonesModels;
        std::vector<RL::Drawable3D*> _projectileModels;
        std::vector<RL::Drawable3D*> _spacecraftModels;
        std::vector<RL::Drawable3D*> _ennemyModels;
        std::vector<RL::Drawable3D*> _obstacleModels;
        std::vector<RL::Drawable3D*> _explosionModelsAnim;
        std::vector<RL::Drawable3D*> _effectsModels3D;
        std::vector<RL::Drawable3D*> _powerUpModels;

        //2d assets
        std::vector<RL::Drawable2D*> _ingameBackgrounds;
        std::vector<RL::Drawable2D*> _IconsUIelements;

        //maps
        std::vector<Map*> _maps;

        //data assets
        std::vector<Wave_t> _obstacleWaves;
        std::vector<Wave_t> _ennemyWaves;
        std::vector<Scenario_t> _scenarios;

        //scenario   this is what decides how the game flows and when boss pops etc etc
        //           so this is a vector of scenarios where it has the ennemy waves and obstacles waves order
        //           for the current map the player selected, and also what are the requirements for a boss to pop etc
        //           and when the scenario is being completed it can contact the map to tell it hey open boss room
        // .         and when the boss is dead it should tell the scenario and tell the map that it died
        //           so dont forget to do it the delete entity system a function that if the ennemy is a boss it should
        // .         contact the map AND the scenario to push the game forward. also add scenario and map in the delete entity systemnow

        //fonts
        std::vector<Font> _fonts;
        bool _racerMode = false;

        //

};

