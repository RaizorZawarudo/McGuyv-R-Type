/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** DrawSystem
*/

#pragma once

#include "ISystem.hpp"
#include "../Renderer.hpp"


class DrawSystem : public ISystem {
    public:
        DrawSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Renderer>) {
            _em = em;
        }
        ~DrawSystem() {};

        void update(std::vector<EntityID> &allEntities) override {
            for (EntityID ent : EntityViewer<Position, ModelName, EntityType>(*_em.get())) {
                Position *objectPos = _em->Get<Position>(ent);
                ModelName *objectModelName = _em->Get<ModelName>(ent);
                // CollisionObjectType type = *_em->Get<CollisionObjectType>(ent);

                // if (type != ITEM) {
                //     objectSprite->model->setPosition((RL::Vector3f){
                //         translateObjectCoordinates(objectPos->x, borderWidth, widthEven),
                //         0.5f,
                //         translateObjectCoordinates(objectPos->y, borderDepth, depthEven)
                //     });
                // }
                // if (type == PLAYER || type == AI || type == EXPLOSION)            
                
                // objectSprite->model.draw();
            }
        }

    private:
        int borderWidth;
        int borderDepth;
        bool widthEven;
        bool depthEven;
};
