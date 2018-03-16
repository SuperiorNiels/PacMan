//
// Created by niels on 04/03/18.
//

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include <vector>
#include "Entity.h"

class System
{
public:
    virtual void update() = 0;
    virtual void addEntity(Entity* e);
    virtual void removeEntity(entityID id);
    virtual bool checkEntity(Entity* e);
    virtual bool entityInSystem(entityID id);
    virtual ~System();
protected:
    std::vector<Entity*> entities = std::vector<Entity*>();
    std::vector<int8_t> component_types = std::vector<int8_t>();
};

inline void System::addEntity(Entity *e)
{
    if(e->hasComponentTypes(component_types))
    {
        if (!entityInSystem(e->id))
        {
            entities.push_back(e);
        }
    }
}

inline void System::removeEntity(entityID id)
{
    for(auto it = entities.begin(); it < entities.end(); it++)
    {
        if(it.operator*()->id == id)
        {
            entities.erase(it);
            break;
        }
    }
}

inline bool System::checkEntity(Entity* e)
{
    return e->hasComponentTypes(component_types);
}

inline bool System::entityInSystem(entityID id)
{
    for(auto* e: entities)
    {
        if(e->id == id)
            return true;
    }
    return false;
}

inline System::~System()
{
    entities.clear();
    component_types.clear();
}

#endif //ECS_SYSTEM_H
