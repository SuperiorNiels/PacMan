//
// Created by niels on 06/03/18.
//

#ifndef ECS_AISYSTEM_H
#define ECS_AISYSTEM_H

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
    std::vector<Node*> getPath(int start_x, int start_y, int stop_x, int stop_y);
    double calculateDistance(int x1, int x2, int y1, int y2);
};


#endif //ECS_AISYSTEM_H
