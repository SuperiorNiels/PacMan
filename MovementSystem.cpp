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
        p->x += 5;
        p->y += 5;
        std::cout << "[Movement] \t Moved entity with id: " << e->id << std::endl;
    }
}