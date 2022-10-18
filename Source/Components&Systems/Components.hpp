/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Components
*/

#pragma once

#include <memory>
#include <vector>
#include "deque"

#include "../Drawable3D.hpp"
#include "../ECS/ECS.hpp"


enum PlayerNumber {
    One = 0,
    Two = 1,
    Three = 2,
    Four = 4,
};

enum EntityType {
    MCGUYVER,
    PLAYER,
    ENNEMY,
    PROJECTILE,
    OBSTACLE,
    POWERUP
};

struct EntityModelType {
    RL::ModelType modelType;

};

enum UserInput {
    SHOOT = 10,
    FIRSTWEAPON = 49,
    SECONDWEAPON = 50,
    THIRDWEAPON = 51,
    UP = 122,
    LEFT = 113,
    DOWN = 115,
    RIGHT = 100,
    FORWARD = 32,
    UP2 = 119,
    LEFT2 = 97,
    DOWN2 = 115,
    RIGHT2 = 100,
    NONE = -7,
    ESCAPE = -8
};

struct Input {
    std::vector<int> _inputQueue;
    // UserInput pressedKey; // fly up down left right forward, shoot, activate shield (backspace), cahge weapons ( 1, 2, 3)
};

struct IsAlive {
    bool alive;
};

struct Position {
    Vector3 pos;

    bool operator==(Position &position) {
        if (this->pos.x == position.pos.x && \
            this->pos.y == position.pos.y && \
            this->pos.z == position.pos.z)
            return true;
        return false;
    }
};

struct Owner {
    EntityID id;
    RL::ModelType ownerType;
};

enum TargetType {
    MCGUYVER_TARGET,
    PLAYER_TARGET,
    PROJECTILE_TARGET,
    ENNEMY_TARGET,
    OBSTACLE_TARGET,
    POWERUP_TARGET,
};

struct ModelName {
    std::string modelname;
};

struct ModelScale {
    float modelScale;
};

struct AmmoCapacity {
    std::size_t maxAmmo;
    std::size_t curAmmo;
};

// enum ItemType {
//     SPEED_UP = 's',
//     BOMB_UP = 'b',
//     FIRE_UP = 'f',
//     WALLPASS = 'w'
// };



// struct Level {
//     std::size_t level;
// };

// struct Skillset {
//     std::size_t bombUp;
//     std::size_t speedUp;
//     std::size_t fireUp;
//     bool wallPass;

//     Skillset operator+=(const Skillset &other) {
//         bombUp += other.bombUp;
//         speedUp += other.speedUp;
//         fireUp += other.fireUp;
//         if (!wallPass && other.wallPass)
//             wallPass = true;
//         return *this;
//     };
// };

struct UIPos {
    int x;
    int y;
};

struct UiContinue {
    bool continueToRight;
};

struct Velocity {
    float x;
    float y;
    float z;

    Velocity operator*(const float &factor) {
        Velocity vel = Velocity();
        vel.x = this->x * factor;
        vel.y = this->y * factor;
        vel.z = this->z * factor;
        return vel;
    };

    Velocity operator+(const float &factor) {
        Velocity vel = Velocity(*this);
        if (this->x)
            vel.x = this->x + factor;
        if (this->y)
            vel.y = this->y + factor;
        if (this->z)
            vel.z = this->z + factor;
        return vel;
    };
};

struct Score {
    std::size_t score;
};

struct Hp {
    int hp;
};

struct Shield {
    int shield;
};

