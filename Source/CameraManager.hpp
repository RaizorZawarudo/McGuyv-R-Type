/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** CameraManager
*/

#include "raylib.h"
#include "Drawable3D.hpp"

#pragma once

namespace RL {
    class CameraManager {
        public:
            CameraManager();
            ~CameraManager();

            void changeCameraPosition(Drawable3D* mapModelInQueueAtZero);

            //getter
            Camera getCamera();

        protected:
        private:
        Camera _ingameCamera;

    };
}