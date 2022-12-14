#include "McGuyverType.hpp"
// #include "CollisionManager.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int counter;
int main(void)
{
    McGuyverType Game;

    Game.startGame();

    return 0;

}
    // float screenWidth = 1024.0f;
    // float screenHeight = 768.0f;
    // // Initialization 
    // // InitWindow(screenWidth, screenHeight, "McGuyv´R-Type");

    // //--------------------------------------------------------------------------------------
    // // Camera camera = { {  -4.0f, 6.0f, -15.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 70.0f, CAMERA_PERSPECTIVE};
    // RL::Window windowManager("McGuyv R-Type");
    // RL::CameraManager cameraManager;
    // RL::Renderer Renderer("BETATESTING");
    // RL::InputManager InputManager("TESTINPUTMANAGER");

    // AssetManager AssetManager;


    // //here debug if implementation of maps work ,, then to do : priniting of maps ina loop way through the RENDERER :D 

    // int ennemyIndex = 0;
    // int spaceshipIndex = 0;
    // int projectileIndex = 0;

    // std::vector<Map*> Maps = AssetManager.getMaps();
    // // for (int i = 0; i < Maps.size(); i++)    {
    // //     std::cout << " MAP NAME : " << Maps.at(i)->getMapName() << std::endl;
    // //     std::cout << Maps.at(i)->getMapPathsData().size() << std::endl;
    // //     for (int j = 0; j < Maps.at(i)->getMapPathsData().size(); j++ ){
    // //         std::cout << "path name :  " << Maps.at(i)->getMapPathsData().at(j)._pathName << std::endl;
    // //         std::cout << "path length : " << Maps.at(i)->getMapPathsData().at(j)._length << std::endl;
    // //         std::cout << "path width :  " << Maps.at(i)->getMapPathsData().at(j)._width << std::endl;
    // //         std::cout << "path height :  " << Maps.at(i)->getMapPathsData().at(j)._height << std::endl;
    // //     }
    // // }
    

    // //debugging of map data loading end

    // //testing map queue

    // int currLevel = 1;

    // Maps.at(currLevel)->mapUpdate();
    // Maps.at(currLevel)->setGameRunning();
    // std::vector<mapQueueSection_t> currentMapQueue = Maps.at(currLevel)->getMapQueue();

    // for (int j = 0; j < currentMapQueue.size(); j++) {
    //     std::cout << currentMapQueue[j]._sectionName << " at position " << currentMapQueue[j]._zPosition << std::endl;
    // }


    // float playerStartingPos = 8.0f;
    // float ennemystartingpos = 15.0f;


    // Image spacebackground = LoadImage("Source/Assets/SideWallTextures/space.png");
    // ImageResize(&spacebackground, 1024, 768);
    // Texture2D spacebackgroundText = LoadTextureFromImage(spacebackground);
    // UnloadImage(spacebackground);


    
    // float X = 800.0f;

    // // AssetManager.getSpacecraftModels()[3]->setCurrentAnim(0);

    // SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // //--------------------------------------------------------------------------------------

    // // Main game loop
    // // while (windowManager.checkWindowOpen())
    // while (windowManager.checkWindowOpen())    // Detect window close button or ESC key
    // {
    //     //UPDATES SECTION
    //     AssetManager.getMaps().at(currLevel)->mapUpdate();
    //     cameraManager.changeCameraPosition(AssetManager.getSpecificDrawableWithType(AssetManager.getMaps().at(currLevel)->getMapQueue().at(0)._sectionName, RL::ModelType::ZONE));
    //     //not sure where record inputs goes
    //     InputManager.recordInputs();

    //     // std::cout << cameraManager.getCamera().position.x << "and y = "<< cameraManager.getCamera().position.y << "and z = "<< cameraManager.getCamera().position.z  << std::endl;
    //     //----------------------------------------------------------------------------------
    //     // Draw
    //     //----------------------------------------------------------------------------------
    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);
    //         DrawTexture(spacebackgroundText, 0 , 0 , WHITE);

    //         BeginMode3D(cameraManager.getCamera());

    //             //DRAW MODEL USING ASSET LIST FROM MANAGER 
    //             //TO BE ADDED IN THE RENDERER

    //             if (InputManager.playerHasPressedKeyAsChar('p')) {
    //                 spaceshipIndex += 1;
    //                 if (spaceshipIndex == AssetManager.getSpacecraftModels().size() )
    //                     spaceshipIndex = 0;
    //             }

    //             DrawModelEx(AssetManager.getSpacecraftModels()[spaceshipIndex]->getModel(),{2.5f, 1.0f, cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                
                    
    //             if (InputManager.playerHasPressedKeyAsChar('e')) {
    //                 ennemyIndex += 1;
    //                 if (ennemyIndex == AssetManager.getEnnemyModels().size() )
    //                     ennemyIndex = 0;
    //             }
                    
    //             DrawModelEx(AssetManager.getEnnemyModels()[ennemyIndex]->getModel(),{-5.0f, 1.0f,cameraManager.getCamera().position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);


    //             if (InputManager.playerHasPressedKeyAsChar('l')) {
    //                 projectileIndex += 1;
    //                 if (projectileIndex == AssetManager.getProjectileModels().size() )
    //                     projectileIndex = 0;
    //             }

    //             DrawModelEx(AssetManager.getProjectileModels()[projectileIndex]->getModel(),{0.0f, 1.0f,cameraManager.getCamera().position.z + playerStartingPos }, {0, 1, 0}, 180.0f, {4.0f,4.0f, 4.0f}, WHITE);

    //             Renderer.drawMap(Maps.at(currLevel), cameraManager.getCamera(), AssetManager);

    //             // DrawGrid(2000, 1.0f);        // Draw a grid

    //         EndMode3D();

    //         //Input queue must be popped
    //         InputManager.popInputs();

    //         DrawFPS(10, 10);


    //     EndDrawing();
    //     //---------------------------------------------------------------------------------- 
    // }

    // // De-Initialization
    // //--------------------------------------------------------------------------------------
    // windowManager.close();        // Close window and OpenGL context
    // //--------------------------------------------------------------------------------------

    // return 0;
// }

