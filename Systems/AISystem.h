//
// Created by niels on 06/03/18.
//

#ifndef ECS_AISYSTEM_H
#define ECS_AISYSTEM_H

#include <random>
#include "../ECS/ECS.h"
#include "../PacMan_Components.h"
#include "../Pathfinding/Pathfinder.h"

class AISystem : public System {
public:
    AISystem() = delete;
    explicit AISystem(World* world);
    void update() override;
    ~AISystem() override;
private:
    double calculateDistance(int x1, int y1, int x2, int y2);
    World* world;
    std::uniform_int_distribution<int> random_x;
    std::uniform_int_distribution<int> random_y;
    std::default_random_engine random_engine;

    Pathfinder* pathfinder = nullptr;
};


#endif //ECS_AISYSTEM_H
