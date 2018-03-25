//
// Created by niels on 07/03/18.
//

#ifndef ECS_COLLISIONSYSTEM_H
#define ECS_COLLISIONSYSTEM_H

#include <cmath>
#include "../ECS/ECS.h"
#include "../PacMan_Components.h"
#include "../PacMan_Constants.h"


class CollisionSystem : public System
{
public:
    CollisionSystem();
    void update() override;
    void addEntity(Entity* e) override;
    void removeEntity(entityID id) override;
    bool entityInSystem(entityID id) override;
private:
    std::vector<Entity*> to_check = std::vector<Entity*>();
};


#endif //ECS_COLLISIONSYSTEM_H
