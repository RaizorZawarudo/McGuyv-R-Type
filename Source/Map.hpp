/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Map
*/

#pragma once

#include <raylib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <cstring>
#include <cstdlib>

#include "CsvParser.hpp"
#include "Drawable3D.hpp"


typedef struct
    {
        std::string _pathName;
        int _length;
        float _width;
        float _height;

        Vector3 _cameraPositionMcGuyv;
    } repeatPathData_t;

typedef struct
    {
        std::string _bossRoomName;
        std::string _bossName;

        float _length;
        float _width;
        float _height;

        Vector3 _cameraPositionMcGuyv;

    } bossRoomData_t;

typedef struct
    {
        std::string _sectionName;
        float _zPosition;
        float _length;
        bool _isBossRoom;

    } mapQueueSection_t;

    
class Map {
    public:
        Map(std::string mapName, std::string mapPath, std::vector<RL::Drawable3D*> zonesModels);
        ~Map();

        //load map data
        void fillMapData(std::string mapPath, std::vector<RL::Drawable3D*> zonesModels);
        repeatPathData_t fillPathData(std::string zoneName, std::vector<RL::Drawable3D*> zonesModels);
        bossRoomData_t fillBossRoomData(std::string zoneName, std::vector<RL::Drawable3D*> zonesModels);


        //Map update and logic and scrolling and (to add spawning of bosses and mobs and walls etc)
        void mapUpdate();
        void refillMapQueue();
        void updateMapQueue();

        //getters
        std::string getMapName();
        std::vector<repeatPathData_t> getMapPathsData();
        std::vector<bossRoomData_t> getMapBossRoomData();
        std::vector<mapQueueSection_t> getMapQueue();
        int getCurrentStage();
        bool getFightingBoss();
        bool getGameRunning();

        //setters
        void setGameRunning();


    private:

        std::string _mapName;
        float _scrollspeed;

        std::vector<repeatPathData_t> _repeatPaths; //this should be in order of game aspect in the csv already
        std::vector<bossRoomData_t> _bossRooms; // this should be in order also in csv
        //we dont need a display queue we just need to know what stage we are on  and if we are fighting a boss
        // eg : we are in stage2, so we can only display repeatPaths[2] and if we enter the conditions to spawn boss, we will have 
        // is fighting boss == 1 then we display the boss room at the end and stop adding new rooms .

        std::vector<mapQueueSection_t> _mapQueue;

        //delete these two lines later, not usefull anymore
        std::vector<std::string> _repeatPathsnames;
        std::vector<std::string> _bossRoomsnames;

        bool _gameRunning = false;
        int _currentStage = 0;
        bool _isFightingBoss = false;
        bool _hasSpawnedBossroom = false;

        
};
