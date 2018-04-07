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

            int target_pos_x = random_x(random_engine);
            int target_pos_y = random_y(random_engine);

            if(target_pos_x - pc->x < 0 )
                mc->wanted_dir = LEFT;
            else if(target_pos_x == pc->x)
            {
                if(target_pos_y - pc->y < 0)
                    mc->wanted_dir = UP;
                else if(target_pos_y == pc->y)
                    mc->wanted_dir = STOP;
                else
                    mc->wanted_dir = DOWN;
            }
            else
                mc->wanted_dir = RIGHT;
        }

        pathfinder->getPath(50,30,4,5);
    }
}

AISystem::~AISystem()
{
    delete pathfinder;
}