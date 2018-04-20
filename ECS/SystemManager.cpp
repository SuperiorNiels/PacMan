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

void SystemManager::updateEntities()
{
    // Check if entity belongs in system and add to new system (when needed)
    for(auto& e : entities)
    {
        if(e->getComponentsSize() != 0)
        {
            for (auto &s : systems)
            {
                if (!s->checkEntity(e) && s->entityInSystem(e->id))
                    s->removeEntity(e->id);
            }
            registerEntity(e);
        }
        else
        {
            unregisterEntity(e);
        }
    }
}

void SystemManager::registerSystem(System *s)
{
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
    entities.emplace(e);
    for(auto* s : systems)
    {
        s->addEntity(e);
    }
}

void SystemManager::unregisterEntity(Entity *e)
{
    // remove the entity from all systems
    for(auto& s : systems)
    {
        if(s->entityInSystem(e->id))
            s->removeEntity(e->id);
    }
    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        if(it.operator*()->id == e->id)
        {
            delete it.operator*();
            entities.erase(it);
            break;
        }
    }
}

void SystemManager::clearEntities()
{
    for(auto e : entities)
    {
        for(auto* s : systems)
        {
            s->removeEntity(e->id);
        }
        delete e;
    }
    entities.clear();
}

void SystemManager::removeSystem(System *s)
{
    for(auto it = systems.begin(); it != systems.end(); it++)
    {
        if(it.operator*() == s)
        {
            systems.erase(it);
            break;
        }
    }
}

SystemManager::~SystemManager()
{
    for(auto& e : entities)
        delete e;
    for(auto& s : systems)
        delete s;
}
