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

const float MAXLEFT = 7.0F;
const float MAXRIGHT = -7.0F;
const float MAXUP = 6.0F;
const float MAXDOWN = 1.0F;


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
            for (EntityID ent : EntityViewer<Position, Velocity, Input, EntityModelType, PitchYawRoll>(*_em.get())) {
                _ent = ent;
                Position* entityPos = _em->Get<Position>(ent);
                Velocity* entityVel = _em->Get<Velocity>(ent);
                Input* entityMovement = _em->Get<Input>(ent);
                EntityModelType* entityType = _em->Get<EntityModelType>(ent);
                PitchYawRoll* pitchYawRoll = _em->Get<PitchYawRoll>(ent);
                

                if (entityType->modelType == RL::ModelType::SPACESHIP) {
                    if (entityMovement->_inputQueue.empty()) {
                        if (pitchYawRoll->roll > 0.0f) pitchYawRoll->roll -= 1.0f;
                        else if (pitchYawRoll->roll < 0.0f) pitchYawRoll->roll += 1.0f;
                        if (pitchYawRoll->pitch > 0.0f) pitchYawRoll->pitch -= 0.5f;
                        else if (pitchYawRoll->pitch < 0.0f) pitchYawRoll->pitch += 0.5f;
                    }
                    for (int keypressed : entityMovement->_inputQueue) { // && ID of entity = id of client
                        if (keypressed == UP || keypressed == UP2) moveUp(entityPos, entityVel, entityMovement, pitchYawRoll);
                        else if (keypressed == DOWN) moveDown(entityPos, entityVel, entityMovement, pitchYawRoll);
                        else {
                            if (pitchYawRoll->pitch > 0.0f) pitchYawRoll->pitch -= 0.5f;
                            else if (pitchYawRoll->pitch < 0.0f) pitchYawRoll->pitch += 0.5f;
                        }
                        if (keypressed == LEFT || keypressed == LEFT2) moveLeft(entityPos, entityVel, entityMovement, pitchYawRoll);
                        else if (keypressed == RIGHT) moveRight(entityPos, entityVel, entityMovement, pitchYawRoll);
                        else {
                            if (pitchYawRoll->roll > 0.0f) pitchYawRoll->roll -= 0.5f;
                            else if (pitchYawRoll->roll < 0.0f) pitchYawRoll->roll += 0.5f;
                        }
                    }
                }
            }
        };

        // if entity == ENNEMY do AI movement

        //if entity == PROJECTILE == DO MOVEMENTS FOR PROJECTILES

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

        void moveLeft(Position *pos, Velocity *vel, Input* entityMovement, PitchYawRoll* pitchYawRoll)
        {
            pitchYawRoll->roll > -20.0f ? pitchYawRoll->roll -= 1.0f : pitchYawRoll->roll -= 0.0f;

            if (pos->pos.x > MAXLEFT) return;

            if ((pos->pos.y < MAXUP) && checkPressedUp(entityMovement)) {
                moveUpLeft(pos, vel);
                return;
            }
            if ((pos->pos.y > MAXUP) && checkPressedDown(entityMovement)) {
                moveDownLeft(pos, vel);
                return;
            }
                pos->pos.x += vel->x;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(270.0f);

        };

        void moveRight(Position *pos, Velocity *vel, Input* entityMovement, PitchYawRoll* pitchYawRoll)
        {
        
            pitchYawRoll->roll < 20.0f ? pitchYawRoll->roll += 1.0f : pitchYawRoll->roll += 0.0f;

            if (pos->pos.x < MAXRIGHT) return;

            if ((pos->pos.y < MAXUP) && checkPressedUp(entityMovement)) {
                moveUpRight(pos, vel);
                return;
            }
            if ((pos->pos.y > MAXUP) && checkPressedDown(entityMovement)) {
                moveDownRight(pos, vel);
                return;
            }
                pos->pos.x -= vel->x;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(90.0f);
        };

        void moveUp(Position *pos, Velocity *vel, Input* entityMovement, PitchYawRoll* pitchYawRoll)
        {
            pitchYawRoll->pitch > -15.0f ? pitchYawRoll->pitch -= 1.0f : pitchYawRoll->pitch -= 0.0f;

            if (pos->pos.y > MAXUP) return;

            if ((pos->pos.x < MAXLEFT) && checkPressedLeft(entityMovement)) {
                moveUpLeft(pos, vel);
                return;
            }
            if ((pos->pos.x > -MAXRIGHT) && checkPressedRight(entityMovement)) {
                moveUpRight(pos, vel);
                return;
            }
                pos->pos.y += vel->y;
                // playerSprite->model->setPosition((RL::Vector3f){pos->x, pos->y, pos->z});
                // playerSprite->model->setRotation(180.0f);
        };

        void moveDown(Position *pos, Velocity *vel, Input* entityMovement, PitchYawRoll* pitchYawRoll)
        {
            pitchYawRoll->pitch < 15.0f ? pitchYawRoll->pitch += MAXUP : pitchYawRoll->pitch += 0.0f;

            if (pos->pos.y < MAXDOWN) return;

            if ((pos->pos.x < MAXLEFT) && checkPressedLeft(entityMovement)) {
                moveDownLeft(pos, vel);
                // playerSprite->model->setCurrentAnim(1);
                // playerSprite->model->updateModelsAnimation();
                return;
            }
            if ((pos->pos.x > MAXRIGHT) && checkPressedRight(entityMovement)) {
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