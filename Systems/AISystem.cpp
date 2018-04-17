//
// Created by niels on 06/03/18.
//

#include <map>
#include "AISystem.h"
#include "../Pathfinding/A_star.h"

AISystem::AISystem(World* world)
{
    component_types = {AI_COMPONENT};
    AISystem::world = world;
    std::random_device r;
    random_engine  = std::default_random_engine(r());
    random_x = std::uniform_int_distribution<int>(0, world->getWidth());
    random_y = std::uniform_int_distribution<int>(0, world->getHeight());

    //AISystem::pathfinder = new A_star(world);
}

void AISystem::update()
{
    for(auto& e : entities)
    {
        if(e->hasComponentTypes({AI_COMPONENT,MOVABLE_COMPONENT,POSITION_COMPONENT}))
        {
            auto *ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
            auto *mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            auto *pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            auto* target = ac->goal->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            ac->count++;

            if((pc->x == ac->test_x && pc->y == ac->test_y) || ac->count > 50)
            {
                if(calculateDistance(pc->x,pc->y,target->x,target->y) < 5.f)
                {
                    ac->test_x = target->x;
                    ac->test_y = target->y;
                    //std::cout << "following" << std::endl;
                } else {
                    ac->test_x = random_x(random_engine);
                    ac->test_y = random_y(random_engine);
                    //std::cout << "random" << std::endl;
                }
                ac->count = 0;
                //std::cout << "x: " << ac->test_x << " y: " << ac->test_y << std::endl;
            }

            if (mc->state == IDLE)
            {
                //std::cout << "Distance: " << pathfinder->calculateDistance(pc->x,pc->y,target->x,target->y) << std::endl;

                std::multimap<double, direction> best_dirs = std::multimap<double, direction>();

                for(int i=1; i<5; i++)
                {
                    int new_x = pc->x + movement_vector[i][0];
                    int new_y = pc->y + movement_vector[i][1];
                    if(world->getWorld()[new_y][new_x] != 1)
                    {
                        // Direction is possible
                        double distance = calculateDistance(new_x, new_y, ac->test_x, ac->test_y);

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

AISystem::~AISystem()
{
    delete pathfinder;
}