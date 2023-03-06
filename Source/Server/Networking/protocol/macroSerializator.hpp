/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** macroSerializator
*/

#ifndef MACROSERIALIZATOR_HPP_
#define MACROSERIALIZATOR_HPP_

// right macro for the size of each packet
enum PACKET_SIZE {
    SIZE_DELETE_ENTITY = 1 + sizeof(unsigned long long),
    SIZE_UPDATE_LOOT = 1 + sizeof(unsigned long long) + sizeof(int) * 4,
    SIZE_UPDATE_EXPLOSION = 1 + sizeof(unsigned long long) + sizeof(int) * 4,
    SIZE_UPDATE_ENNEMY = 1 + sizeof(unsigned long long) + sizeof(int) * 7,
    SIZE_UPDATE_OBSTACLE = 1 + sizeof(unsigned long long) + sizeof(int) * 4,
    SIZE_UPDATE_PROJECTILE = 1 + sizeof(unsigned long long) * 2 + sizeof(int) * 5,
    SIZE_UPDATE_PLAYER = 1 + sizeof(unsigned long long) * 2 + sizeof(int) * 7,
    SIZE_UPDATE_MAP = 1 + sizeof(unsigned long long) + sizeof(int) * 3,
    SIZE_STATE_GAME = 2,
    SIZE_ACTION = 1 + sizeof(unsigned long long) + sizeof(int) * 3,
    SIZE_SELECTION = 1 + sizeof(unsigned long long) + sizeof(int) * 3,
    SIZE_ID_CLIENT = 1 + sizeof(int),
    SIZE_CAN_SELECT = 1 + sizeof(int) + 1,
    SIZE_LONG_INT = 1 + sizeof(int) + sizeof(unsigned long long),
    SIZE_2_INT = 1 + sizeof(int) * 2,
};

#endif /* !MACROSERIALIZATOR_HPP_ */
