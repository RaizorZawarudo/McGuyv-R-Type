/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** AssetManager
*/


#include "CsvParser.hpp"
#include "AssetManager.hpp"
#include "Drawable3D.hpp"


AssetManager::AssetManager(EntityID currentClientID)
{
    this->_currentclientID = currentClientID;
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
    std::string effectsCSVPath = "Source/Assets/Models/Effects/Effects.csv";
    std::string powerUpCSVPath = "Source/Assets/Models/PowerUps/PowerUps.csv";
    std::string iconsUICSVPath = "Source/Assets/Icons/Icons.csv";
    std::string fontsCSVPath = "Source/Assets/Fonts/Fonts.csv";
    std::string obstacleWavesCSVPath = "Source/Assets/ObstacleWaves/obstacleWaves.csv";

    //load all fonts
    this->_fonts = loadAllFonts(fontsCSVPath);

    //load all backgrounds;
    this->_ingameBackgrounds = loadAllBackgrounds(mapBackgroundCSVPath);

    //load all Icons & IngameUI Elements
    this->_IconsUIelements = loadAllIcons(iconsUICSVPath);

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

    //load all effects ( like shield etc)
    this->_effectsModels3D = loadEffectModels3D(effectsCSVPath, RL::ModelType::EFFECT);

    //load all powerups
    this->_powerUpModels = loadPowerUpModels(powerUpCSVPath, RL::ModelType::POWERUP);

    //done

    //load all obstacleWaves
    this->_obstacleWaves = loadObstacleWaves(obstacleWavesCSVPath);

    //here we check if ostacle waves were properly loaded

    for (int i = 0; i < _obstacleWaves.size(); i++)
        std::cout << "WAVE NAME : " << _obstacleWaves[i].name << std::endl;

    //load all enemyWaves
    //this->_ennemyWaves = loadEnnemyWaves(ennemyWavesCSVPath)
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
                length = atof(parsedCsv[i][j].c_str());
            if (j == 7)
                width = atof(parsedCsv[i][j].c_str());
            if (j == 8)
                height = atof(parsedCsv[i][j].c_str());
            if (j == 9 && type == RL::ModelType::ZONE) {
                cameraPositionMcGuyv.x = atof(splitStr( parsedCsv[i][j], ";")[0].c_str());
                cameraPositionMcGuyv.y = atof(splitStr( parsedCsv[i][j], ";")[1].c_str());
                cameraPositionMcGuyv.z = atof(splitStr( parsedCsv[i][j], ";")[2].c_str());
            }
            else if (j == 9 && (type == RL::ModelType::PROJECTILE ||type == RL::ModelType::ENNEMY || type == RL::ModelType::SPACESHIP)) {
                velocity.x = atof(parsedCsv[i][j].c_str());
                velocity.y = velocity.x;
                velocity.z = velocity.x;
            }
            if (j == 10 && type == RL::ModelType::ZONE)
                cameraFovMcGuyv = atof(parsedCsv[i][j].c_str());    
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
                length = atof(parsedCsv[i][j].c_str());
            if (j == 7)
                width = atof(parsedCsv[i][j].c_str());
            if (j == 8)
                height = atof(parsedCsv[i][j].c_str());  
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
            if (j == 6)
                length = atof(parsedCsv[i][j].c_str());
            if (j == 7)
                width = atof(parsedCsv[i][j].c_str());
            if (j == 8)
                height = atof(parsedCsv[i][j].c_str()); 
        }
        //HERE WE CREATE A NEW 3D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable3D *newModel = new RL::Drawable3D(type , modelName, modelPath, texturePath, animationPath, scale, style, length, width, height, cameraPositionMcGuyv, cameraFovMcGuyv, velocity, hp, shootCD, explosionname);
       // std::cout<< "LOADING THIS MODEL : " << modelName << " " << style << " " << modelPath << " " << texturePath << " " << animationPath << " " << scale  << " " << std::endl;

        modelVector.emplace_back(newModel);
    }

    return modelVector;
}

std::vector<RL::Drawable3D*> AssetManager::loadEffectModels3D(const std::string &path, RL::ModelType type)
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
    float width = 0; // windowsize basically
    float height = 0; // window size basically
    std::string type;

    std::vector<RL::Drawable2D*> backgroundVector;


    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {;
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                backgroundName = parsedCsv[i][j];
            if (j == 1)
                backgroundPath = parsedCsv[i][j];
            if (j == 2)
                type = parsedCsv[i][j];
        }
        //HERE WE CREATE A NEW 2D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable2D *newbackgroundDrawable = new RL::Drawable2D(backgroundPath, backgroundName, width, height, type);       
        backgroundVector.push_back(newbackgroundDrawable);
    }
    return backgroundVector;
}

std::vector<RL::Drawable3D*> AssetManager::loadPowerUpModels(const std::string &path, RL::ModelType type)
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
        }
        //HERE WE CREATE A NEW 3D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable3D *newModel = new RL::Drawable3D(type , modelName, modelPath, texturePath, animationPath, scale, style, length, width, height, cameraPositionMcGuyv, cameraFovMcGuyv, velocity, hp, shootCD, explosionname);
       // std::cout<< "LOADING THIS MODEL : " << modelName << " " << style << " " << modelPath << " " << texturePath << " " << animationPath << " " << scale  << " " << std::endl;

        modelVector.emplace_back(newModel);
    }

    return modelVector;

}


std::vector<RL::Drawable2D*> AssetManager::loadAllIcons(const std::string &backgroundCSVPath)
{

    std::vector<std::vector<std::string>> parsedCsv = csvToTable(backgroundCSVPath);

    std::string iconName;
    std::string iconPath;
    float iconwidth;
    float iconheight;
    std::string type;

    std::vector<RL::Drawable2D*> iconVector;


    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {;
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                iconName = parsedCsv[i][j];
            if (j == 1)
                iconPath = parsedCsv[i][j];
            if (j == 2)
                iconwidth = atof(parsedCsv[i][j].c_str());
            if (j == 3)
                iconheight = atof(parsedCsv[i][j].c_str());
            if (j == 4)
                type = parsedCsv[i][j];
        }
        //HERE WE CREATE A NEW 2D MODEL WITH THE INFO AND ADD IT TO THE VECTOR
        RL::Drawable2D *newiconDrawable = new RL::Drawable2D(iconPath, iconName, iconwidth, iconheight, type);       
        iconVector.push_back(newiconDrawable);
    }
    return iconVector;
}

std::vector<Font> AssetManager::loadAllFonts(const std::string &fontCSVPath)
{
    std::vector<std::vector<std::string>> parsedCsv = csvToTable(fontCSVPath);

    std::string fontpath;
    Font newfont;
    std::vector<Font> fontVector;

    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 1)
                fontpath = parsedCsv[i][j];
        }
        newfont = LoadFontEx(fontpath.c_str(), 25, 0, 250);
        fontVector.push_back(newfont);
    }
    return fontVector;
}

std::vector<Wave_t> AssetManager::loadObstacleWaves(const std::string &obstacleWavesCSVPath)
{
    std::vector<std::vector<std::string>> parsedCsv = csvToTable(obstacleWavesCSVPath);
    Wave_t newWave;
    std::string waveData;
    std::vector<Wave_t> obstacleWaves;

    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {
        //HERE WE SEPARATE EACH cell of the csv into its designated value
        for (long unsigned int j = 0; j < parsedCsv[i].size(); j++) {
            if (j == 0)
                newWave.name = parsedCsv[i][j];
            if (j == 1)
                newWave.waveComponents = loadWaveData(parsedCsv[i][j]);
        }
        obstacleWaves.push_back(newWave);
    }
    return obstacleWaves;
}

std::vector<waveAsset_t> AssetManager::loadWaveData(const std::string &obstacleWaveDataCSVPath)
{
    std::vector<std::vector<std::string>> parsedCsv = csvToTable(obstacleWaveDataCSVPath);
    std::vector<waveAsset_t> waveComponents;

    //HERE WE PARSE THE WAVE DATA AND CREATE AN WAVE ENTITIY DEPENDING ON THE I J and name present in the cell
    for (long unsigned int i = 1; i < parsedCsv.size(); i++) {
        for (long unsigned int j = 1; j < parsedCsv[i].size(); j++) {
            if (parsedCsv[i][j] != "free")

                // std::cout << "there is " << parsedCsv[i][j] << " at position "<< i << " " << j << std::endl;
                 waveComponents.push_back(loadWaveAssetData(parsedCsv[i][j], i, j));
        }
    }
    return waveComponents;
}

int transformCSVintoGameCoords(int x)
{
    int a;
    switch (x)
    {
    case 1:
        a = 6;
        break;
    case 2:
        a = 5;
        break;
    case 3:
        a = 4;
        break;
    case 4:
        a = 3;
        break;
    case 5:
        a = 2;
        break;
    case 6:
        a = 1;
        break;
    default:
        break;
    }
    return a;
}

waveAsset_t AssetManager::loadWaveAssetData(std::string name, int i, int j)
{
    waveAsset_t newWaveAsset;

    newWaveAsset.codename = name;

    newWaveAsset.position.x = j - 8;
    newWaveAsset.position.y = transformCSVintoGameCoords(i);

    std::cout << "name : " << newWaveAsset.codename << " and position x : " << newWaveAsset.position.x << " and position y : " << newWaveAsset.position.y << std::endl;

    return newWaveAsset;
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

std::vector<RL::Drawable3D*> AssetManager::getEffectsModels3D()
{
    return this->_obstacleModels;
}

std::vector<RL::Drawable3D*> AssetManager::getPowerUpModels()
{
    return this->_powerUpModels;
}

std::vector<Map*> AssetManager::getMaps()
{
    return this->_maps;
}

std::vector<RL::Drawable2D*> AssetManager::getBackgrounds()
{
    return this->_ingameBackgrounds;
}

std::vector<RL::Drawable2D*> AssetManager::getUIelements()
{
    return this->_IconsUIelements;
}

std::vector<Font> AssetManager::getAllFonts()
{
    return this->_fonts;
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

    if (modelType == RL::ModelType::EFFECT) {
        for (int i = 0; i < this->_effectsModels3D.size(); i++) {
            if (modelName == this->_effectsModels3D.at(i)->getName())
                return this->_effectsModels3D.at(i);
        }
    }

    if (modelType == RL::ModelType::ENNEMY) {
        for (int i = 0; i < this->_ennemyModels.size(); i++) {
            if (modelName == this->_ennemyModels.at(i)->getName())
                return this->_ennemyModels.at(i);
        }
    }

    if (modelType == RL::ModelType::POWERUP) {
        for (int i = 0; i < this->_powerUpModels.size(); i++) {
            if (modelName == this->_powerUpModels.at(i)->getName())
                return this->_powerUpModels.at(i);
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

RL::Drawable2D* AssetManager::getSpecificIcon(std::string iconName)
{
    for (RL::Drawable2D* drawable : this->_IconsUIelements) {
        if (drawable->getName() == iconName)
            return drawable;
    }

}

int AssetManager::getCurrentMapBeingPlayed()
{
    return this->_currentLevelBeingPlayed;
}

EntityID AssetManager::getCurrentClientID()
{
    return this->_currentclientID;
}

int AssetManager::getLootRand()
{
    return this->_lootrand;
}


//Setters

void AssetManager::setCurrentMapBeingPlayed(int level)
{
    this->_currentLevelBeingPlayed = level;
}

void AssetManager::setLootRand(int rand)
{
    this->_lootrand = rand;
}