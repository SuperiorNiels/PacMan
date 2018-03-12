//
// Created by niels on 05/03/18.
//

#include "MovementSystem.h"
#include "../PacMan_Constants.h"
#include "../SDL_Components.h"

MovementSystem::MovementSystem()
{
    component_types = {MOVABLE_COMPONENT};
}

void MovementSystem::update()
{
    for(auto& e : entities)
    {
        auto* p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
        auto* m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
        auto* rc = e->getComponentByType<RenderComponent>(RENDER_COMPONENT);
        if(p != nullptr && m != nullptr)
        {
            p->x += m->x_speed;
            p->y += m->y_speed;
            if(p->x > WINDOW_WIDTH/SCALE_FACTOR)
            {
                p->x = 0;
            }
            if(p->x+rc->width < 0)
            {
                p->x = (int)floor(WINDOW_WIDTH/SCALE_FACTOR);
            }
            if(p->y > WINDOW_HEIGHT/SCALE_FACTOR)
            {
                p->y = 0;
            }
            if(p->y+rc->width < 0)
            {
                p->y = (int)floor(WINDOW_HEIGHT/SCALE_FACTOR);
            }
            //std::cout << "[Movement] \t Moved entity with id: " << e->id << std::endl;
        }
    }
}