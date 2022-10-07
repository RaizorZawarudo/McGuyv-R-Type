/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(std::string mapName, std::string MapPath, std::vector<RL::Drawable3D*> zonesModels)
{
    this->_mapName = mapName;
    fillMapData(MapPath, zonesModels);


    
    //debug end
}

Map::~Map()
{
    //this->_mapStaticAssets.clear();
}

void Map::fillMapData(std::string MapPath, std::vector<RL::Drawable3D*> zonesModels)
{
    std::vector<std::vector<std::string>> parsedCsv = csvToTable(MapPath);

    // repeatPathData_t pathDataPunchCard;
    // bossRoomData_t bossRoomPunchCard;

    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0) { //j == 0 corresponds to al simple paths name
                this->_repeatPathsnames.emplace_back(parsedCsv[i][j]); //to be deleted once implementation line below is tested in main
                this->_repeatPaths.emplace_back(fillPathData(parsedCsv[i][j], zonesModels));
            }
            if (j == 1) {//j == 1 corresponds to all boss room names
               this->_bossRoomsnames.emplace_back(parsedCsv[i][j]); //to be deleted once implementation line below is tested in main
               this->_bossRooms.emplace_back(fillBossRoomData(parsedCsv[i][j], zonesModels));
            }
            //can add as many columns as we want in the csv if we want to add other types of rooms 
            // eg : transition pahts to blend from small mountain to big mountain etc etc
        }
    }
    //debugging
    std::cout << "MAP NAME = " << this->_mapName << std::endl; 
        for ( int i = 0 ; i < _repeatPathsnames.size(); i++)
            std::cout << "      has a simpe path called : " << _repeatPathsnames[i] << std::endl;
        for (int i = 0 ; i < _bossRoomsnames.size(); i++)
            std::cout << "      has a boss room called : " << _bossRoomsnames[i] << std::endl;
    

    
    //debugging end
}

repeatPathData_t Map::fillPathData(std::string zoneName, std::vector<RL::Drawable3D*> zonesModels)
{
    repeatPathData_t newrepeatPathData;

    newrepeatPathData._pathName = zoneName;

    for (int i  = 0; i < zonesModels.size(); i++) {
        if (zonesModels.at(i)->getName() == zoneName) {
            newrepeatPathData._height = zonesModels.at(i)->getHeight();
            newrepeatPathData._width = zonesModels.at(i)->getWidth();
            newrepeatPathData._length = zonesModels.at(i)->getLength();
            newrepeatPathData._cameraPositionMcGuyv = zonesModels.at(i)->getCameraPositionMcGuyv();
        }
    }
    return newrepeatPathData;
}

bossRoomData_t Map::fillBossRoomData(std::string zoneName, std::vector<RL::Drawable3D*> zonesModels)
{
    bossRoomData_t newBossRoomData;

    newBossRoomData._bossRoomName = zoneName;

    for (int i  = 0; i < zonesModels.size(); i++) {
        if (zonesModels.at(i)->getName() == zoneName) {
            newBossRoomData._height = zonesModels.at(i)->getHeight();
            newBossRoomData._width = zonesModels.at(i)->getWidth();
            newBossRoomData._length = zonesModels.at(i)->getLength();
            newBossRoomData._cameraPositionMcGuyv = zonesModels.at(i)->getCameraPositionMcGuyv();
        }
    }
    return newBossRoomData;
}

std::string Map::getMapName()
{
    return this->_mapName;
}

std::vector<repeatPathData_t> Map::getMapPathsData()
{
    return this->_repeatPaths;
}

std::vector<bossRoomData_t> Map::getMapBossRoomData()
{
    return this->_bossRooms;
}

int Map::getCurrentStage()
{
    return this->currentStage;
}