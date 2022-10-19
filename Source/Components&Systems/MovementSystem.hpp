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
        MovementSystem(std::shared_ptr<EntityManager> em)
        {
            _em = em;
        };
        ~MovementSystem() {};

        bool entityHasPressedKeyAsChar(Input *entityMovement, int key)
        {
            for (int i = 0; i < entityMovement->_inputQueue.size(); i++) {
                    if (entityMovement->_inputQueue[i]== key)
                        return true;
            }
             return false;        
        };

        void update(std::vector<EntityID> &allEntities) override {
            for (EntityID ent : EntityViewer<Position, Velocity, Input, EntityModelType>(*_em.get())) {
                _ent = ent;
                Position* entityPos = _em->Get<Position>(ent);
                Velocity* entityVel = _em->Get<Velocity>(ent);
                Input* entityMovement = _em->Get<Input>(ent);
                EntityModelType* entityType = _em->Get<EntityModelType>(ent);

                if (entityType->modelType == RL::ModelType::SPACESHIP) {
                    for (int keypressed : entityMovement->_inputQueue) { // && ID of entity = id of client
                        switch (keypressed) {
                            case UP:
                            case UP2:
                                //playerSprite->model->setCurrentAnim(1);
                                moveUp(entityPos, entityVel, entityMovement); // add entitiyMovement to constructor
                                break;
                            case DOWN:
                                //playerSprite->model->setCurrentAnim(1);
                                moveDown(entityPos, entityVel, entityMovement);
                                break;
                            case LEFT:
                            case LEFT2:
                                //playerSprite->model->setCurrentAnim(1);
                                moveLeft(entityPos, entityVel, entityMovement);
                                break;
                            case RIGHT:
                                //playerSprite->model->setCurrentAnim(1);
                                //playerSprite->model->updateModelsAnimation();
                                moveRight(entityPos, entityVel, entityMovement);
                                break;
                            // case FORWARD :
                            //     moveForward(entityPos, entityVel);
                            
                            //The other buttons are going to be in other systems
                            
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

        bool checkPressedUp(Input* entityMovement) {
            if (entityHasPressedKeyAsChar(entityMovement, UserInput::UP) || entityHasPressedKeyAsChar(entityMovement, UserInput::UP2) )
                return true;
            else
                return false;
         }

        bool checkPressedDown(Input* entityMovement) {
            if (entityHasPressedKeyAsChar(entityMovement, UserInput::DOWN) || entityHasPressedKeyAsChar(entityMovement, UserInput::DOWN2) )
                return true;
            else
                return false;
        }

        bool checkPressedLeft(Input* entityMovement) {
            if (entityHasPressedKeyAsChar(entityMovement, UserInput::LEFT) || entityHasPressedKeyAsChar(entityMovement, UserInput::LEFT2))
                return true;
            else
                return false;
        }

        bool checkPressedRight(Input* entityMovement) {
            if (entityHasPressedKeyAsChar(entityMovement, UserInput::RIGHT) || entityHasPressedKeyAsChar(entityMovement, UserInput::RIGHT2))
                return true;
            else
                return false;
        }

        void moveLeft(Position *pos, Velocity *vel, Input* entityMovement)
        {
            if (checkPressedUp(entityMovement)) {
                moveUpLeft(pos, vel);
                return;
            }
            if (checkPressedDown(entityMovement)) {
                moveDownLeft(pos, vel);
                return;
            }
                pos->pos.x += vel->x;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(270.0f);

        };

        void moveRight(Position *pos, Velocity *vel, Input* entityMovement)
        {
            if (checkPressedUp(entityMovement)) {
                moveUpRight(pos, vel);
                return;
            }
            if (checkPressedDown(entityMovement)) {
                moveDownRight(pos, vel);
                return;
            }
                pos->pos.x -= vel->x;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(90.0f);
        };

        void moveUp(Position *pos, Velocity *vel, Input* entityMovement)
        {
            if (checkPressedLeft(entityMovement)) {
                moveUpLeft(pos, vel);
                return;
            }
            if (checkPressedRight(entityMovement)) {
                moveUpRight(pos, vel);
                return;
            }
                pos->pos.y += vel->y;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(180.0f);
        };

        void moveDown(Position *pos, Velocity *vel, Input* entityMovement)
        {
            if (checkPressedLeft(entityMovement)) {
                moveDownLeft(pos, vel);
                // playerSprite->model->setCurrentAnim(1);
                // playerSprite->model->updateModelsAnimation();
                return;
            }
            if (checkPressedRight(entityMovement)) {
                moveDownRight(pos, vel);
                return;
            }
                pos->pos.y -= vel->y;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(0.0f);
        };

        void moveUpLeft(Position *pos, Velocity *vel)
        {
                pos->pos.x += vel->x / 2;
                pos->pos.y += vel->y / 2;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(225.0f);
        };

        void moveUpRight(Position *pos, Velocity *vel)
        {
                pos->pos.x -= vel->x / 2;
                pos->pos.y += vel->y / 2;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(135.0f);
        };

        void moveDownLeft(Position *pos, Velocity *vel)
        {

                pos->pos.x += vel->x / 2;
                pos->pos.y -= vel->y / 2;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(315.0f);
        };

        void moveDownRight(Position *pos, Velocity *vel)
        {
                pos->pos.x -= vel->x / 2;
                pos->pos.y -= vel->y / 2;
            //     playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
            //     playerSprite->model->setRotation(45.0f);
            // }
        };

    private:
        // RL::CollisionManager _colManager;
        // PlayerType _type = Other;
        EntityID _ent;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */