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
    if(e->getComponentByType<PlayerInputComponent>(PLAYER_INPUT_COMPONENT) != nullptr)
    {
        to_check.push_back(e);
        return;
    }
    // entity is ghost?
    if(e->getComponentByType<AIComponent>(AI_COMPONENT) != nullptr)
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
            auto *cc = player->getComponentByType<CollisionComponent>(COLLISION_COMPONENT);
            box player_box;
            player_box.x = p->x+cc->collision_box[0];
            player_box.y = p->y+cc->collision_box[1];
            player_box.w = cc->collision_box[2];
            player_box.h = cc->collision_box[3];
            for (auto &e : entities)
            {
                if (e->id != player->id)
                {
                    auto *p2 = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                    auto *cc2 = e->getComponentByType<CollisionComponent>(COLLISION_COMPONENT);
                    box entity_box;
                    entity_box.x = p2->x+cc2->collision_box[0];
                    entity_box.y = p2->y+cc2->collision_box[1];
                    entity_box.w = cc2->collision_box[2];
                    entity_box.h = cc2->collision_box[3];
                    if (checkCollision(player_box, entity_box))
                    {
                        //std::cout << "Player collided with entity: " << e->id << std::endl;
                        auto *m = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                        auto *pc = e->getComponentByType<PointsComponent>(POINTS_COMPONENT);
                        auto *ac = player->getComponentByType<AIComponent>(AI_COMPONENT);
                        if(m != nullptr && pc == nullptr)
                        {
                            p->x -= m->x_speed;
                            p->y -= m->y_speed;
                            m->x_speed = 0;
                            m->y_speed = 0;
                        }
                        if(pc != nullptr)
                        {
                            // add points
                            auto* render = e->getComponentByType<RenderComponent>(RENDER_COMPONENT);
                            render->visable = false;
                        }
                        if(ac != nullptr)
                        {
                            ac->count = ac->length;
                        }
                    }
                }
            }
        }
    }
}

bool CollisionSystem::checkCollision(box a, box b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }
    if( topA >= bottomB )
    {
        return false;
    }
    if( rightA <= leftB )
    {
        return false;
    }
    return leftA < rightB;
}