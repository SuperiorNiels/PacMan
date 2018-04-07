//
// Created by niels on 06/03/18.
//

#ifndef ECS_AISYSTEM_H
#define ECS_AISYSTEM_H

#include <random>
#include "../ECS/ECS.h"
#include "../PacMan_Components.h"
#include "../Pathfinding/Node.h"

class AISystem : public System {
public:
    AISystem() = delete;
    AISystem(World* world);
    void update() override;
private:
    World* world;
    std::uniform_int_distribution<int> random_x;
    std::uniform_int_distribution<int> random_y;
    std::default_random_engine random_engine;
};


#endif //ECS_AISYSTEM_H
