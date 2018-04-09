//
// Created by niels on 06/03/18.
//

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

    AISystem::pathfinder = new A_star(world);
}

void AISystem::update()
{
    for(auto& e : entities)
    {
        if(e->hasComponentTypes({AI_COMPONENT,MOVABLE_COMPONENT,POSITION_COMPONENT}))
        {
            auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
            auto* mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            auto* pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            auto* target = ac->goal->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            std::cout << "Distance: " << pathfinder->calculateDistance(pc->x,pc->y,target->x,target->y) << std::endl;

            if(ac->path.empty())
                ac->path = pathfinder->getPath(pc->x,pc->y,target->x,target->y);

            if(mc->state == MOVING || ac->path.empty())
                continue;

            PathNode next = ac->path[ac->path.size()-1];
            ac->path.pop_back();

            int direction = 0;
            for(int i=0;i<5;i++)
            {
                int new_x = pc->x + movement_vector[i][0];
                int new_y = pc->y + movement_vector[i][1];
                if(new_x == next.getX() && new_y == next.getY())
                {
                    direction = i;
                    break;
                }
            }

            if(direction == 0 || (pc->x == target->x && pc->y == target->y))
                mc->wanted_dir = STOP;
            if(direction == 1)
                mc->wanted_dir = LEFT;
            if(direction == 2)
                mc->wanted_dir = RIGHT;
            if(direction == 3)
                mc->wanted_dir = UP;
            if(direction == 4)
                mc->wanted_dir = DOWN;

        }
    }
}

AISystem::~AISystem()
{
    delete pathfinder;
}