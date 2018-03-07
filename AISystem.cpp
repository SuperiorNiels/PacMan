//
// Created by niels on 06/03/18.
//

#include "AISystem.h"
#include "SDL_Components.h"


AISystem::AISystem()
{
    component_types = {AI_COMPONENT};
    srand (time(NULL));
}

void AISystem::update()
{
    for(auto& e : entities)
    {
        auto* m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
        auto* a = e->getComponentByType<AIComponent>(AI_COMPONENT);
        auto* rc = e->getComponentByType<RenderComponent>(RENDER_COMPONENT);
        if(m != nullptr && a != nullptr && rc != nullptr)
        {
            if(a->count > a->length)
            {
                a->length = rand() % 250 + 20;
                int r = rand() % 4 + 1;
                m->x_speed = -1;
                m->y_speed = 0;
                rc->frame_offset = rc->direction_offsets[0];
                if (r == 1)
                {
                    m->x_speed = 1;
                    m->y_speed = 0;
                    rc->frame_offset = rc->direction_offsets[1];
                }
                else if(r == 2)
                {
                    m->x_speed = 0;
                    m->y_speed = 1;
                    rc->frame_offset = rc->direction_offsets[3];
                }
                else if(r == 3)
                {
                    m->x_speed = 0;
                    m->y_speed = -1;
                    rc->frame_offset = rc->direction_offsets[2];
                }
                a->count = 0;
            }
            a->count++;
        }
    }
}