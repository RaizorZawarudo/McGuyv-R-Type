/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** CameraManager
*/

#include "CameraManager.hpp"

RL::CameraManager::CameraManager()
{
    this->_ingameCamera = { {  -4.0f, 6.0f, -15.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 90.0f, CAMERA_PERSPECTIVE};
}

RL::CameraManager::~CameraManager()
{
}

void RL::CameraManager::changeCameraPosition(Drawable3D* mapModelInQueueAtZero)
{
    Vector3 newCamPos =  mapModelInQueueAtZero->getCameraPositionMcGuyv();
    float newCamFov = mapModelInQueueAtZero->getCameraFovMcGuyv();
    changeCameraX(newCamPos);
    changeCameraY(newCamPos);
    changeCameraZ(newCamPos);
    changeCameraFov(newCamFov);

    // this->_ingameCamera.position = newCamPos;
}

void RL::CameraManager::changeCameraX(Vector3 newCamPos)
{
    if (newCamPos.x < this->_ingameCamera.position.x)
        this->_ingameCamera.position.x = ((this->_ingameCamera.position.x * 10) - 1)/10;
    else if (newCamPos.x > this->_ingameCamera.position.x)
        this->_ingameCamera.position.x = ((this->_ingameCamera.position.x * 10) + 1)/10;
}

void RL::CameraManager::changeCameraY(Vector3 newCamPos)
{
    if (newCamPos.y < this->_ingameCamera.position.y)
        this->_ingameCamera.position.y = ((this->_ingameCamera.position.y * 10) - 1)/10;
    else if (newCamPos.y > this->_ingameCamera.position.y)
        this->_ingameCamera.position.y = ((this->_ingameCamera.position.y * 10) + 1)/10;   
}

void RL::CameraManager::changeCameraZ(Vector3 newCamPos)
{
    if (newCamPos.z < this->_ingameCamera.position.z)
        this->_ingameCamera.position.z = ((this->_ingameCamera.position.z * 10) - 1)/10;
    else if (newCamPos.z > this->_ingameCamera.position.z)
        this->_ingameCamera.position.z = ((this->_ingameCamera.position.y * 10) + 1)/10;   
}

void RL::CameraManager::changeCameraFov(float newCamFov)
{
    if (newCamFov < this->_ingameCamera.fovy)
        this->_ingameCamera.fovy = ((this->_ingameCamera.fovy * 10) - 1)/10;
    else if (newCamFov > this->_ingameCamera.fovy)
        this->_ingameCamera.fovy = ((this->_ingameCamera.fovy * 10) + 1)/10;   
}

//getters

Camera RL::CameraManager::getCamera()
{
    return this->_ingameCamera;
}

