//
// Created by niels on 05/03/18.
//

#include "SystemManager.h"

void SystemManager::updateSystems()
{
    for(auto& s : systems)
    {
        s->update();
    }
}

void SystemManager::registerSystem(System *s)
{
    // TODO: check if vector is best for keeping the systems (order is important, no doubles)
    bool found = false;
    for(auto& sys : systems)
    {
        if(sys == s) {
            found = true;
            break;
        }
    }
    if(!found)
        systems.push_back(s);
}

void SystemManager::registerEntity(Entity *e)
{
    entities.insert(e);
    for(auto it = systems.begin();it!=systems.end();it++)
    {
        System* s = it.operator*();
        for(auto itr = s->component_types.begin(); itr < s->component_types.end(); itr++)
        {
            auto* c = e->getComponentByType<Component>(itr.operator*());
            if(c != nullptr)
            {
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
    for(auto it = entities.begin();it!=entities.end();it++)
    {
        if(it.operator*()->id == e->id)
        {
            entities.erase(it);
            break;
        }
    }
}

SystemManager::~SystemManager()
{
    for(auto& e : entities)
    {
        delete e;
    }
    for(auto& s : systems)
    {
        delete s;
    }
}
