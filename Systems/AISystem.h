//
// Created by niels on 06/03/18.
//

#ifndef ECS_AISYSTEM_H
#define ECS_AISYSTEM_H

#include <map>
#include <random>
#include "../ECS/ECS.h"
#include "../PacMan_Components.h"

class AISystem : public System {
public:
    AISystem() = delete;
    explicit AISystem(World* world);
    void update() override;
private:
    double calculateDistance(int x1, int y1, int x2, int y2);
    World* world;
};


#endif //ECS_AISYSTEM_H
