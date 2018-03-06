//
// Created by niels on 06/03/18.
//

#include "AISystem.h"
#include "SDL_Components.h"


AISystem::AISystem()
{
    component_types = {2};
}

void AISystem::update()
{
    for(auto& e : entities)
    {
        auto* m = e->getComponentByType<MovableComponent>(1);
        auto* a = e->getComponentByType<AIComponent>(2);
        auto* rc = e->getComponentByType<SDL_RenderComponent>(10);
        if(m != nullptr && a != nullptr && rc != nullptr)
        {
            if(a->count < 50 && a->count > 0)
            {
                m->x_speed = 2;
                rc->frame_offset = rc->direction_offsets[0];
                a->count++;
            }
        }
    }
}