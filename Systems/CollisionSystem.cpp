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
                        if(!checkCollision(getClip(player), getClip(entity)))
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
                        /*double wanted_x = pc->x + movement_vector[mc->wanted_dir][0] * mc->speed;
                        double wanted_y = pc->y + movement_vector[mc->wanted_dir][1] * mc->speed;
                        //std::cout << "wanted: " << mc->wanted_dir << " current: " << mc->current_dir << std::endl;
                        if(!checkCollision(getClip(player),getClip(entity)))
                        {
                            mc->current_dir = mc->wanted_dir;
                        } else {
                            std::cout << "collision " << pc2->x << " " << pc2->y << std::endl;
                        }*/

                        //double new_x = pc->x + movement_vector[mc->current_dir][0] * mc->speed;
                        //double new_y = pc->y + movement_vector[mc->current_dir][1] * mc->speed;
                        //std::cout << "wanted: " << mc->wanted_dir << " current: " << mc->current_dir << std::endl;
                        if(checkCollision(getClip(player),getClip(entity)))
                        {
                            mc->wanted_dir = STOP;
                        }
                        mc->current_dir = mc->wanted_dir;
                    }
                }
            }
        }
    }
}

bool CollisionSystem::checkCollision(clip player, clip entity)
{
    double leftA, leftB;
    double rightA, rightB;
    double topA, topB;
    double bottomA, bottomB;

    leftA = player.x;
    rightA = player.x + player.w;
    topA = player.y;
    bottomA = player.y + player.h;

    leftB = entity.x;
    rightB = entity.x + entity.w;
    topB = entity.y;
    bottomB = entity.y + entity.h;

    //If any of the sides from A are outside of B
    double temp = fabs(bottomA - topB);
    if(bottomA - topB <= 0.001f)
        return false;
    double temp1 = fabs(topA - bottomB);
    if(topA - bottomB >= 0.001f)
        return false;
    double temp2 = fabs(rightA - leftB);
    if(rightA - leftB <= 0.001f)
        return false;
    double temp3 = fabs(leftA - rightB);
    if(leftA - rightB >= 0.001f)
        return false;

    return true;
}

clip CollisionSystem::getClip(Entity *e)
{
    clip c = clip();
    if(e->hasComponentTypes({POSITION_COMPONENT,COLLISION_COMPONENT}))
    {
        auto* pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
        auto* cc = e->getComponentByType<CollisionComponent>(COLLISION_COMPONENT);
        c.x = pc->x + cc->collision_box.x;
        c.y = pc->y + cc->collision_box.y;
        c.w = cc->collision_box.w;
        c.h = cc->collision_box.h;
    }
    return c;
}