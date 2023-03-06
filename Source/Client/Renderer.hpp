/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawer
*/

#pragma once

#include <raylib.h>
#include <iostream>
#include "Map.hpp"
#include "AssetManager.hpp"
#include "Components&Systems/Components.hpp"
#include "raymath.h"



// how does the drawer work :
//Drawer.clear()
//Drawer.begin_drawing()
//Drawer.begin_MODE()    MODE= 2D or 3D
//Drawer.draw_XXX
//Draweer.end_MODE()

namespace RL {
    class Renderer {
        public:
            Renderer(std::string name);
            ~Renderer();

            void clearBackground(); // Done on window no ?

            void drawBackground(std::shared_ptr<AssetManager> AssetManager, int currentLevel);
            void draw_3D_model(Model model, Vector3 position, float scale, RL::ModelType ownerType, const PitchYawRoll *pitchYawRoll);
            void draw_2D_model(Texture2D texture, int x, int y);

            //EDIT:: drawMap should only draw, map logic of scrolling and spawning mobs etc will be in the map class for better encapsulations
            void drawMap(Map* Map, Camera camera, std::shared_ptr<AssetManager> AssetManager); //should take map class as parameter, map class containing path and boosrooms (and transition rooms maybe if we do it)


            void draw_text(std::string text, Color color, int x, int y, Font font, float size); // temporary, should create text class with font and size

            float translateCoordinatestoWorld(int pos, int borderSize);

            void begin3DMode(Camera camera);
            void beginDrawing();
            void end3DMode();
            void endDrawing();

        private:
            std::string _name;
    };   
}
