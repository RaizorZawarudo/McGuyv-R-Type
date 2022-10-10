/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#pragma once

#include <iostream>
#include <raylib.h>
#include <string>
#include <stdexcept>
#include <sys/stat.h>

#include "IDrawable.hpp"
#include "CsvParser.hpp"
//#include "RaylibTypeEncaps.hpp"
    
namespace RL {
    enum ModelType {
        MCGUYVER,
        ZONE,
        SPACESHIP,
        PROJECTILE,
        ENNEMY,
        OSTACLE,
        POWERUP
    };


    class Drawable3D: public IDrawable {
        public:
            Drawable3D(RL::ModelType type, std::string name, std::string modelPath, std::string texturePath, std::string animationPath, float scale, std::string style, float lenght, float width, float height, Vector3 cameraPositionMcGuyv, float cameraFovMcGuyv);
            ~Drawable3D();

            // IDrawable methods
            void draw();
            void drawPower();
            // void reset();

            // Image Loading / Manipulation methods
            void load3DModel(std::string texturePath, std::string modelPath, std::string animationPath);
            void unloadAll();
            void resize(float newScale);

            // Animation
            void loadAnimation(std::string path);
            void unloadAnimation();
            void updateModelsAnimation();
            void resetAnimSequence();
            void setCurrentAnim(int anim);
            int getCurrentAnim() const;

            bool isAnimLoaded() const;

            // Getters and setters
            bool isImageLoaded() const;
            void setTint(Color newTint);
            void setRotation(float newRotation);

            void setPosition(float x, float y, float z);
            Vector3 getPosition();

            Vector3 getBoxSize();

            Texture2D getTexture();

            ModelAnimation* getAnimation();

            Model getModel();
            std::string getName();
            float getLength();
            float getWidth();
            float getHeight();
            float getScale();
            Vector3 getCameraPositionMcGuyv();
            float getCameraFovMcGuyv();

            void setBoundingBox();
            BoundingBox getBoundingBox();

        protected:

            ModelType _type;
            std::string _name;
            std::string _style;
            Color _tint = WHITE;
            float _scale;
            Model _model;
            float _length;
            float _width;
            float _height;
            Vector3 _cameraPositionMcGuyv;
            float _cameraFovMcGuyv;

            Vector3 _boxSize;
            BoundingBox _boundingBox;
            // These initializations will not work
            Vector3 _position = {0, 0, 0}; //useless do not add position in the model, add position in the entity data
            
            
            bool _imageLoaded = false;
            Image _img;
            Texture2D _texture;
            int up;

             // Animation
            ModelAnimation *_animations;
            int _currentAnim = 0;
            int _currentFrame = 0;
            unsigned int _animCount;
            bool _animationLoaded = false;
            float _rotationAngle = 0.0f;
    };
}