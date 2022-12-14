/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include <memory>
#include "../ECS/EntityViewer.hpp"
#include "Components.hpp"

class ISystem {
    public:
        virtual ~ISystem() = default;

        virtual void update(std::vector<EntityID> &allEntities) = 0;
    
    protected:
        std::shared_ptr<EntityManager> _em;
};

#endif /* !ISYSTEM_HPP_ */