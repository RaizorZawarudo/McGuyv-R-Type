#include "raylib.h"
#include "AssetManager.hpp"
#include "Map.hpp"
#include "InputManager.hpp"
#include "Renderer.hpp"
#include "CameraManager.hpp"
#include "InputManager.hpp"

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
    // Camera camera = { {  -4.0f, 6.0f, -15.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 70.0f, CAMERA_PERSPECTIVE};
    RL::CameraManager cameraManager;
    RL::Renderer Renderer("BETATESTING");
    RL::InputManager InputManager("TESTINPUTMANAGER");

    AssetManager AssetManager;


    //here debug if implementation of maps work ,, then to do : priniting of maps ina loop way through the RENDERER :D 

    int ennemyIndex = 0;
    int spaceshipIndex = 0;
    int projectileIndex = 0;

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
    float ennemystartingpos = 15.0f;


    Image spacebackground = LoadImage("Source/Assets/SideWallTextures/space.png");
    ImageResize(&spacebackground, 1024, 768);
    Texture2D spacebackgroundText = LoadTextureFromImage(spacebackground);
    UnloadImage(spacebackground);


    
    float X = 800.0f;

    // AssetManager.getSpacecraftModels()[3]->setCurrentAnim(0);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //UPDATES SECTION
        AssetManager.getMaps().at(currLevel)->mapUpdate();
        cameraManager.changeCameraPosition(AssetManager.getSpecificDrawableWithType(AssetManager.getMaps().at(currLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));
        //not sure where record inputs goes
        InputManager.recordInputs();

        // std::cout << cameraManager.getCamera().position.x << "and y = "<< cameraManager.getCamera().position.y << "and z = "<< cameraManager.getCamera().position.z  << std::endl;
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(spacebackgroundText, 0 , 0 , WHITE);

            BeginMode3D(cameraManager.getCamera());

                //DRAW MODEL USING ASSET LIST FROM MANAGER 
                //TO BE ADDED IN THE RENDERER

                // DrawCube({0.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos}, 1.0f, 1.0f, 1.0f, RED);
                // DrawCube({-8.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos}, 1.0f, 1.0f, 1.0f, RED);
                // DrawCube({8.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos}, 1.0f, 1.0f, 1.0f, RED);

                //AssetManager.getSpacecraftModels()[3]->updateModelsAnimation();

                // DrawModelEx(AssetManager.getSpacecraftModels()[0]->getModel(),{0.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[1]->getModel(),{2.5f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[2]->getModel(),{5.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[3]->getModel(),{7.5f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                
                // DrawModelEx(AssetManager.getSpacecraftModels()[4]->getModel(),{-2.5f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[5]->getModel(),{-5.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[6]->getModel(),{-7.5f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[7]->getModel(),{0.0f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[8]->getModel(),{-2.5f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[9]->getModel(),{-5.0f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[10]->getModel(),{-7.5f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[11]->getModel(),{2.5f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[12]->getModel(),{5.0f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[14]->getModel(),{7.5f, 3.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[16]->getModel(),{0.0f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos - 3 }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[17]->getModel(),{-2.5f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos - 3 }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                
                // DrawModelEx(AssetManager.getSpacecraftModels()[6]->getModel(),{-7.5f, 1.0f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getSpacecraftModels()[7]->getModel(),{-0.0f, 2.5f, cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);


                if (InputManager.playerHasPressedKeyAsChar('p')) {
                    spaceshipIndex += 1;
                    if (spaceshipIndex == AssetManager.getSpacecraftModels().size() )
                        spaceshipIndex = 0;
                }

                DrawModelEx(AssetManager.getSpacecraftModels()[spaceshipIndex]->getModel(),{2.5f, 1.0f, cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                
                    
                if (InputManager.playerHasPressedKeyAsChar('e')) {
                    ennemyIndex += 1;
                    if (ennemyIndex == AssetManager.getEnnemyModels().size() )
                        ennemyIndex = 0;
                }
                    
                DrawModelEx(AssetManager.getEnnemyModels()[ennemyIndex]->getModel(),{-5.0f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);


                if (InputManager.playerHasPressedKeyAsChar('l')) {
                    projectileIndex += 1;
                    if (projectileIndex == AssetManager.getProjectileModels().size() )
                        projectileIndex = 0;
                }

                DrawModelEx(AssetManager.getProjectileModels()[projectileIndex]->getModel(),{0.0f, 1.0f,cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {1.0f, 1.0f, 1.0f}, WHITE);

                // DrawModelEx(AssetManager.getEnnemyModels()[1]->getModel(),{-0.0f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[2]->getModel(),{-2.5f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[3]->getModel(),{-5.0f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[4]->getModel(),{-7.5f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[5]->getModel(),{2.5f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[6]->getModel(),{0.0f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[7]->getModel(),{7.5f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[8]->getModel(),{-7.5f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[10]->getModel(),{0.0f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[11]->getModel(),{3.0f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[12]->getModel(),{-3.0f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[13]->getModel(),{-7.0f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 20 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[14]->getModel(),{0.0f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 40 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[15]->getModel(),{-2.5f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 40 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[16]->getModel(),{2.5f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 40 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[17]->getModel(),{5.0f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 40 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                // DrawModelEx(AssetManager.getEnnemyModels()[18]->getModel(),{-7.5f, 5.0f,cameraManager.getCamera().position.z + ennemystartingpos - 40 }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                
                Renderer.drawMap(Maps.at(currLevel), cameraManager.getCamera(), AssetManager);

                // DrawGrid(2000, 1.0f);        // Draw a grid

            EndMode3D();

            //Input queue must be popped
            InputManager.popInputs();

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

