/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** AssetManager
*/


#include "CsvParser.hpp"
#include "AssetManager.hpp"
#include "Drawable3D.hpp"


AssetManager::AssetManager()
{
    loadAllModels();
    
    //load all maps ( maps is the data structure which contains the matching paths to be linked together to create the world
    // ex : mountainsPath + big mountainpath + mountainboss room + big mountain boss room

    loadAllMaps();


}

AssetManager::~AssetManager()
{
}

void AssetManager::loadAllModels()
{
    std::string zonesModelCSVPath = "Source/Assets/Models/Zones/Zones.csv";
    std::string spacecraftModelCSVPath = "Source/Assets/Models/Spacecrafts/Spacecrafts.csv";
    std::string ennemyModelCSVPath = "Source/Assets/Models/Ennemies/Ennemies.csv";

    //load all zones
    this->_zonesModels = loadModels(zonesModelCSVPath, RL::ModelType::ZONE);
    
    //load all spacecrafts
    this->_spacecraftModels = loadModels(spacecraftModelCSVPath, RL::ModelType::SPACESHIP);


    //load all projectiles


    //load all ennemies
    this->_ennemyModels = loadModels(ennemyModelCSVPath, RL::ModelType::ENNEMY);

    //load all obstacles

    //done
}

std::vector<RL::Drawable3D*> AssetManager::loadModels(const std::string &path, RL::ModelType type)
{
    std::string modelName;
    std::string style;
    std::string modelPath;
    std::string texturePath;
    std::string animationPath;
    float scale;
    float length;
    float width;
    float height;
    Vector3 cameraPositionMcGuyv;

    std::vector<std::vector<std::string>> parsedCsv = csvToTable(path);
    std::vector<RL::Drawable3D*> modelVector;

    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {;
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                modelName = parsedCsv[i][j];
            if (j == 1)
                style = parsedCsv[i][j];
            if (j == 2)
                modelPath = parsedCsv[i][j];
            if (j == 3)
                texturePath = parsedCsv[i][j];
            if ( j == 4)
                animationPath = parsedCsv[i][j];
            if (j == 5)
                scale = atoi(parsedCsv[i][j].c_str());
            if (j == 6)
                length = atoi(parsedCsv[i][j].c_str());
            if (j == 7)
                width = atoi(parsedCsv[i][j].c_str());
            if (j ==8)
                height = atoi(parsedCsv[i][j].c_str());
            if (j == 9) {
                cameraPositionMcGuyv.x = atoi(splitStr( parsedCsv[i][j], ";")[0].c_str());
                cameraPositionMcGuyv.y = atoi(splitStr( parsedCsv[i][j], ";")[1].c_str());
                cameraPositionMcGuyv.z = atoi(splitStr( parsedCsv[i][j], ";")[2].c_str());
            }
                

        }
        //HERE WE CREATE A NEW 3D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable3D *newModel = new RL::Drawable3D(type , modelName, modelPath, texturePath, animationPath, scale, style, length, width, height, cameraPositionMcGuyv);
       // std::cout<< "LOADING THIS MODEL : " << modelName << " " << style << " " << modelPath << " " << texturePath << " " << animationPath << " " << scale  << " " << std::endl;

        modelVector.emplace_back(newModel);
    }

    return modelVector;
}

void AssetManager::loadAllMaps()
{
    std::string allMapsCSVPath = "Source/Maps/maps.csv";

    std::vector<std::vector<std::string>> parsedCsv = csvToTable(allMapsCSVPath);

    std::string mapName;
    std::string mapPath;


    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {;
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                mapName = parsedCsv[i][j];
            if (j == 1)
                mapPath = parsedCsv[i][j];
        }

        //debugging
        std::cout << "MAP NAME = " << mapName << " and MAP PATH = " << mapPath << std::endl; // debugging line
        //now we crate a map from each map line in the map .csv
        Map *newMap = new Map(mapName, mapPath, this->_zonesModels);
        this->_maps.emplace_back(newMap);
    //done
    }
    //debugging
    std::cout << " BIG DEBUG ::  2 == " << this->_maps.size() << std::endl;
}

//Getters

std::vector<RL::Drawable3D*> AssetManager::getSpacecraftModels()
{
    return this->_spacecraftModels;
}

std::vector<RL::Drawable3D*> AssetManager::getZonesModels()
{
    return this->_zonesModels;
}
std::vector<RL::Drawable3D*> AssetManager::getProjectileModels()
{
    return this->_projectileModels;
}

std::vector<RL::Drawable3D*> AssetManager::getEnnemyModels()
{
    return this->_ennemyModels;
}

std::vector<Map*> AssetManager::getMaps()
{
    return this->_maps;
}

