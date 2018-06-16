//
// Created by niels on 05/03/18.
//

#ifndef ECS_MOVEMENTSYSTEM_H
#define ECS_MOVEMENTSYSTEM_H


#include "../Pacman/PacMan_Components.h"
#include "../Pacman/World.h"

using namespace Pacman;

namespace Systems {
    class MovementSystem : public System {
    public:
        MovementSystem() = delete;

        explicit MovementSystem(World *world);

        void update() override;

    private:
        World *world = nullptr;
    };
};


#endif //ECS_MOVEMENTSYSTEM_H
