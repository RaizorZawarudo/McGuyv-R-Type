//
// Created by speedy on 2/8/23.
//

#include "Serializator.hpp"
#include <stdlib.h>

// Update entity

char *Serializator::createPackageStateGame(serializator::Header status, bool state)
{
    char *data = new char[SIZE_STATE_GAME];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), &state, sizeof(bool));
    return data;
}

char *Serializator::createPackageCanSelect(serializator::Header status, int id, bool state)
{
    char *data = new char[SIZE_CAN_SELECT];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));

    memcpy(data + sizeof(char), intToByte(id), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), &state, sizeof(bool));
    return data;
}

char *Serializator::createPackageUpdEnnemies(serializator::Header status, int index, int x, int y, int z, int pitch, int yaw, int roll, unsigned long long entityId)
{
    char *data = new char[SIZE_UPDATE_ENNEMY];

    char tmp = enumToByte(status);
    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(index), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(x), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 2, intToByte(y), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 3, intToByte(z), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 4, intToByte(pitch), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 5, intToByte(yaw), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 6, intToByte(roll), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 7, intToByte(entityId), sizeof(unsigned long long));
    return data;
}

// Remove entity
char *Serializator::createPackageRemoveEntity(serializator::Header status, unsigned long long entityId)
{
    char *data = new char[SIZE_DELETE_ENTITY];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(entityId), sizeof(entityId));
    return data;
}

// Update Map and state game
char *Serializator::createPackageUpdObs(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId)
{
    char *data = new char[SIZE_UPDATE_OBSTACLE];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(model), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(x), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 2), intToByte(y), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 3), intToByte(z), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 4), intToByte(entityId), sizeof(entityId));
    return data;
}

char *Serializator::createPackageUpdPowerUp(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId)
{
    char *data = new char[SIZE_UPDATE_LOOT];
    char tmp = enumToByte(status);
    
    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(model), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(x), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 2), intToByte(y), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 3), intToByte(z), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 4, intToByte(entityId), sizeof(entityId));
    return data;
}

char *Serializator::createPackageUpdExplosion(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId)
{
    char *data = new char[SIZE_UPDATE_EXPLOSION];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));    
    memcpy(data + sizeof(char), intToByte(model), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(x), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 2), intToByte(y), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 3), intToByte(z), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 4, intToByte(entityId), sizeof(entityId));
    return data;
}

char *Serializator::createPackageUpdProjectile(serializator::Header status, int weapon, int x, int y, int z, unsigned long long serverEntityId, int direction, unsigned long long OwnerId)
{
    char *data = new char[SIZE_UPDATE_PROJECTILE];
    char tmp = enumToByte(status);
    
    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(weapon), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(x), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 2), intToByte(y), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 3), intToByte(z), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 4), intToByte(serverEntityId), sizeof(serverEntityId));
    memcpy(data + sizeof(char) + (sizeof(int) * 4) + sizeof(unsigned long long), intToByte(direction), sizeof(int));
    memcpy(data + sizeof(char) + (sizeof(int) * 5) + sizeof(unsigned long long), intToByte(OwnerId), sizeof(serverEntityId));
    return data;
}

char *Serializator::createPackageSetClientId(serializator::Header status, unsigned long long id)
{
    char *data = new char[SIZE_DELETE_ENTITY];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(id), sizeof(unsigned long long));
    return data;
}

char *Serializator::createPackageSetSpaceShip(serializator::Header status, int indexSpaceShip, unsigned long long id)
{
    char *data = new char[SIZE_LONG_INT];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(indexSpaceShip), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(id), sizeof(unsigned long long));
    return data;
}

char *Serializator::createPackageStartGame(serializator::Header status, bool state)
{
    char *data = new char[SIZE_STATE_GAME];
    char tmp = enumToByte(status);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), &state, sizeof(bool));
    return data;
}

char *Serializator::createPackageUpdPlayer(serializator::Header header, int avatarIndex, int positionX, int positionY, int positionZ, int pitch, int yaw, int roll, unsigned long long serverEntitiyID, unsigned long long clientHashNumber) {
    char *data = new char[SIZE_UPDATE_PLAYER];
    char tmp = enumToByte(header);

    memcpy(data, &tmp, sizeof(char));
    memcpy(data + sizeof(char), intToByte(avatarIndex), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int), intToByte(positionX), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 2, intToByte(positionY), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 3, intToByte(positionZ), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 4, intToByte(pitch), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 5, intToByte(yaw), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 6, intToByte(roll), sizeof(int));
    memcpy(data + sizeof(char) + sizeof(int) * 7, intToByte(serverEntitiyID), sizeof(unsigned long long));
    std::cout << "BEFORE create Package Upd Player: " << clientHashNumber << std::endl;
    memcpy(data + sizeof(char) + sizeof(int) * 7 + sizeof(unsigned long long), intToByte(clientHashNumber), sizeof(unsigned long long));
    std::cout << "AFTER create Package Upd Player: " << byteArrayToLongLong(&data[sizeof(char) + sizeof(int) * 7 + sizeof(unsigned long long)]) << std::endl;
    return data;

}