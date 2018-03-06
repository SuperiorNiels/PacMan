//
// Created by niels on 05/03/18.
//

#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
    component_types = {0}; // position component
}

void MovementSystem::update()
{
    for(auto& e : entities)
    {
        auto* p = e->getComponentByType<PositionComponent>(0);
        int to_add = 0;
        if(e->id == 1)
            to_add = -1;
        p->x += to_add;
        p->y += to_add;
        std::cout << "[Movement] \t Moved entity with id: " << e->id << std::endl;
    }
}