//
// Created by niels on 05/03/18.
//

#include "MovementSystem.h"

MovementSystem::MovementSystem(World* world)
{
    component_types = {MOVABLE_COMPONENT};
    MovementSystem::world = world;
}

void MovementSystem::update()
{
    for(auto& e : entities)
    {
        if(e->hasComponentTypes({POSITION_COMPONENT,MOVABLE_COMPONENT}))
        {
            auto* p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            auto* m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            p->x += m->x_speed;
            p->y += m->y_speed;
            if(p->x > world->getWidth())
            {
                p->x = 0;
            }
            if(p->x < 0)
            {
                p->x = world->getWidth();
            }
            if(p->y > world->getHeight())
            {
                p->y = 0;
            }
            if(p->y < 0)
            {
                p->y = world->getHeight();
            }
            std::cout << "[Movement] " << "x: " << (int)p->x << " y: " << (int)p->y << std::endl;
        }
    }
}