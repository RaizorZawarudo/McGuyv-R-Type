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
    std::string projectileCSVPath = "Source/Assets/Models/Projectiles/Projectiles.csv";
    std::string mapBackgroundCSVPath = "Source/Assets/BackgroundTextures/Backgrounds.csv";
    std::string obstacleCSVPath = "Source/Assets/Models/Obstacles/Obstacles.csv";
    std::string explosionCSVPath = "Source/Assets/Models/Explosions/Explosions.csv";

    //load all backgrounds;
    this->_ingameBackgrounds = loadAllBackgrounds(mapBackgroundCSVPath);

    //load all zones
    this->_zonesModels = loadModels(zonesModelCSVPath, RL::ModelType::ZONE);
    
    //load all spacecrafts
    this->_spacecraftModels = loadModels(spacecraftModelCSVPath, RL::ModelType::SPACESHIP);


    //load all projectiles
    this->_projectileModels= loadModels(projectileCSVPath, RL::ModelType::PROJECTILE);


    //load all ennemies
    this->_ennemyModels = loadModels(ennemyModelCSVPath, RL::ModelType::ENNEMY);

    //load all obstacles
    this->_obstacleModels = loadObstacleModels(obstacleCSVPath, RL::ModelType::OBSTACLE);

    //load all exposions , they have animation !!
    this->_explosionModelsAnim = loadExplosionModels(explosionCSVPath, RL::ModelType::EXPLOSION);

    //load all powerups

    //done
}

std::vector<RL::Drawable3D*> AssetManager::loadModels(const std::string &path, RL::ModelType type)
{
    std::string modelName;
    std::string style;
    std::string modelPath;
    std::string texturePath;
    std::string animationPath;
    float scale = 1;
    float length= 1;
    float width = 1;
    float height = 1;
    Vector3 cameraPositionMcGuyv = {0, 0, 0};
    float cameraFovMcGuyv;
    Vector3 velocity = {0, 0, 0};
    int hp = 0;
    float shootCD = 0;
    std::string explosionname;

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
                scale = atof(parsedCsv[i][j].c_str());
            if (j == 6)
                length = atoi(parsedCsv[i][j].c_str());
            if (j == 7)
                width = atoi(parsedCsv[i][j].c_str());
            if (j == 8)
                height = atoi(parsedCsv[i][j].c_str());
            if (j == 9 && type == RL::ModelType::ZONE) {
                cameraPositionMcGuyv.x = atoi(splitStr( parsedCsv[i][j], ";")[0].c_str());
                cameraPositionMcGuyv.y = atoi(splitStr( parsedCsv[i][j], ";")[1].c_str());
                cameraPositionMcGuyv.z = atoi(splitStr( parsedCsv[i][j], ";")[2].c_str());
            }
            else if (j == 9 && (type == RL::ModelType::PROJECTILE ||type == RL::ModelType::ENNEMY || type == RL::ModelType::SPACESHIP)) {
                velocity.x = atof(parsedCsv[i][j].c_str());
                velocity.y = velocity.x;
                velocity.z = velocity.x;
            }
            if (j == 10 && type == RL::ModelType::ZONE)
                cameraFovMcGuyv = atoi(parsedCsv[i][j].c_str());    
            else if (j == 10 && (type == RL::ModelType::PROJECTILE ||type == RL::ModelType::ENNEMY || type == RL::ModelType::SPACESHIP))
                hp = atoi(parsedCsv[i][j].c_str());

            if (j == 11 && type == RL::ModelType::PROJECTILE) {
                shootCD = atof(parsedCsv[i][j].c_str());
            }
            else if (j == 11 && (type == RL::ModelType::ENNEMY || type == RL::ModelType::SPACESHIP)) {
                explosionname = parsedCsv[i][j].c_str();
            }
            if (j == 12 && type == RL::ModelType::PROJECTILE) {
                explosionname = parsedCsv[i][j].c_str();
            }



        }
        //HERE WE CREATE A NEW 3D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable3D *newModel = new RL::Drawable3D(type , modelName, modelPath, texturePath, animationPath, scale, style, length, width, height, cameraPositionMcGuyv, cameraFovMcGuyv, velocity, hp, shootCD, explosionname);
       // std::cout<< "LOADING THIS MODEL : " << modelName << " " << style << " " << modelPath << " " << texturePath << " " << animationPath << " " << scale  << " " << std::endl;

        modelVector.emplace_back(newModel);
    }

    return modelVector;
}

std::vector<RL::Drawable3D*> AssetManager::loadObstacleModels(const std::string &path, RL::ModelType type)
{
    std::string modelName;
    std::string style;
    std::string modelPath;
    std::string texturePath;
    std::string animationPath;
    float scale = 1;
    float length= 1;
    float width = 1;
    float height = 1;
    Vector3 velocity = {0, 0, 0};
    Vector3 cameraPositionMcGuyv = {0, 0, 0};
    float cameraFovMcGuyv;
    int hp = 0;
    float shootCD = 0;
    std::string explosionname;

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
                scale = atof(parsedCsv[i][j].c_str());
            if (j == 6)
                length = atoi(parsedCsv[i][j].c_str());
            if (j == 7)
                width = atoi(parsedCsv[i][j].c_str());
            if (j == 8)
                height = atoi(parsedCsv[i][j].c_str());  
            if (j == 9 && type)
                hp = atoi(parsedCsv[i][j].c_str());
            if (j == 10)
                explosionname = parsedCsv[i][j];

        }
        //HERE WE CREATE A NEW 3D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable3D *newModel = new RL::Drawable3D(type , modelName, modelPath, texturePath, animationPath, scale, style, length, width, height, cameraPositionMcGuyv, cameraFovMcGuyv, velocity, hp, shootCD, explosionname);
       // std::cout<< "LOADING THIS MODEL : " << modelName << " " << style << " " << modelPath << " " << texturePath << " " << animationPath << " " << scale  << " " << std::endl;

        modelVector.emplace_back(newModel);
    }

    return modelVector;
}

std::vector<RL::Drawable3D*> AssetManager::loadExplosionModels(const std::string &path, RL::ModelType type)
{
    std::string modelName;
    std::string style;
    std::string modelPath;
    std::string texturePath;
    std::string animationPath;
    float scale = 1;
    float length= 1;
    float width = 1;
    float height = 1;
    Vector3 velocity = {0, 0, 0};
    Vector3 cameraPositionMcGuyv = {0, 0, 0};
    float cameraFovMcGuyv;
    int hp = 0;
    float shootCD = 0;
    std::string explosionname;

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
                scale = atof(parsedCsv[i][j].c_str());
        }
        //HERE WE CREATE A NEW 3D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable3D *newModel = new RL::Drawable3D(type , modelName, modelPath, texturePath, animationPath, scale, style, length, width, height, cameraPositionMcGuyv, cameraFovMcGuyv, velocity, hp, shootCD, explosionname);
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
    std::string backgroundName;


    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {;
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                mapName = parsedCsv[i][j];
            if (j == 1)
                mapPath = parsedCsv[i][j];
            if (j == 2)
                backgroundName = parsedCsv[i][j];
        }

        //debugging
        // std::cout << "MAP NAME = " << mapName << " and MAP PATH = " << mapPath << std::endl; // debugging line

        //now we crate a map from each map line in the map .csv
        Map *newMap = new Map(mapName, mapPath, this->_zonesModels, backgroundName);
        this->_maps.emplace_back(newMap);
    //done
    }
    //debugging
    // std::cout << " BIG DEBUG ::  2 == " << this->_maps.size() << std::endl;
}


std::vector<RL::Drawable2D*> AssetManager::loadAllBackgrounds(const std::string &backgroundCSVPath)
{

    std::vector<std::vector<std::string>> parsedCsv = csvToTable(backgroundCSVPath);

    std::string backgroundName;
    std::string backgroundPath;

    std::vector<RL::Drawable2D*> backgroundVector;


    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {;
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                backgroundName = parsedCsv[i][j];
            if (j == 1)
                backgroundPath = parsedCsv[i][j];
        }
        //HERE WE CREATE A NEW 2D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable2D *newbackgroundDrawable = new RL::Drawable2D(backgroundPath, backgroundName);       
        backgroundVector.push_back(newbackgroundDrawable);
    }
    return backgroundVector;
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

std::vector<RL::Drawable3D*> AssetManager::getObstacleModels()
{
    return this->_obstacleModels;
}

std::vector<Map*> AssetManager::getMaps()
{
    return this->_maps;
}

std::vector<RL::Drawable2D*> AssetManager::getBackgrounds()
{
    return this->_ingameBackgrounds;
}

RL::Drawable2D* AssetManager::getSpecificBackground(std::string backgroundName)
{
    for (RL::Drawable2D* drawable : this->_ingameBackgrounds) {
        if (drawable->getName() == backgroundName)
            return drawable;
    }
}

RL::Drawable3D* AssetManager::getSpecificDrawableWithType(std::string modelName, RL::ModelType modelType)
{
    if (modelType == RL::ModelType::ZONE) {
        for (int i = 0; i < this->_zonesModels.size(); i++) {
            if (modelName == this->_zonesModels.at(i)->getName())
                return this->_zonesModels.at(i);
        }
    }

    if (modelType == RL::ModelType::SPACESHIP) {
        for (int i = 0; i < this->_spacecraftModels.size(); i++) {
            if (modelName == this->_spacecraftModels.at(i)->getName())
                return this->_spacecraftModels.at(i);
        }
    }

    if (modelType == RL::ModelType::PROJECTILE) {
        for (int i = 0; i < this->_projectileModels.size(); i++) {
            if (modelName == this->_projectileModels.at(i)->getName())
                return this->_projectileModels.at(i);
        }
    }

    if (modelType == RL::ModelType::OBSTACLE) {
        for (int i = 0; i < this->_obstacleModels.size(); i++) {
            if (modelName == this->_obstacleModels.at(i)->getName())
                return this->_obstacleModels.at(i);
        }
    }

    if (modelType == RL::ModelType::EXPLOSION) {
        for (int i = 0; i < this->_explosionModelsAnim.size(); i++) {
            if (modelName == this->_explosionModelsAnim.at(i)->getName())
                return this->_explosionModelsAnim.at(i);
        }
    }

        //find in ZONES
    // if (modelType == 1)
    //     //find in ZONES
    // if (modelType == 1)
    //     //find in ZONES
    // if (modelType == 1)
    //     //find in ZONES
    // if (modelType == 1)
    //     //find in ZONES
    // if (modelType == 1)
    //     //find in ZONES

}

int AssetManager::getCurrentMapBeingPlayed()
{
    return this->_currentLevelBeingPlayed;
}


//Setters

void AssetManager::setCurrentMapBeingPlayed(int level)
{
    this->_currentLevelBeingPlayed = level;
}