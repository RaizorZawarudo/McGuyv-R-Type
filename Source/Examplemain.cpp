#include "raylib.h"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "InputManager.hpp"
#include "Renderer.hpp"

// #include "Window.hpp"
// #include "CollisionManager.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    float screenWidth = 1024.0f;
    float screenHeight = 768.0f;
    // Initialization 
    InitWindow(screenWidth, screenHeight, "McGuyv´R-Type");
    //--------------------------------------------------------------------------------------
    Camera camera = { {  -4.0f, 6.0f, -15.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 70.0f, CAMERA_PERSPECTIVE};

    AssetManager AssetManager;
    RL::Renderer Renderer("BETATESTING");


    //here debug if implementation of maps work ,, then to do : priniting of maps ina loop way through the RENDERER :D 

    std::vector<Map*> Maps = AssetManager.getMaps();
    // for (int i = 0; i < Maps.size(); i++)    {
    //     std::cout << " MAP NAME : " << Maps.at(i)->getMapName() << std::endl;
    //     std::cout << Maps.at(i)->getMapPathsData().size() << std::endl;
    //     for (int j = 0; j < Maps.at(i)->getMapPathsData().size(); j++ ){
    //         std::cout << "path name :  " << Maps.at(i)->getMapPathsData().at(j)._pathName << std::endl;
    //         std::cout << "path length : " << Maps.at(i)->getMapPathsData().at(j)._length << std::endl;
    //         std::cout << "path width :  " << Maps.at(i)->getMapPathsData().at(j)._width << std::endl;
    //         std::cout << "path height :  " << Maps.at(i)->getMapPathsData().at(j)._height << std::endl;
    //     }
    // }
    

    //debugging of map data loading end

    //testing map queue

    int currLevel = 1;

    Maps.at(currLevel)->mapUpdate();
    Maps.at(currLevel)->setGameRunning();
    std::vector<mapQueueSection_t> currentMapQueue = Maps.at(currLevel)->getMapQueue();

    for (int j = 0; j < currentMapQueue.size(); j++) {
        std::cout << currentMapQueue[j]._sectionName << " at position " << currentMapQueue[j]._zPosition << std::endl;
    }


    float playerStartingPos = 8.0f;
    float ennemystartingpos = 20.0f;

    float alientunnelLenght = 300.0f; //936.0f;

    float alientunnelGap = 1.0f;
    Vector3 alienTunnelPos = { 0.0f, -0.0f, alientunnelLenght };
    Vector3 alienTunnelPos2 = { 0.0f, -0.0f, alientunnelLenght };


    Vector3 endWallSize = { 40.0f, 40.0f, 1.0f };
    Vector3 endWallPos = { 0.0f, 0.0f, 100.0f };




    
    // Image spacebackground = LoadImage("Source/Assets/SideWallTextures/space.png");
    // ImageResize(&spacebackground, 800, 600);
    // Texture2D spacebackgroundText = LoadTextureFromImage(spacebackground);
    // UnloadImage(spacebackground);

    // Model alienTunnelModel =  LoadModel("Source/Assets/Models/Zones/WideMountainPath/mountainsWide.obj");
    // Model alienTunnelModel2 = LoadModel("Source/Assets/Models/Zones/BigMountainPath/bigmountains.obj");


    // Model Heaven =  LoadModel("Source/Assets/Models/Spacecrafts/Heaven/Heaven.obj");
    // Texture2D HeavenText = LoadTexture("Source/Assets/Models/Spacecrafts/Heaven/HeavenTexture.png");
    // SetMaterialTexture(&Heaven.materials[0], MATERIAL_MAP_DIFFUSE, HeavenText);


    // Model Earth =  LoadModel("Source/Assets/Models/Spacecrafts/Earth/Earth2.obj");


    // std::cout << alienTunnelModel.materialCount << std::endl;


    
    float X = 800.0f;



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // camera.position.z += 2.90f;
        // camera.target.z += 2.90f;
        AssetManager.getMaps().at(currLevel)->mapUpdate();
        


        

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            // DrawTexture(spacebackgroundText, 0 , 0 , WHITE);

            BeginMode3D(camera);

                //DRAW MODEL USING ASSET LIST FROM MANAGER 
                //TO BE ADDED IN THE RENDERER

                DrawCube({0.0f, 1.0f, camera.position.z + playerStartingPos}, 1.0f, 1.0f, 1.0f, RED);
                DrawCube({-8.0f, 1.0f, camera.position.z + playerStartingPos}, 1.0f, 1.0f, 1.0f, RED);
                DrawCube({8.0f, 1.0f, camera.position.z + playerStartingPos}, 1.0f, 1.0f, 1.0f, RED);

                DrawCube({0.0f, 1.0f, X * 0.0f}, 1.0f, 1.0f, 1.0f,GREEN);
                DrawCube({0.0f, 1.0f, X * 1.0f}, 1.0f, 1.0f, 1.0f,GREEN);
                DrawCube({0.0f, 1.0f, X * 2.0f}, 1.0f, 1.0f, 1.0f,GREEN);
                DrawCube({0.0f, 1.0f, X * 3.0f}, 1.0f, 1.0f, 1.0f,GREEN);
                DrawCube({0.0f, 1.0f, X * 4.0f}, 1.0f, 1.0f, 1.0f,GREEN);
                DrawCube({0.0f, 1.0f, X * 5.0f}, 1.0f, 1.0f, 1.0f,GREEN);
                DrawCube({0.0f, 1.0f, X * 6.0f}, 1.0f, 1.0f, 1.0f,BLACK);

                //DrawModelEx(AssetManager.getSpacecraftModels()[1]->getModel(),{-0.0f, 1.0f, camera.position.z + playerStartingPos }, {0, 1, 0}, 0.0f, {0.3f, 0.3f, 0.3f}, WHITE);

                DrawModelEx(AssetManager.getEnnemyModels()[0]->getModel(),{-0.0f, 1.0f,camera.position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {3.0f, 3.0f, 3.0f}, WHITE);

                DrawModelEx(AssetManager.getEnnemyModels()[0]->getModel(),{-0.0f, 1.0f,camera.position.z + playerStartingPos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                
                // DrawModelEx(AssetManager.getZonesModels()[2]->getModel(),{-0.0f, 0.0f, 0.0f }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // for (int i = 0; i < 6; i++)
                //     DrawModelEx(AssetManager.getZonesModels()[2]->getModel(),{-0.0f, 0.0f, 160.0f + i * 160.0f }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                //     //zones indexes -2 always
                
                Renderer.drawMap(Maps.at(currLevel), camera, AssetManager);

                // DrawGrid(2000, 1.0f);        // Draw a grid

            EndMode3D();

            DrawFPS(10, 10);


        EndDrawing();
        //----------------------------------------------------------------------------------

        
       
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

