//
// Created by niels on 07/03/18.
//

#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
    component_types = {COLLISION_COMPONENT};
}

void CollisionSystem::addEntity(Entity *e)
{
    // TODO: create removeEntity function
    // entity is player?
    if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
    {
        to_check.push_back(e);
        return;
    }
    // entity is ghost?
    if(e->hasComponentType(AI_COMPONENT))
    {
        to_check.push_back(e);
        return;
    }
    System::addEntity(e);
}

void CollisionSystem::update()
{
    if(!to_check.empty())
    {
        for(auto& player : to_check)
        {
            auto *p = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            auto* mc = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            for (auto &e : entities)
            {
                if (e->id != player->id)
                {
                    auto *p2 = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                    if((int)floor(p->x) == (int)floor(p2->x) && (int)floor(p->y) == (int)floor(p2->y))
                    {
                        if(e->hasComponentType(POINTS_COMPONENT))
                        {
                            auto* rc = e->getComponentByType<RenderComponent>(RENDER_COMPONENT);
                            rc->visible = false;
                        }
                        else
                        {
                            p->x -= mc->x_speed;
                            p->y -= mc->y_speed;
                            mc->x_speed = 0;
                            mc->y_speed = 0;
                        }
                        //std::cout << "[Collision] " << "x1: " << (int)p->x << " y1: " << (int)p->y
                        //          << " x1: " << (int)p2->x << " y1: " << (int)p2->y << std::endl;
                    }
                }
            }
        }
    }
}