//
// Created by niels on 05/03/18.
//

#include "SystemManager.h"

void SystemManager::registerSystem(System *s)
{
    systems.insert(s);
}

void SystemManager::registerEntity(Entity *e)
{
    for(auto it = systems.begin();it!=systems.end();it++)
    {
        System* s = it.operator*();
        for(auto itr = s->component_types.begin(); itr < s->component_types.end(); itr++)
        {
            auto* c = e->getComponentByType<Component>(itr.operator*());
            if(c != nullptr)
            {
                // TODO: Be sure the entity is only added once to the same system
                s->addEntity(e);
            }
        }
    }
}

void SystemManager::unregisterEntity(Entity *e)
{
    // remove the entity from all systems
    for(auto& s : systems)
    {
        s->removeEntity(e->id);
    }
}
