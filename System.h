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
    void addEntity(Entity* e) {
        // TODO: check if entity is already in array
        entities.push_back(e);
    };
protected:
    //std::vector<int8_t> component_types;
    std::vector<Entity*> entities;
};



#endif //ECS_SYSTEM_H
