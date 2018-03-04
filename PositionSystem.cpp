//
// Created by niels on 04/03/18.
//

#include "PositionSystem.h"

void PositionSystem::update()
{
    for(auto& e : entities)
    {
        auto* p = e->getComponentByType<PositionComponent>(0);
        if(p != nullptr)
        {
            p->x += 5;
            p->y += 5;
            std::cout << "[PositionSystem] entity moved. New position: " << p->x << ", " << p->y  << std::endl;
        }
    }
}