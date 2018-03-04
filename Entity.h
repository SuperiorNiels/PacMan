//
// Created by niels on 04/03/18.
//

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H


#include <vector>
#include "Component.h"

class Entity {
public:
    void addComponent(Component* c);
    template <class T> T* getComponentById(componentID id);
    template <class T> T* getComponentByType(int8_t type);
    void removeComponentById(componentID id);
    //void removeComponentByType(int8_t type);
private:
    std::vector<Component*> components;
};

inline void Entity::addComponent(Component *c)
{
    if(getComponentByType<Component>(c->type) == nullptr)
    {
        components.push_back(c);
    }
}

template <class T>
T* Entity::getComponentById(componentID id)
{
    for(auto& c : components)
    {
        if(c->id == id)
        {
            return dynamic_cast<T*>(c);
        }
    }
    return nullptr;
}

template <class T>
T* Entity::getComponentByType(int8_t type)
{
    for(auto& c : components)
    {
        if(c->type == type)
        {
            return dynamic_cast<T*>(c);
        }
    }
    return nullptr;
}

#endif //ECS_ENTITY_H
