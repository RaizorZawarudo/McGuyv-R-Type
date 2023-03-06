/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawer
*/

#include "Renderer.hpp"

RL::Renderer::Renderer(std::string name)
{
    this->_name = name;
}

RL::Renderer::~Renderer()
{
}

void RL::Renderer::draw_text(std::string text, Color color, int x, int y, Font font, float size)
{
    //DrawText(text.c_str(), x, y, 20, color);

    //use this function when we get font handled
    DrawTextEx(font, text.c_str(), Vector2 {float(x), float(y)}, size, 2, color);
}

void RL::Renderer::draw_3D_model(Model model, Vector3 position, float scale, RL::ModelType ownerType, const PitchYawRoll *pYR)
{
    float yRotationAngle = 0;
    float pitch = DEG2RAD*pYR->pitch;
    float reyaw = DEG2RAD*pYR->yaw;
    float roll = DEG2RAD*pYR->roll;
    if (ownerType == RL::ModelType::SPACESHIP || ownerType == RL::ModelType::MCGUYVER)
        yRotationAngle = 180.0f;
    model.transform = MatrixRotateXYZ((Vector3){ pitch, reyaw ,roll });
    DrawModelEx(model, position, {0, 1, 0}, yRotationAngle, {scale, scale, scale}, WHITE);


}

void RL::Renderer::draw_2D_model(Texture2D texture, int x, int y)
{
    DrawTexture(texture, x, y, WHITE);
}

void RL::Renderer::drawBackground(std::shared_ptr<AssetManager> AssetManager, int currentLevel)
{
    draw_2D_model(AssetManager->getSpecificBackground(AssetManager->getMaps().at(currentLevel)->getBackgroundName())->getTexture() , 0 , 0);
        
}

void RL::Renderer::drawMap(Map* Map, Camera camera, std::shared_ptr<AssetManager> AssetManager)
{
    int size =  Map->getMapQueue().size();
    for (int i = 0; i < size ; i++) {
        // std::cout << "drawing at position : " << Map->getMapQueue().at(i)._zPosition << std::endl;
        DrawModelEx(AssetManager->getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getModel(),
                    (Vector3){0.0f, 0.0f , Map->getMapQueue().at(i)._zPosition}, {0.0f, 1.0f, 0.0f}, 0.0f,
                    (Vector3){AssetManager->getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getScale(),
                              AssetManager->getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getScale(),
                              AssetManager->getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getScale()},
                    WHITE);
    }
}

float RL::Renderer::translateCoordinatestoWorld(int pos, int borderSize)
{
    float newpos = pos - (borderSize / 2);
    if (borderSize % 2 == 0)
        newpos += 0.5;
    return newpos;
}


void RL::Renderer::clearBackground()
{
    ClearBackground(RAYWHITE);
}

void RL::Renderer::begin3DMode(Camera camera)
{
    BeginMode3D(camera);
}

void RL::Renderer::end3DMode()
{
    EndMode3D();
}

void RL::Renderer::beginDrawing()
{
    BeginDrawing();
}

void RL::Renderer::endDrawing()
{
    EndDrawing();
}