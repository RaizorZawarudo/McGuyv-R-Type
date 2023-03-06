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
#include <chrono>

#include "../Drawable3D.hpp"
#include "../ECS/ECS.hpp"

#include <ctime>

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

enum PowerUpEnum {
    WEAPONPOWER,
    SHIELDPOWER,
    REFLECTPOWER,
    IMMUNEPOWER,
    ETCPoWER
};

struct PowerUpType {
    PowerUpEnum type;
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
    SHIELD = 112,
    DROPWEAPON = 108,
    NONE = -7,
    ESCAPE = -8,
};

struct Input {
    std::vector<int> _inputQueue;
    // UserInput pressedKey; // fly up down left right forward, shoot, activate shield (backspace), cahge weapons ( 1, 2, 3)
};

struct IsAlive {
    bool alive;
};

struct EnnemyAnim {
    bool animated;
};

struct HasUpdated {
    bool updated;
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

struct PitchYawRoll {
    float pitch;
    float yaw;
    float roll;
};

struct Collider {
    BoundingBox collider;
};

struct Owner {
    EntityID id;
    RL::ModelType ownerType;
};

struct ModelName {
    std::string modelname;
    std::string explosionname;
};

struct ModelScale {
    float modelScale;
};

struct ModelDimensions {
    float heightY;
    float widthX;
    float lengthZ;
};

struct AnimationData {
    int currentFrame;
    int currentAnim;
    int maxFrame;
};

struct UIAvatarNames {
    std::string avatarName;
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
    int score;
};

struct Hp {
    int hp;
};

struct Shield {
    int shield;
    bool shieldActive;
    Shield operator+=(const Shield &other) {
        shield += other.shield;
        return *this;
    }
};

struct ProjectileWeapon {
    std::string name;
    std::string modelName;
    Velocity vel;
    float range;
    float splash;
    int maxAmmo;
    int curAmmo;
    int damage;

    float cooldowninseconds;
    std::chrono::system_clock::time_point lasttimeweaponwasshot;

    ProjectileWeapon operator+=(const ProjectileWeapon &other) {
        curAmmo += other.curAmmo;
        if (curAmmo > maxAmmo) curAmmo = maxAmmo;
        return *this;
    }
};

struct Weaponset {
    std::vector<ProjectileWeapon> weapons;
    std::size_t currentWeapon;
};

struct Loot {
    bool hasloot;
    ProjectileWeapon weaponLoot;
    Shield shieldLoot;
};

struct Timer {
    std::chrono::system_clock::time_point lastTimeClocked;
    float cooldowninseconds;
};

enum TargetType {
    MCGUYVER_TARGET,
    PLAYER_TARGET,
    PROJECTILE_TARGET,
    ENNEMY_TARGET,
    OBSTACLE_TARGET,
    POWERUP_TARGET,
};

struct AI {
    std::string style;
    bool isMoving;
    float moveCooldown;
    std::chrono::system_clock::time_point lastTimeMoved;
    float moveDetectRange;
    float targetPlayerDetectRange;
    float moveRange;
    Vector3 moveTargetPos;

    bool hasShot;
    float shootCooldown;
    std::chrono::system_clock::time_point lastTimeShot;
    float shootDetectRange;
};

struct ServerEntityID {
    unsigned long long id;
};
