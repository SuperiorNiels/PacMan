//
// Created by niels on 07/03/18.
//

#ifndef ECS_COLLISIONSYSTEM_H
#define ECS_COLLISIONSYSTEM_H

#include <cmath>
#include "../ECS/ECS.h"
#include "../Pacman/PacMan_Components.h"
#include "../Pacman/PacMan_Constants.h"

using namespace Pacman;

namespace Systems {
    class CollisionSystem : public ECS::System {
    public:
        explicit CollisionSystem(std::map<Pacman::events_numbers, bool> *events);

        void update() override;

        void addEntity(ECS::Entity *e) override;

        void removeEntity(ECS::entityID id) override;

        bool entityInSystem(ECS::entityID id) override;

    private:
        std::map<ECS::entityID, ECS::Entity *> players;
        std::map<ECS::entityID, ECS::Entity *> ghosts;
        std::map<events_numbers, bool> *events;
    };
};


#endif //ECS_COLLISIONSYSTEM_H
