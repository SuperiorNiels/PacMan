//
// Created by niels on 05/03/18.
//

#include "../../include/ECS/SystemManager.h"

namespace ECS
{
    void SystemManager::updateSystems()
    {
        for (auto &s : systems)
        {
            s->update();
        }
    }

    void SystemManager::updateUnpausableSystems()
    {
        for (auto &s : systems)
        {
            if (!s->isPausable())
                s->update();
        }
    }

    void SystemManager::updateEntities()
    {
        // Check if entity belongs in system and add to new system (when needed)
        for (auto it = entities.begin(); it != entities.end();)
        {
            auto *e = it->second;
            ++it;
            if (e->getComponentsSize() != 0)
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
        for (auto &sys : systems)
        {
            if (sys == s)
            {
                found = true;
                break;
            }
        }
        if (!found)
            systems.push_back(s);
    }

    void SystemManager::registerEntity(Entity *e)
    {
        if (e != nullptr)
        {
            entities[e->id] = e;
            for (auto *s : systems)
            {
                s->addEntity(e);
            }
        }
    }

    void SystemManager::unregisterEntity(Entity *e)
    {
        if (e == nullptr)
            return;

        // remove the entity from all systems
        for (auto &s : systems)
        {
            if (s->entityInSystem(e->id))
                s->removeEntity(e->id);
        }
        auto it = entities.find(e->id);
        if (it != entities.end())
            entities.erase(it);
    }

    void SystemManager::clearEntities()
    {
        for (auto it : entities)
        {
            for (auto *s : systems)
            {
                s->removeEntity(it.second->id);
            }
            delete it.second;
        }
        entities.clear();
    }

    void SystemManager::removeSystem(System *s)
    {
        for (auto it = systems.begin(); it != systems.end(); it++)
        {
            if (it.operator*() == s)
            {
                systems.erase(it);
                break;
            }
        }
    }

    int SystemManager::entitiesWithComponent(uint8_t type)
    {
        int result = 0;
        for (auto e : entities)
        {
            if (e.second->hasComponentType(type))
                result++;
        }
        return result;
    }

    SystemManager::~SystemManager()
    {
        for (auto it : entities)
            delete it.second;
        for (auto &s : systems)
            delete s;
    }
}
