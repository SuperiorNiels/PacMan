//
// Created by niels on 06/03/18.
//

#ifndef ECS_AISYSTEM_H
#define ECS_AISYSTEM_H

#include <map>
#include <random>
#include "../ECS/ECS.h"
#include "../Pacman/PacMan_Components.h"

using namespace Pacman;

namespace Systems {
    class AISystem : public System {
    public:
        AISystem() = delete;

        explicit AISystem(World *world);

        void update() override;

    private:
        std::mt19937 gen;
        std::uniform_int_distribution<> dis;

        void updateState(Entity *e);

        void calculateRedTarget(Entity *e);

        void calculatePinkTarget(Entity *e);

        void calculateBlueTarget(Entity *e);

        void calculateOrangeTarget(Entity *e);

        double calculateDistance(int x1, int y1, int x2, int y2);

        World *world;
    };
};


#endif //ECS_AISYSTEM_H
