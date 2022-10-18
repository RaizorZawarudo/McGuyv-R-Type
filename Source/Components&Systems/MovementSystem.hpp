/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ISystem.hpp"
#include "../InputManager.hpp"
// #include "../CollisionManager.hpp"


class MovementSystem : public ISystem {
    public:
        // enum PlayerType {
        //     Player_One,
        //     Player_Two,
        //     Player_AI,
        //     Other
        // };
        MovementSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::InputManager> inputManager) : _inputManager(inputManager)
        {
            _em = em;
        };
        ~MovementSystem() {};

        void update(std::vector<EntityID> &allEntities) override {
            for (EntityID ent : EntityViewer<Position, Velocity, Input, EntityType>(*_em.get())) {
                _ent = ent;
                Position* entityPos = _em->Get<Position>(ent);
                Velocity* entityVel = _em->Get<Velocity>(ent);
                Input* entityMovement = _em->Get<Input>(ent);
                EntityModelType* entityType = _em->Get<EntityModelType>(ent);

                if (entityType->modelType == RL::ModelType::SPACESHIP) {
                    std::cout << "THERE IS SPACESHIP IN MOVEMENT SYSTEMS!!!" << std::endl;
                    for (int keypressed : entityMovement->_inputQueue) { // && ID of entity = id of client
                        switch (keypressed) {
                            case UP:
                            case UP2:
                                //playerSprite->model->setCurrentAnim(1);
                                moveUp(entityPos, entityVel);
                                break;
                            case DOWN:
                                //playerSprite->model->setCurrentAnim(1);
                                moveDown(entityPos, entityVel);
                                break;
                            case LEFT:
                            case LEFT2:
                                //playerSprite->model->setCurrentAnim(1);
                                moveLeft(entityPos, entityVel);
                                break;
                            case RIGHT:
                                //playerSprite->model->setCurrentAnim(1);
                                //playerSprite->model->updateModelsAnimation();
                                moveRight(entityPos, entityVel);
                                break;
                            // case FORWARD :
                            //     moveForward(entityPos, entityVel);
                            // case SHOOT: 
                            //     shootProjectile(weapontype); // here we have to create the entity depending on the bullet type, so we need the weapons pointer
                            // case FIRSTWEAPON :
                            // case SECONDWEAPON:
                            // case THIRDWEAPON:
                            case NONE:
                                break;
                        }
                    }
                }
            }
        };

        // if entity == ENNEMY do AI movement

        //if entity == PROJECTILE == DO MOVEMENTS FOR PROJECTILES



        // if entity == obstale to movement for obstacle

        // bool checkMovable(Pos pos, bool wallPass) {
        //     if (_colManager.collisionsWithWalls((RL::Vector3f){pos.x, pos.y, pos.z}, *_map.get()))
        //         return false;
        //     if (!wallPass && _colManager.collisionsWithCrates((RL::Vector3f){pos.x, pos.y, pos.z}, *_map.get()))
        //         return false;
        //     Sprite *player = _em->Get<Sprite>(_ent);
        //     Pos *playerPos = _em->Get<Pos>(_ent);
        //     for (EntityID ent : EntityViewer<Pos, Sprite, BombProperty, BombOwner>(*_em.get())) {
        //         Sprite *bomb = _em->Get<Sprite>(ent);
        //         Pos *bombPos = _em->Get<Pos>(ent); //remove again
        //         BombProperty *bombProperty = _em->Get<BombProperty>(ent);
        //         if (_colManager.collisionsWithModels((RL::Vector3f){pos.x, pos.y, pos.z}, *bomb->model)) {
        //             for (Blocking blocking : bombProperty->blockingForPlayer) {
        //                 if (blocking.id == _ent && blocking.isBlocking)
        //                     return false;
        //             }
        //         }
        //     }
        //     return true;
        // }

        bool checkPressedUp() {
            if (_inputManager->playerHasPressedKeyAsChar(UP) || _inputManager->playerHasPressedKeyAsChar(UP2) )
                return true;
            else
                return false;
        }

        bool checkPressedDown() {
            if (_inputManager->playerHasPressedKeyAsChar(DOWN) || _inputManager->playerHasPressedKeyAsChar(DOWN2) )
                return true;
            else
                return false;
        }

        bool checkPressedLeft() {
            if (_inputManager->playerHasPressedKeyAsChar(LEFT) || _inputManager->playerHasPressedKeyAsChar(LEFT2))
                return true;
            else
                return false;
        }

        bool checkPressedRight() {
            if (_inputManager->playerHasPressedKeyAsChar(RIGHT) || _inputManager->playerHasPressedKeyAsChar(RIGHT2))
                return true;
            else
                return false;
        }

        void moveLeft(Position *pos, Velocity *vel)
        {
            if (checkPressedUp()) {
                moveUpLeft(pos, vel);
                return;
            }
            if (checkPressedDown()) {
                moveDownLeft(pos, vel);
                return;
            }
                pos->pos.x -= vel->x;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(270.0f);

        };

        void moveRight(Position *pos, Velocity *vel)
        {
            if (checkPressedUp()) {
                moveUpRight(pos, vel);
                return;
            }
            if (checkPressedDown()) {
                moveDownRight(pos, vel);
                return;
            }
                pos->pos.x += vel->x;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(90.0f);
        };

        void moveUp(Position *pos, Velocity *vel)
        {
            if (checkPressedLeft()) {
                moveUpLeft(pos, vel);
                return;
            }
            if (checkPressedRight()) {
                moveUpRight(pos, vel);
                return;
            }
                pos->pos.y -= vel->y;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(180.0f);
        };

        void moveDown(Position *pos, Velocity *vel)
        {
            if (checkPressedLeft()) {
                moveDownLeft(pos, vel);
                // playerSprite->model->setCurrentAnim(1);
                // playerSprite->model->updateModelsAnimation();
                return;
            }
            if (checkPressedRight()) {
                moveDownRight(pos, vel);
                return;
            }
                pos->pos.y += vel->y;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(0.0f);
        };

        void moveUpLeft(Position *pos, Velocity *vel)
        {
                pos->pos.x -= vel->x / 2;
                pos->pos.y -= vel->y / 2;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(225.0f);
        };

        void moveUpRight(Position *pos, Velocity *vel)
        {
                pos->pos.x += vel->x / 2;
                pos->pos.y -= vel->y / 2;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(135.0f);
        };

        void moveDownLeft(Position *pos, Velocity *vel)
        {

                pos->pos.x -= vel->x / 2;
                pos->pos.y += vel->y / 2;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(315.0f);
        };

        void moveDownRight(Position *pos, Velocity *vel)
        {
                pos->pos.x += vel->x / 2;
                pos->pos.y += vel->y / 2;
            //     playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
            //     playerSprite->model->setRotation(45.0f);
            // }
        };

    private:
        std::shared_ptr<RL::InputManager> _inputManager;
        // RL::CollisionManager _colManager;
        // PlayerType _type = Other;
        EntityID _ent;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */