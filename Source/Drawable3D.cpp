/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** Drawable3D
*/

#include "Drawable3D.hpp"

//how to create a 3d model : if it is not an animated 3d item ( aka not a character or a bomb), the modelPath
//and the animationPath should be set to ""
//the scale can be set to 1
//set type == RL::MODEL only if its an animated model / bomb. the powerups are RL::POWER, the walls are RL::WALL
//add this->_cameraFOV to 90.0f in order to see everything in BOSS MODE OR ELSE IT DOESNT WORK BABY
RL::Drawable3D::Drawable3D(RL::ModelType type, std::string name, std::string modelPath, std::string texturePath, std::string animationPath, float scale, std::string style, float length, float width, float height, Vector3 cameraPositionMcGuyv, float cameraFovMcGuyv, Vector3 velocity, int hp, float shootCD, std::string explosionname)
{
    this->_name = name;
    this->_type = type;
    this->_scale = scale;
    this->_style = style;
    this->_length = length;
    this->_width = width;
    this->_height = height;
    this->_cameraPositionMcGuyv = cameraPositionMcGuyv;
    this->_cameraFovMcGuyv = cameraFovMcGuyv;
    this->_velocity = velocity;
    this->_hp = hp;
    this->_shootCD = shootCD;
    this->_explosionname = explosionname;


    this->load3DModel(modelPath, texturePath, animationPath);
}

RL::Drawable3D::~Drawable3D()
{
    this->unloadAll();
}

//LOADING FROM FILES
void RL::Drawable3D::load3DModel( std::string modelPath, std::string texturePath, std::string animationPath)
{
    struct stat sb;

    if (texturePath != "0" && stat(texturePath.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");
    if (this->_imageLoaded == true)
        this->unloadAll();
    this->_model = LoadModel(modelPath.c_str());
    if (texturePath != "0") {
        this->_img = LoadImage(texturePath.c_str());
        this->_texture = LoadTextureFromImage(this->_img);
        SetMaterialTexture(&this->_model.materials[0], MATERIAL_MAP_DIFFUSE, this->_texture);
        UnloadImage(this->_img);
    }
    //HERE ADD LOAD ANIMATION, 
    loadAnimation(animationPath);
    this->_imageLoaded = true;
}







//


//DEPRECATED
void RL::Drawable3D::draw()
{
    //BeginDrawing();
//     if (this->_type == RL::ZONE)
//         DrawCubeTexture(this->_texture, this->_position, 1.0f, 1.0f, 1.0f, WHITE);
//     if (this->_type == RL::SPACESHIP) {
//         DrawModelEx(this->_model, this->_position, {0, 1, 0}, this->_rotationAngle, (Vector3) {this->_scale,this->_scale,this->_scale} , WHITE);
//         //DrawModel(this->_model, this->_position, this->_scale, WHITE);
//         //DrawSphere(this->_position, 0.5f, RED);
//     }
//     // if (this->_type == RL::POWERUP)
//     //     drawPower();  //here we implement the movement and rotation of the poweup and bouncy etc etc and smaller size etc etc
//     //EndDrawing();
// }

// // void RL::Drawable3D::drawPower()
// // {
// //     if (this->_position.y >= 0.59f && this->up == 0) {
// //         this->_position.y -= 0.01f;
// //         DrawCubeTexture(this->_texture, this->_position, 0.6f, 0.6f, 0.6f, WHITE);
// //         if (this->_position.y <= 0.6f)
// //             this->up = 1;
// //         }
// //     if (this->_position.y <= 1.41f && this->up == 1) {
// //         this->_position.y += 0.01f;
// //         DrawCubeTexture(this->_texture, this->_position, 0.6f, 0.6f, 0.6f, WHITE);
// //         if (this->_position.y >= 1.4f)
// //             this->up = 0;
// //         }

}


// //
// // ANIMATION
//
void RL::Drawable3D::loadAnimation(std::string path)
{
    if (path == "0")
        return;
    struct stat sb;

    if (stat(path.c_str(), &sb) == -1)
        throw std::invalid_argument("Asset path is invalid");
    if (S_ISDIR(sb.st_mode))
        throw std::invalid_argument("Asset path is a directory");

    if (_animationLoaded)
        this->unloadAnimation();
    this->_animations = LoadModelAnimations(path.c_str(), &this->_animCount);
    this->_animationLoaded = true;
    std::cout << this->_animCount << this->_animations[1].frameCount << std::endl;
}

void RL::Drawable3D::unloadAnimation()
{
    for (unsigned int i = 0; i < this->_animCount; i++)
        UnloadModelAnimation(this->_animations[i]);
    RL_FREE(this->_animations);
    this->_animationLoaded = false;
}

int RL::Drawable3D::updateModelsAnimation(int currFrame, int currAnim) // add int as parameter to set to the animation frame of the entity
{
    if (currFrame > this->_animations[currAnim].frameCount) {
        currFrame = 0;
    }
    UpdateModelAnimation(this->_model, this->_animations[currAnim], currFrame);
    return this->_animations[currAnim].frameCount;
}

void RL::Drawable3D::setCurrentAnim(int anim)
{
    // this->_currentAnim;

    if (anim >= this->_animCount) {
        std::cout << "Animation index invalid" << std::endl;
        return;
    }

    this->resetAnimSequence();
}

void RL::Drawable3D::resetAnimSequence()
{
    this->_currentFrame = 0;
}

int RL::Drawable3D::getCurrentAnim() const
{
    return this->_currentAnim;
}

void RL::Drawable3D::unloadAll()
{
    if (!this->_imageLoaded)
        return;
    UnloadImage(this->_img);
    UnloadTexture(this->_texture);
    this->_imageLoaded = false;
}

void RL::Drawable3D::resize(float newScale)
{
    this->_scale = newScale;
}

bool RL::Drawable3D::isImageLoaded() const
{
    return this->_imageLoaded;
}

void RL::Drawable3D::setTint(Color newTint)
{
    this->_tint = newTint;
}

void RL::Drawable3D::setRotation(float newRotation)
{
    this->_rotationAngle = newRotation;
}

 Texture2D RL::Drawable3D::getTexture()
 {
     return this->_texture;
 }

ModelAnimation *RL::Drawable3D::getAnimation()
{
    return this->_animations;
}

Model RL::Drawable3D::getModel()
{
    return this->_model;
}

std::string RL::Drawable3D::getName()
{
    return this->_name;
}

float RL::Drawable3D::getLength()
{
    return this->_length;
}

float RL::Drawable3D::getWidth()
{
    return this->_width;
}

float RL::Drawable3D::getHeight()
{
    return this->_height;
}

float RL::Drawable3D::getScale()
{
    return this->_scale;
}

Vector3 RL::Drawable3D::getCameraPositionMcGuyv()
{
    return this->_cameraPositionMcGuyv;
}

float RL::Drawable3D::getCameraFovMcGuyv()
{
    return this->_cameraFovMcGuyv;
}

Vector3 RL::Drawable3D::getVelocity()
{
    return this->_velocity;
}

int RL::Drawable3D::getHp()
{
    return this->_hp;
}

float RL::Drawable3D::getShootCD()
{
    return this->_shootCD;
}

std::string RL::Drawable3D::getExplosionName()
{
    return this->_explosionname;
}