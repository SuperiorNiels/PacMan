//
// Created by niels on 05/03/18.
//

#include "../../include/Systems/MovementSystem.h"

namespace Systems
{

    MovementSystem::MovementSystem(World *world, std::map<events_numbers, bool> *events)
    {
        component_types = {MOVABLE_COMPONENT};
        MovementSystem::world = world;
        MovementSystem::events = events;
    }

    void MovementSystem::update()
    {
        // If death event is triggered, stop movement system
        if (events->find(DEATH) != events->end())
            return;

        for (auto it : entities)
        {
            auto e = it.second; // get entity
            if (e->hasComponentTypes({POSITION_COMPONENT, MOVABLE_COMPONENT}))
            {
                auto *p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                auto *m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);

                if (m->state != MOVING && m->current_dir != STOP)
                {
                    m->x_prev = p->x;
                    m->y_prev = p->y;

                    p->x += movement_vector[m->current_dir][0];
                    p->y += movement_vector[m->current_dir][1];

                    m->state = MOVING;

                    if (p->x > world->getWidth() - 1)
                    {
                        p->x = 0;
                        m->state = IDLE;
                    }
                    if (p->x < 0)
                    {
                        p->x = world->getWidth() - 1;
                        m->state = IDLE;
                    }
                    if (p->y > world->getHeight() - 1)
                    {
                        p->y = 0;
                        m->state = IDLE;
                    }
                    if (p->y < 0)
                    {
                        p->y = world->getHeight() - 1;
                        m->state = IDLE;
                    }
                }

                if (m->state == MOVING && !m->animate)
                {
                    if (100 - m->speed < m->time)
                    {
                        m->state = IDLE;
                        m->time = 0;
                    }
                    else
                    {
                        m->time += 4;
                    }
                }
            }
        }
    }

};