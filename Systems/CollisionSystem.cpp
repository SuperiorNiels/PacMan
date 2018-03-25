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
    if((e->hasComponentType(PLAYER_INPUT_COMPONENT) || e->hasComponentType(AI_COMPONENT)) && !entityInSystem(e->id))
    {
        to_check.push_back(e);
        return;
    }
    System::addEntity(e);
}

void CollisionSystem::removeEntity(entityID id)
{
    for(auto it = to_check.begin(); it != to_check.end(); it++)
    {
        Entity* e = it.operator*();
        if(e->id == id)
        {
            to_check.erase(it);
            return;
        }
    }
    System::removeEntity(id);
}

bool CollisionSystem::entityInSystem(entityID id)
{
    for(auto* e : to_check)
    {
        if(e->id == id)
            return true;
    }
    return System::entityInSystem(id);
}

void CollisionSystem::update()
{
    if(!to_check.empty())
    {
        for(auto& player : to_check)
        {
            auto* pc = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
            for (auto& entity : entities)
            {
                if (entity->id != player->id)
                {
                    auto *pc2 = entity->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                    if(entity->hasComponentType(POINTS_COMPONENT))
                    {
                        if ((int) floor(pc->x) == (int) floor(pc2->x) && (int) floor(pc->y) == (int) floor(pc2->y))
                        {
                            auto *rc = entity->getComponentByType<RenderComponent>(RENDER_COMPONENT);
                            rc->visible = false;
                            //TODO : add dots to different list, no collision with ghosts!!
                            //entity->clearComponents();
                        }
                    }
                    else
                    {
                        auto* mc = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                        double wanted_x = pc->x;
                        double wanted_y = pc->y;
                        if(mc->wanted_dir == LEFT)
                            wanted_x -= mc->speed;
                        else if(mc->wanted_dir == RIGHT)
                            wanted_x += mc->speed;
                        else if(mc->wanted_dir == UP)
                            wanted_y -= mc->speed;
                        else if(mc->wanted_dir == DOWN)
                            wanted_y += mc->speed;
                        std::cout << "wanted: " << mc->wanted_dir << " current: " << mc->current_dir << std::endl;
                        if ((int) floor(wanted_x) == (int) floor(pc2->x) && (int) floor(wanted_y) == (int) floor(pc2->y))
                        {
                            if(mc->current_dir == mc->wanted_dir)
                            {
                                mc->wanted_dir = STOP;
                                mc->current_dir = STOP;
                            }
                        }
                        else
                        {
                            mc->current_dir = mc->wanted_dir;
                        }

                    }
                }
            }
        }
    }
}