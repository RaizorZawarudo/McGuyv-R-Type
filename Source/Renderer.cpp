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

void RL::Renderer::draw_3D_model(Model model, float x, float y, float z)
{
    Vector3 position = { x, y, z };
    float scale = 0.1f;
    DrawModel(model, position, scale, WHITE);
    //DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, rotationangle, (Vector3){ 0.1f, 0.1f, 0.1f }, WHITE);

}

void RL::Renderer::draw_2D_model(Texture2D texture, int x, int y)
{
    DrawTexture(texture, x, y, WHITE);
}

void RL::Renderer::drawMap(Map* Map, Camera camera, AssetManager AssetManager)
{
    
    int size =  Map->getMapQueue().size();
    for (int i = 0; i < size ; i++) {
        DrawModelEx(AssetManager.getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getModel(),
                    (Vector3){0.0f, 0.0f , Map->getMapQueue().at(i)._zPosition}, {0.0f, 1.0f, 0.0f}, 0.0f,
                    (Vector3){AssetManager.getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getScale(),
                              AssetManager.getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getScale(),
                              AssetManager.getSpecificDrawableWithType(Map->getMapQueue().at(i)._sectionName, RL::ModelType::ZONE)->getScale()},
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