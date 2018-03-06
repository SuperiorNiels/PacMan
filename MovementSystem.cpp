//
// Created by niels on 05/03/18.
//

#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
    component_types = {0, 1}; // position component
}

void MovementSystem::update()
{
    for(auto& e : entities)
    {
        auto* p = e->getComponentByType<PositionComponent>(0);
        auto* m = e->getComponentByType<MovableComponent>(1);
        if(p != nullptr && m != nullptr)
        {
            p->x += m->x_speed;
            p->y += m->y_speed;
            //std::cout << "[Movement] \t Moved entity with id: " << e->id << std::endl;
        }
    }
}