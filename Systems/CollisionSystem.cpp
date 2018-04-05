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
    if(e->hasComponentType(PLAYER_INPUT_COMPONENT) && !entityInSystem(e->id))
    {
        players.push_back(e);
        return;
    }
    if(e->hasComponentType(AI_COMPONENT) && !entityInSystem(e->id))
    {
        ghosts.push_back(e);
        return;
    }
    System::addEntity(e);
}

void CollisionSystem::removeEntity(entityID id)
{
    for(auto it = players.begin(); it != players.end(); it++)
    {
        Entity* e = it.operator*();
        if(e->id == id)
        {
            players.erase(it);
            return;
        }
    }
    for(auto it = ghosts.begin(); it != ghosts.end(); it++)
    {
        Entity* e = it.operator*();
        if(e->id == id)
        {
            ghosts.erase(it);
            return;
        }
    }
    System::removeEntity(id);
}

bool CollisionSystem::entityInSystem(entityID id)
{
    for(auto* e : players)
    {
        if(e->id == id)
            return true;
    }
    for(auto* e : ghosts)
    {
        if(e->id == id)
            return true;
    }
    return System::entityInSystem(id);
}

void CollisionSystem::update()
{
    // TODO: collision for ghosts
    for(auto* player : players)
    {
        auto* mc = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
        if(mc->state == IDLE)
        {
            auto* pc = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            double wanted_x = pc->x + movement_vector[mc->wanted_dir][0];
            double wanted_y = pc->y + movement_vector[mc->wanted_dir][1];
            double new_x = pc->x + movement_vector[mc->current_dir][0];
            double new_y = pc->y + movement_vector[mc->current_dir][1];

            bool wanted_possible = true;
            bool current_possible = true;

            std::vector<Entity*> to_remove = std::vector<Entity*>();

            for (auto& entity : entities)
            {
                auto *pc2 = entity->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                if(!entity->hasComponentType(POINTS_COMPONENT))
                {
                    if(wanted_x == pc2->x && wanted_y == pc2->y)
                        wanted_possible = false;

                    if(new_x == pc2->x && new_y == pc2->y)
                        current_possible = false;
                }
                else
                {
                    if(pc->x == pc2->x && pc->y == pc2->y)
                    {
                        if(player->hasComponentType(SCORE_COMPONENT))
                        {
                            auto* sc = player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
                            auto* pp = entity->getComponentByType<PointsComponent>(POINTS_COMPONENT);
                            sc->score += pp->points;
                        }
                        to_remove.push_back(entity);
                    }
                }
            }

            // Remove entities if needed (points)
            for(auto* e : to_remove)
            {
                e->clearComponents();
                removeEntity(e->id);
            }

            bool dead = false;

            for (auto& ghost : ghosts)
            {
                auto *pc2 = ghost->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                if(pc->x == pc2->x && pc->y == (pc2->y))
                {
                    std::cout << "you are dead" << std::endl;
                    dead = true;
                    if(player->hasComponentType(LIVES_COMPONENT))
                    {
                        auto* lc = player->getComponentByType<LivesComponent>(LIVES_COMPONENT);
                        lc->lives--;
                        pc->x = lc->start_x;
                        pc->y = lc->start_y;
                    }
                }
            }

            if(wanted_possible)
                mc->current_dir = mc->wanted_dir;
            if((!wanted_possible && !current_possible) | dead)
            {
                mc->wanted_dir = STOP;
                mc->current_dir = STOP;
            }
        }
    }
}