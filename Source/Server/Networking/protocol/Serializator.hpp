/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** Serializator
*/

#ifndef SERIALIZATOR_HPP_
#define SERIALIZATOR_HPP_

#include <vector>
#include <bitset>
#include "macroSerializator.hpp"

#include <iostream>
#include <cstddef>
#include <string.h>

namespace serializator
{
    enum Movement {
        LEFT,
        RIGHT,
        DOWN,
        UP,
        SHOOT
    };
    enum Header {
        deleteEntity,
        UpdateLoot,
        UpdateExplosion,
        UpdateEnnemy,
        UpdateObstacle,
        UpdateProjectile,
        UpdatePlayer,
        updateMap,
        stateGame,
        action,
        menu,
        startGame,
        canSelect,
        spaceShipSelection
    };
} // namespace serializator


class Msg {
public:

    int getstatus() const {return _status;};
    void setstatus(serializator::Header status) {_status = status;};

    unsigned long long getId() const {return _id;};
    void setId(unsigned long long id) {_id = id;};

    int getOwnerId() const {return _ownerId;};
    void setOwnerId(unsigned long long id) {_ownerId = id;};

    int getWeaponId() const {return _weaponIndex;};
    void setWeaponId(unsigned long long weaponIndex) {_weaponIndex = weaponIndex;};

    unsigned long long getClientHash() const {return _clientHashNumber;};
    void setClientHash(int clientHashNumber) {_clientHashNumber = clientHashNumber;};

    int getX() const {return _x;};
    void setX(int x) {_x = x;};

    int getY() const {return _y;};
    void setY(int y) {_y = y;};

    void setZ(int z) {_z = z;};
    int getZ() const {return _z;};

    void setDirection(int direction) {_direction = direction;};
    int getDirection() const {return _direction;};

    bool getstate() const {return _state;};
    void setstate(bool state) {_state = state;};

    int getaction() const {return _action;};
    void setaction(int action) {_action = action;};

    int getLootIndex() const {return _lootIndex;};
    void setLootIndex(int lootIndex) { _lootIndex = lootIndex;};

    int getExplosionIndex() const {return _explosionIndex;};
    void setExplosionIndex(int lootIndex) { _explosionIndex = lootIndex;};

    int getEnemyIndex() const {return _enemyIndex;};
    void setEnemyIndex(int lootIndex) { _enemyIndex = lootIndex;};

    int getObstacleIndex() const {return _obstacleIndex;};
    void setObstacleIndex(int lootIndex) { _obstacleIndex = lootIndex;};

    int getModelIndex() const {return _modelIndex;};
    void setModelIndex(int lootIndex) { _modelIndex = lootIndex;};

    int getSpaceShipIndex() const {return _modelSpaceShip;};
    void setSpaceShipIndex(int model) { _modelSpaceShip = model;};

    int getAvatarIndex() const {return _avatarIndex;};
    void setAvatarIndex(int lootIndex) { _avatarIndex = lootIndex;};

    unsigned short int gettype() const {return _type;};
    void settype(unsigned short int type) {_type = type;};

    void setYaw(int yaw) {_yaw = yaw;};
    int getYaw() const {return _yaw;};

    void setPitch(int pitch) {_pitch = pitch;};
    int getPitch() const {return _pitch;};
    
    void setRoll(int roll) {_roll = roll;};
    int getRoll() const {return _roll;};

    void setStartGame(bool start) {_startGame = start;};
    bool getStartGame() const {return _startGame;};

    void setMapIndex(int mapIndex) {_mapIndex = mapIndex;};
    int getMapIndex() const {return _mapIndex;};

    void setRacerMode(bool racerMode) {_racerMode = racerMode;};
    bool getRacerMode() const {return _racerMode;};

    serializator::Movement getmovement() const {return _mvt;};
    void setmovement(serializator::Movement type) {_mvt = type;};

private:

    unsigned long long _id = 0;
    unsigned long long _ownerId = 0;
    unsigned long long _clientHashNumber = 0;
    unsigned short int _type = 0;
    int _x = 0;
    int _y = 0;
    int _z = 0;
    int _action = 0;
    bool _state = 0;
    int _lootIndex = 0;
    int _explosionIndex = 0;
    int _enemyIndex = 0;
    int _obstacleIndex = 0;
    int _direction = 0;
    int _weaponIndex = 0;
    int _modelIndex = 0;
    int _modelSpaceShip = 0;
    int _avatarIndex = 0;
    int _yaw = 0;
    int _pitch = 0;
    int _roll = 0;
    bool _startGame = false;
    int _mapIndex = 0;
    bool _racerMode = false;
    serializator::Header _status;
    serializator::Movement _mvt;
};

class Serializator {

public:
    Serializator();

    ~Serializator();

    char enumToByte(serializator::Header);
    char enumToByte(serializator::Movement);

    char *intToByte(unsigned long long);
    char *intToByte(int);
    char *intToByte(float number);

    int byteArrayToInt(char *byteArray);
    unsigned long long byteArrayToLongLong(char *byteArray);

    char *createPackageUpdPlayer(serializator::Header header, int avatarIdex, int positionX, int positionY, int positionZ, int pitch, int yaw, int roll, unsigned long long serverEntitiyID, unsigned long long clientHashNumber);
    char *createPackageUpdEnnemies(serializator::Header, int model, int x, int y, int z, int pitch, int raw, int roll, unsigned long long serverEntityId);
    char *createPackageRemoveEntity(serializator::Header, unsigned long long);
    char *createPackagePosEntity(serializator::Header, unsigned long long serverEntityId, int x, int y, int z);
    char *createPackageUpgLootExp(serializator::Header, int , int x, int y, int z, unsigned long long serverEntityId);
    char *createPackageUpdProjectile(serializator::Header, int , int x, int y, int z, unsigned long long serverEntityId, int, unsigned long long OwnerId);
    char *createPackageUpdPowerUp(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId);
    char *createPackageUpdObs(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId);
    char *createPackageUpdExplosion(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId);
    char *createPackageStateGame(serializator::Header status, bool state);
    

    // SERIALIZATOR MENU //
    char *createPackageSelection(serializator::Header status, int action);
    char *createPackageSetClientId(serializator::Header status, unsigned long long id);
    char *createPackageStartGame(serializator::Header status, bool);
    char *createPackageCanSelect(serializator::Header status, int,bool state);
    char *createPackageSetSpaceShip(serializator::Header status, int indexSpaceShip, unsigned long long id);


    Msg bytesToStruct(char *l);
};

std::ostream& operator<< (std::ostream& stream, const Msg &message);
#endif /* !SERIALIZATOR_HPP_ */
