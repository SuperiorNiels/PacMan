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
    std::vector<int8_t> component_types = std::vector<int8_t>();
    virtual ~System() = default;
protected:
    std::vector<Entity*> entities = std::vector<Entity*>();
};

inline void System::addEntity(Entity *e)
{
    bool found = false;
    for(auto it = entities.begin(); it<entities.end(); it++)
    {
        if(it.operator*()->id == e->id)
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        entities.push_back(e);
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


#endif //ECS_SYSTEM_H
