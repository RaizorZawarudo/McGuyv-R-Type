/*
** EPITECH PROJECT, 2023
** RType
** File description:
** updatedNotifSystem
*/

#include "ISystem.hpp"

class HasUpdatedSystem : public ISystem {
    public:
        HasUpdatedSystem(std::shared_ptr<EntityManager> em) {
            _em = em;
        }
        ~HasUpdatedSystem();

        void update(std::vector<EntityID> &allEntities) override;
};
