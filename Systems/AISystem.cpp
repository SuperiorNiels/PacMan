//
// Created by niels on 06/03/18.
//

#include "AISystem.h"

AISystem::AISystem(World* world)
{
    component_types = {AI_COMPONENT};
    AISystem::world = world;
}

void AISystem::update()
{
    for (auto it : entities)
    {
        auto e = it.second; // get entity
        if(e->hasComponentTypes({AI_COMPONENT,MOVABLE_COMPONENT,POSITION_COMPONENT}))
        {
            auto *mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);

            if (mc->state == IDLE)
            {
                auto *ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
                auto *pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

                std::multimap<double, direction> best_dirs = std::multimap<double, direction>();

                for(int i=1; i<5; i++)
                {
                    int new_x = pc->x + movement_vector[i][0];
                    int new_y = pc->y + movement_vector[i][1];
                    if(world->getWorld()[new_y][new_x] != 1)
                    {
                        if(world->getWorld()[new_y][new_x] == 2 && !(ac->state == HOME || ac->state == LEAVE || ac->state == RETURN))
                            continue;
                        // Direction is possible
                        double distance = calculateDistance(new_x, new_y, ac->target_x, ac->target_y);

                        direction wanted_dir = STOP;
                        if(i == 1)
                            wanted_dir = LEFT;
                        else if(i == 2)
                            wanted_dir = RIGHT;
                        else if(i == 3)
                            wanted_dir = UP;
                        else if(i == 4)
                            wanted_dir = DOWN;

                        best_dirs.emplace(distance, wanted_dir);
                    }
                }

                for (auto &best_dir : best_dirs)
                {
                    bool change = false;
                    switch(best_dir.second)
                    {
                        case LEFT:
                            if(ac->previous != RIGHT)
                                change = true;
                            break;
                        case RIGHT:
                            if(ac->previous != LEFT)
                                change = true;
                            break;
                        case UP:
                            if(ac->previous != DOWN)
                                change = true;
                            break;
                        case DOWN:
                            if(ac->previous != UP)
                                change = true;
                            break;
                        default:
                            break;
                    }

                    if(change)
                    {
                        mc->wanted_dir = best_dir.second;
                        mc->current_dir = best_dir.second;
                        ac->previous = best_dir.second;
                        break;
                    }
                }
            }
        }
    }
}

double AISystem::calculateDistance(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    return sqrt(dx*dx + dy*dy);
}