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
    for(auto& e : entities)
    {
        if(e->hasComponentTypes({AI_COMPONENT,MOVABLE_COMPONENT,POSITION_COMPONENT}))
        {
            auto* ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
            auto* mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            auto* pc = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            auto* target = ac->goal;
            if(target->hasComponentType(POSITION_COMPONENT))
            {
                auto* target_pos = target->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                if(target_pos->x - pc->x < 0 )
                    mc->wanted_dir = LEFT;
                else if(target_pos->x == pc->x)
                {
                    if(target_pos->y - pc->y < 0)
                        mc->wanted_dir = UP;
                    else if(target_pos->y == pc->y)
                        mc->wanted_dir = STOP;
                    else
                        mc->wanted_dir = DOWN;
                }
                else
                    mc->wanted_dir = RIGHT;
            }
        }
    }
}

std::vector<Node*> AISystem::getPath(int start_x, int start_y, int stop_x, int stop_y)
{

}

double AISystem::calculateDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x1-x2,2.f) + pow(y1-y2,2.f));
}