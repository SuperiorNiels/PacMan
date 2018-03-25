//
// Created by niels on 05/03/18.
//

#include "MovementSystem.h"

MovementSystem::MovementSystem(World* world)
{
    component_types = {MOVABLE_COMPONENT};
    MovementSystem::world = world; //fixme: shared pointer?
}

void MovementSystem::update()
{
    for(auto& e : entities)
    {
        if(e->hasComponentTypes({POSITION_COMPONENT,MOVABLE_COMPONENT}))
        {
            auto* p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            auto* m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);

            if(m->dir == LEFT)
            {
                p->x -= m->speed;
            } else if(m->dir == RIGHT)
            {
                p->x += m->speed;
            } else if(m->dir == UP)
            {
                p->y -= m->speed;
            } else if(m->dir == DOWN)
            {
                p->y += m->speed;
            }

            if(p->x > world->getWidth()-1)
            {
                p->x = 0;
            }
            if(p->x < 0)
            {
                p->x = world->getWidth()-1;
            }
            if(p->y > world->getHeight()-1)
            {
                p->y = 0;
            }
            if(p->y < 0)
            {
                p->y = world->getHeight()-1;
            }
        }
    }
}