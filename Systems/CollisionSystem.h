//
// Created by niels on 07/03/18.
//

#ifndef ECS_COLLISIONSYSTEM_H
#define ECS_COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "SDL2/SDL.h"
#include "../PacMan_Components.h"
#include "../PacMan_Constants.h"

struct box
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

class CollisionSystem : public System
{
public:
    CollisionSystem();
    void update() override;
    void addEntity(Entity* e) override;
    bool checkCollision(box a, box b);
private:
    std::vector<Entity*> to_check = std::vector<Entity*>();
};


#endif //ECS_COLLISIONSYSTEM_H
