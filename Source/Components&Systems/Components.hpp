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
// #include "../Raylib/RaylibTypeEncaps.hpp"
#include "../ECS/ECS.hpp"

typedef std::pair<size_t, size_t> coordinates_t;

enum PlayerNumber {
    One = 0,
    Two = 1,
    Three = 2,
    Four = 4,
};

enum UserInput {
    LAY_BOMB = -6,
    LAY_BOMB2 = 103,
    CLOSED_WINDOW = -5,
    UP = -4,
    LEFT = -3,
    DOWN = -2,
    RIGHT = -1,
    UP2 = 119,
    LEFT2 = 97,
    DOWN2 = 115,
    RIGHT2 = 100,
    NONE = -7,
    ESCAPE = -8
};

struct Input {
    UserInput pressedKey; // fly up down left right forward, shoot, activate shield (backspace), cahge weapons ( 1, 2, 3)
};

struct Position {
    float x;
    float y;
    float z;

    bool operator==(Position &position) {
        if (this->x == position.x && \
            this->y == position.y && \
            this->z == position.z)
            return true;
        return false;
    }
};

struct Owner {
    EntityID id;
};


// dont change order, it defines their dying priority
enum CollisionObjectType {
    MCGUYVER,
    PLAYER,
    ENNEMY,
    PROJECTILE,
    OBSTACLE,
    POWERUP
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

// ?


typedef struct
{
    int tile;
    int orientation;
} gfx_tile_t;
