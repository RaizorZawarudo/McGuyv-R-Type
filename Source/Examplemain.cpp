#include "raylib.h"
#include "AssetManager.hpp"
//#include "Map.hpp"
#include "InputManager.hpp"

// #include "Window.hpp"
// #include "CollisionManager.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    float screenWidth = 800.0f;
    float screenHeight = 600.0f;
    InitWindow(screenWidth, screenHeight, "raylib [models] example - box collisions");
    // Initialization
    //--------------------------------------------------------------------------------------

    AssetManager AssetManager;
    std::vector<Map*> Maps = AssetManager.getMaps();
    // std::vect;

    //here debug if implementation of maps work ,, then to do : priniting of maps ina loop way through the RENDERER :D 

    for (int i = 0; i < Maps.size(); i++)    {
        std::cout << " MAP NAME : " << Maps.at(i)->getMapName() << std::endl;
        std::cout << Maps.at(i)->getMapPathsData().size() << std::endl;
        for (int j = 0; j < Maps.at(i)->getMapPathsData().size(); j++ ){
            std::cout << "path name :  " << Maps.at(i)->getMapPathsData().at(j)._pathName << std::endl;
            std::cout << "path length : " << Maps.at(i)->getMapPathsData().at(j)._length << std::endl;
            std::cout << "path width :  " << Maps.at(i)->getMapPathsData().at(j)._width << std::endl;
            std::cout << "path height :  " << Maps.at(i)->getMapPathsData().at(j)._height << std::endl;
        }
    }


    float playerStartingPos = 8.0f;
    float ennemystartingpos = 20.0f;

    float alientunnelLenght = 300.0f; //936.0f;

    float alientunnelGap = 1.0f;
    Vector3 alienTunnelPos = { 0.0f, -0.0f, alientunnelLenght };
    Vector3 alienTunnelPos2 = { 0.0f, -0.0f, alientunnelLenght };


    Vector3 endWallSize = { 40.0f, 40.0f, 1.0f };
    Vector3 endWallPos = { 0.0f, 0.0f, 100.0f };


    Camera camera = { {  -5.0f, 6.0f, 0.0f }, { 0.0f, 0.0f, 15.0f }, { 0.0f, 1.0f, 0.0f }, 70.0f, CAMERA_PERSPECTIVE};


    
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


    
    float X = 0.0f;



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        camera.position.z += 0.20f;
        camera.target.z += 0.20f;
        X += 0.02f;
        


        

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

                //DrawModelEx(AssetManager.getSpacecraftModels()[1]->getModel(),{-0.0f, 1.0f, camera.position.z + playerStartingPos }, {0, 1, 0}, 0.0f, {0.3f, 0.3f, 0.3f}, WHITE);

                DrawModelEx(AssetManager.getEnnemyModels()[0]->getModel(),{-0.0f, 1.0f,camera.position.z + ennemystartingpos }, {0, 1, 0}, 0.0f, {3.0f, 3.0f, 3.0f}, WHITE);

                DrawModelEx(AssetManager.getEnnemyModels()[0]->getModel(),{-0.0f, 1.0f,camera.position.z + playerStartingPos }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                  
                for (int i = 0; i < 6; i++)
                    DrawModelEx(AssetManager.getZonesModels()[2]->getModel(),{-0.0f, 0.0f, 160.0f + i * 160.0f }, {0, 1, 0}, 0.0f, {1.0f, 1.0f, 1.0f}, WHITE);
                    //zones indexes -2 always



                //DrawGrid(2000, 1.0f);        // Draw a grid

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

