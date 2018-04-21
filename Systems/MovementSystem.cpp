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

            if(m->state != MOVING && m->current_dir != STOP)
            {
                m->x_prev = p->x;
                m->y_prev = p->y;

                p->x += movement_vector[m->current_dir][0];
                p->y += movement_vector[m->current_dir][1];

                m->state = MOVING;

                if(p->x > world->getWidth()-1)
                {
                    p->x = 0;
                    m->state = IDLE;
                }
                if(p->x < 0)
                {
                    p->x = world->getWidth()-1;
                    m->state = IDLE;
                }
                if(p->y > world->getHeight()-1)
                {
                    p->y = 0;
                    m->state = IDLE;
                }
                if(p->y < 0)
                {
                    p->y = world->getHeight()-1;
                    m->state = IDLE;
                }

                if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
                    std::cout << "x: " << p->x << " y: " << p->y << std::endl;
                //std::cout << "x: " << p->x << " y: " << p->y << std::endl;
            }
        }
    }
}