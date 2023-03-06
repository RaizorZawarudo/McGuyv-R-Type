/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** Serializator
*/

#include "Serializator.hpp"
#include <map>
#include <functional>

Serializator::Serializator()
{
}

Serializator::~Serializator()
{
}

unsigned long long Serializator::byteArrayToLongLong(char *byteArray) {
    unsigned long long number = 0;

    memcpy(&number, byteArray, sizeof(unsigned long long));
    return number;
}

int Serializator::byteArrayToInt(char *byteArray) {
    int number = 0;

    memcpy(&number, byteArray, sizeof(int));
    return number;
}

Msg Serializator::bytesToStruct(char *msg)
{
    std::map<serializator::Header, std::function<Msg(char *msg)>> factory = {
//             {
//                 serializator::Header::createEntity,
//                 [this](char *msg) {
//                     Msg models;
// //                    models.status = Header::createEntity;
//                     models.setstatus(static_cast<serializator::Header>(msg[0]));
//                     models.setId(this->byteArrayToLongLong(&msg[sizeof(char)]));
//                     models.settype(msg[9]);
//                     return models;
//                 }
//             },

            // {
            //     serializator::Header::updateEntity,
            //     [this](char *msg) {
            //         Msg models;

            //         models.setstatus(static_cast<serializator::Header>(msg[0]));
            //         models.setId(this->byteArrayToLongLong(&msg[sizeof(char)]));
            //         models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(unsigned long long)]));
            //         models.setY(this->byteArrayToInt(&msg[sizeof(char) + sizeof(unsigned long long) + sizeof(int)]));
            //         models.setZ(this->byteArrayToInt(&msg[sizeof(char) + sizeof(unsigned long long) + sizeof(int) * 2 ]));
            //         return models;
            //     }
            // },

            {
                serializator::Header::deleteEntity,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setId(this->byteArrayToLongLong(&msg[sizeof(char)]));
                    return models;
                }
            },

            {
                serializator::Header::updateMap,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setaction((int)msg[1] + (int)msg[2] + (int)msg[3] + (int)msg[4] + (int)msg[5] + (int)msg[6] + (int)msg[7] + (int)msg[8]);
                    return models;
                }
            },

            // {
            //     serializator::Header::stateGame,
            //     [this](char *msg) {
            //         Msg models;

            //         models.setstatus(static_cast<serializator::Header>(msg[0]));
            //         models.setstate((int)msg[1] + (int)msg[2] + (int)msg[3] + (int)msg[4]);
            //         return models;
            //     }
            // },

            {
                serializator::Header::action,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setId(this->byteArrayToLongLong(&msg[sizeof(char)]));

                    models.setmovement(static_cast<serializator::Movement>(msg[9]));
                    return models;
                }
            },
            {
                serializator::Header::UpdateLoot,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setLootIndex(this->byteArrayToInt(&msg[sizeof(char)]));
                    models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    models.setY(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 2)]));
                    models.setZ(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 3)]));
                    models.setId(this->byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 4)]));
                    return models;
                }
            },
            {
                serializator::Header::UpdateExplosion,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setExplosionIndex(byteArrayToInt(&msg[sizeof(char)]));
                    models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    models.setY(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 2)]));
                    models.setZ(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 3)]));
                    models.setId(byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 4)]));
                    return models;
                }
            },
            {
                serializator::Header::UpdateEnnemy,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setEnemyIndex(this->byteArrayToInt(&msg[sizeof(char)]));
                    models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    models.setY(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 2)]));
                    models.setZ(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 3)]));
                    models.setPitch(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 4)]));
                    models.setYaw(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 5)]));
                    models.setRoll(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 6)]));
                    models.setId(byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 7)]));
                    return models;
                }
            },
            {
                serializator::Header::UpdateObstacle,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setObstacleIndex(this->byteArrayToInt(&msg[sizeof(char)]));
                    models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    models.setY(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 2)]));
                    models.setZ(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 3)]));
                    models.setId(byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 4)]));
                    return models;
                }
            },
            {
                serializator::Header::UpdateProjectile,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setWeaponId(this->byteArrayToInt(&msg[sizeof(char)]));
                    models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    models.setY(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 2)]));
                    models.setZ(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 3)]));
                    models.setId(byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 4)]));
                    models.setDirection(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int) * 4 + sizeof(unsigned long long)]));
                    models.setOwnerId(this->byteArrayToLongLong(&msg[sizeof(char) + sizeof(int) * 5 + sizeof(unsigned long long)]));
                    return models;

                }
            },
            {
                serializator::Header::UpdatePlayer,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setModelIndex(this->byteArrayToInt(&msg[sizeof(char)]));
                    models.setX(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    models.setY(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 2)]));
                    models.setZ(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 3)]));
                    models.setPitch(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 4)]));
                    models.setYaw(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 5)]));
                    models.setRoll(this->byteArrayToInt(&msg[sizeof(char) + (sizeof(int) * 6)]));
                    models.setId(byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 7)]));
                    models.setOwnerId(this->byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 7) + sizeof(unsigned long long)]));
                    models.setClientHash(this->byteArrayToLongLong(&msg[sizeof(char) + (sizeof(int) * 7) + sizeof(unsigned long long)]));
                    return models;
                }
            },
            {
                serializator::Header::stateGame,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setstate(static_cast<bool>(&msg[sizeof(char)]));
                    return models;
                }
            },

            {
                serializator::Header::menu,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setClientHash(this->byteArrayToInt(&msg[sizeof(char)]));
                    return models;
                }
            }, 
            {
                serializator::Header::startGame,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setStartGame(static_cast<bool>(&msg[sizeof(bool)]));
                    return models;
                }
            },
            {
                serializator::Header::canSelect,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    return models;
                }
            },
            {
                serializator::Header::spaceShipSelection,
                [this](char *msg) {
                    Msg models;

                    models.setstatus(static_cast<serializator::Header>(msg[0]));
                    models.setSpaceShipIndex(this->byteArrayToInt(&msg[sizeof(char)]));
                    models.setClientHash(this->byteArrayToInt(&msg[sizeof(char) + sizeof(int)]));
                    return models;
                }
            },

    };

    serializator::Header headerReceive = static_cast<serializator::Header>(msg[0]);

    auto it = factory[headerReceive];
    if (!it) {
        std::string error("message type Unknown");
        throw error.c_str();
    }
    return it(msg);
}

std::ostream& operator<< (std::ostream& stream, const Msg &message)
{
    stream
        << "id:" << message.getId() << '\n'
        << "status:" << message.getstatus() << '\n'
        << "x:" << message.getX() << '\n'
        << "y:" << message.getY()  << '\n'
        << "z:" << message.getZ() << '\n'
        << "state:" << message.getstate() << '\n'
        << "type:" << message.gettype() << '\n'
        << "action:" << message.getaction() << '\n'
        << "movement:" << message.getmovement() << std::endl;
    return stream;
}
