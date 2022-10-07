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

    
class Map {
    public:
        Map(std::string mapName, std::string mapPath, std::vector<RL::Drawable3D*> zonesModels);
        ~Map();

        //load map data
        void fillMapData(std::string mapPath, std::vector<RL::Drawable3D*> zonesModels);
        repeatPathData_t fillPathData(std::string zoneName, std::vector<RL::Drawable3D*> zonesModels);
        bossRoomData_t fillBossRoomData(std::string zoneName, std::vector<RL::Drawable3D*> zonesModels);

        //getters
        std::string getMapName();
        std::vector<repeatPathData_t> getMapPathsData();
        std::vector<bossRoomData_t> getMapBossRoomData();
        int getCurrentStage();
        


        
    private:

        std::string _mapName;

        std::vector<repeatPathData_t> _repeatPaths;
        std::vector<bossRoomData_t> _bossRooms;
        std::vector<std::string> _repeatPathsnames;
        std::vector<std::string> _bossRoomsnames;

        int currentStage = 0;

        
};
