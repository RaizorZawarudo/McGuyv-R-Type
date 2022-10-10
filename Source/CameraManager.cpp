/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** CameraManager
*/

#include "CameraManager.hpp"

RL::CameraManager::CameraManager()
{
    this->_ingameCamera = { {  -4.0f, 6.0f, -15.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 70.0f, CAMERA_PERSPECTIVE};
}

RL::CameraManager::~CameraManager()
{
}

void RL::CameraManager::changeCameraPosition(Drawable3D* mapModelInQueueAtZero)
{
    Vector3 newCamPos =  mapModelInQueueAtZero->getCameraPositionMcGuyv();
    this->_ingameCamera.position = newCamPos;
}

//getters

Camera RL::CameraManager::getCamera()
{
    return this->_ingameCamera;
}

