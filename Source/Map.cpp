/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(std::string mapName, std::string MapPath, std::vector<RL::Drawable3D*> zonesModels, std::string backgroundName)
{
    this->_mapName = mapName;
    this->_backgroundName = backgroundName;
    this->_currentSpeed = this->_scrollSpeed;
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
            std::cout << "      has a boss room called : " << _bossRoomsnames[i] << "of size " << _bossRooms[i]._length << std::endl;
    

    
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

void Map::mapUpdate()
{
    while (this->_mapQueue.size() < 6)
        refillMapQueue();
    if (this->_gameRunning)
        updateMapQueue(); //here we decrease the z of each mapSection_t by the movement speed backwards to create parallax effect
        // generate mobs / obstacles thorugh ECS by reading mob files and obstacles files, to be implemented !! mucho trabajo :S
        ;
}


//update this functions to stop when in bossroom and to set is fighting boss  to null AFTER boss is killed! and update current stage to +1 !!
//ALSO need to create a stop after we reached the max bosses and a variable in MAP that says _mapFinished = false ; set it to true when stage = max stage and has killed boss is true;
void Map::updateMapQueue()
{
    for (int i = 0; i < this->_mapQueue.size(); i++) {
        this->_mapQueue[i]._zPosition -= this->_currentSpeed;
        // if (this->_mapQueue[0]._isBossRoom && this->_isFightingBoss == true ) // add & isfightingboss = true; if you kill the boss set the isfighting boss to false again
        //     this->_currentSpeed = 0.0f;
        if (this->_isFightingBoss == false)
            this->_currentSpeed = this->_scrollSpeed;
        if (this->_mapQueue[i]._zPosition < (-20 - this->_mapQueue[i]._length)) {
            this->_mapQueue.erase(this->_mapQueue.begin());
        }
    }
}

void Map::refillMapQueue()
{
    mapQueueSection_t newMapSection;
    newMapSection._isBossRoom = false;
    int queueSize = this->getMapQueue().size();

    //test adding boss room
    if (queueSize == 2)
        this->_isFightingBoss = true;

    if (this->_isFightingBoss == false) { // this is the logic to add simple paths when not fighting a boss, so the infinite straight loop without anything else
        newMapSection._sectionName = this->_repeatPaths.at(this->_currentStage)._pathName;
        if (queueSize == 0) {
            newMapSection._zPosition = -20.0f;
            newMapSection._length = this->_repeatPaths.at(this->_currentStage)._length;
            this->_mapQueue.emplace_back(newMapSection);
        }
        else {
            newMapSection._zPosition = this->_mapQueue[queueSize - 1]._zPosition + this->_repeatPaths.at(this->_currentStage)._length;
            newMapSection._length = this->_repeatPaths.at(this->_currentStage)._length;
            this->_mapQueue.emplace_back(newMapSection);
        }
    }
    if (this->_isFightingBoss == true) {
        if (queueSize != 6 && this->_hasSpawnedBossroom == false) {
            newMapSection._sectionName = this->_bossRooms.at(this->_currentStage)._bossRoomName;
            newMapSection._zPosition = this->_mapQueue[queueSize - 1]._zPosition + this->_repeatPaths.at(this->_currentStage)._length;
            newMapSection._length = this->_bossRooms.at(this->_currentStage)._length;
            newMapSection._isBossRoom = true;
            this->_mapQueue.emplace_back(newMapSection);
            this->_hasSpawnedBossroom = true;
            return; //very important or we create one bossroom and one path on the same z!!!
        }
        if (queueSize < 6 && this->_hasSpawnedBossroom == true) {
            //here we add behind the boss room the simple paths of the next level;
            //debugging
            std::cout << "adding path after bossromm" << std::endl;
            //debugging end
            newMapSection._sectionName = this->_repeatPaths.at(this->_currentStage + 1)._pathName;
            if (this->_mapQueue[queueSize - 1]._isBossRoom == true) {
                newMapSection._zPosition = this->_mapQueue[queueSize - 1]._zPosition + this->_bossRooms.at(this->_currentStage)._length;
                newMapSection._length = this->_bossRooms.at(this->_currentStage)._length;
            } else {
                newMapSection._zPosition = this->_mapQueue[queueSize - 1]._zPosition + this->_repeatPaths.at(this->_currentStage)._length;
                newMapSection._length = this->_repeatPaths.at(this->_currentStage)._length;
            }

            //debugging
            std::cout << "new path z = " << newMapSection._zPosition << " and queue size = " << queueSize 
            << " and previous pos is = " << this->_mapQueue[queueSize - 1]._zPosition
            << " and bossroom at this current stage length is = " << this->_bossRooms.at(this->_currentStage)._length << std::endl;
            //debugging end
            this->_mapQueue.emplace_back(newMapSection);

        }
    }
}


//GETTERS

std::string Map::getMapName()
{
    return this->_mapName;
}

std::string Map::getBackgroundName()
{
    return this->_backgroundName;
}

std::vector<repeatPathData_t> Map::getMapPathsData()
{
    return this->_repeatPaths;
}

std::vector<bossRoomData_t> Map::getMapBossRoomData()
{
    return this->_bossRooms;
}

std::vector<mapQueueSection_t> Map::getMapQueue()
{
    return this->_mapQueue;
}

int Map::getCurrentStage()
{
    return this->_currentStage;
}

bool Map::getFightingBoss()
{
    return this->_isFightingBoss;
}

bool Map::getGameRunning()
{
    return this->_gameRunning;
}

//setters

void Map::setGameRunning()
{
    this->_gameRunning = !this->_gameRunning;
}